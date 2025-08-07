#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <memory>
#include <mutex>
#include <stdexcept>
#include <cppconn/prepared_statement.h>
#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/resultset.h>
#include <mysql_driver.h>
#include <vector>
#include <any>

namespace adastra::database
{
    class DatabaseException : public std::exception
    {
    public:
        explicit DatabaseException(const std::string &message);
        const char *what() const noexcept override;
        ~DatabaseException() noexcept = default;

    private:
        std::string message;
    };

    class Database
    {
    private:
        static std::unique_ptr<Database> instance;
        static std::mutex mtx;
        std::shared_ptr<sql::Connection> connection;
        std::string host;
        std::string user;
        std::string password;
        std::string database;

    public:
        Database(const std::string &host, const std::string &user, const std::string &password, const std::string &database);
        void connect();
        std::unique_ptr<sql::ResultSet> executeQuery(const std::string &query);
        // std::unique_ptr<sql::ResultSet> executePreparedQuery(const std::string &query, int param);
        std::unique_ptr<sql::ResultSet> executePreparedQuery(const std::string &query, const std::vector<std::any> &params);
        std::shared_ptr<sql::Connection> getConnection();
        ~Database();

        Database(const Database &) = delete;
        Database &operator=(const Database &) = delete;

        static std::unique_ptr<Database> &getInstance(const std::string &host, const std::string &user, const std::string &password, const std::string &database);

        // Fonctions utilitaires
        static std::string join(const std::vector<std::string> &vec, const std::string &delimiter);
        static std::string placeholders(size_t count);
        static std::string createSetClause(const std::vector<std::string> &columns);

        // Fonctions CRUD génériques
        template <typename... Args>
        void create(const std::string &table, const std::vector<std::string> &columns, Args &&...args);

        template <typename... Args>
        void update(const std::string &table, const std::vector<std::string> &columns, const std::vector<std::string> &values, const std::string &condition, Args &&...args);

        template <typename... Args>
        void remove(const std::string &table, const std::string &condition, Args &&...args);

        template <typename T, typename... Args>
        void setParameters(std::unique_ptr<sql::PreparedStatement> &pstmt, int index, T &&value, Args &&...args);

        template <typename T>
        void setParameters(std::unique_ptr<sql::PreparedStatement> &pstmt, int index, T &&value);

        // Fonction de setParameter pour les types spécifiques (si nécessaire)
        void setParameter(std::unique_ptr<sql::PreparedStatement> &pstmt, int index, int value);
        void setParameter(std::unique_ptr<sql::PreparedStatement> &pstmt, int index, double value);
        void setParameter(std::unique_ptr<sql::PreparedStatement> &pstmt, int index, const std::string &value);
        void setParameter(std::unique_ptr<sql::PreparedStatement> &pstmt, int index, const char *value);

        // Méthodes pour la gestion des transactions
        void beginTransaction()
        {
            if (connection)
            {
                connection->setAutoCommit(false);
            }
            else
            {
                throw DatabaseException("La connexion à la base de données n'est pas établie.");
            }
        }

        void commit()
        {
            if (connection)
            {
                connection->commit();
                connection->setAutoCommit(true); // Revenir au mode auto-commit
            }
            else
            {
                throw DatabaseException("La connexion à la base de données n'est pas établie.");
            }
        }

        void rollback()
        {
            if (connection)
            {
                connection->rollback();
                connection->setAutoCommit(true); // Revenir au mode auto-commit
            }
            else
            {
                throw DatabaseException("La connexion à la base de données n'est pas établie.");
            }
        }
    };

    template <typename... Args>
    void Database::create(const std::string &table, const std::vector<std::string> &columns, Args &&...args)
    {
        try
        {
            // Construction de la requête SQL avec les placeholders
            std::string query = "INSERT INTO " + table + " (" + join(columns, ", ") + ") VALUES (" + placeholders(columns.size()) + ")";

            // Afficher la requête pour déboguer
            std::cout << "Requête SQL générée : " << query << std::endl;

            // Préparer la requête
            std::unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement(query));

            // Lier les paramètres
            setParameters(pstmt, 1, std::forward<Args>(args)...);

            // Exécuter la requête
            pstmt->executeUpdate();
        }
        catch (sql::SQLException &e)
        {
            throw DatabaseException("Erreur d'exécution de la requête d'insertion : " + std::string(e.what()));
        }
    }

    template <typename... Args>
    void Database::update(const std::string &table, const std::vector<std::string> &columns, const std::vector<std::string> &values, const std::string &condition, Args &&...args)
    {
        try
        {
            std::string query = "UPDATE " + table + " SET " + createSetClause(columns) + " WHERE " + condition;
            std::unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement(query));

            size_t index = 1;
            for (const auto &value : values)
            {
                setParameter(pstmt, index++, value);
            }

            if constexpr (sizeof...(args) > 0)
            {
                setParameters(pstmt, index, std::forward<Args>(args)...);
            }

            pstmt->executeUpdate();
        }
        catch (sql::SQLException &e)
        {
            throw DatabaseException("Erreur d'exécution de la requête de mise à jour : " + std::string(e.what()));
        }
    }

    template <typename... Args>
    void Database::remove(const std::string &table, const std::string &condition, Args &&...args)
    {
        try
        {
            std::string query = "DELETE FROM " + table + " WHERE " + condition;
            std::cout << "Requête SQL de suppression : " << query << std::endl; // Ajoutez une impression pour le débogage
            std::unique_ptr<sql::PreparedStatement> pstmt(connection->prepareStatement(query));

            if constexpr (sizeof...(args) > 0)
            {
                setParameters(pstmt, 1, std::forward<Args>(args)...);
            }

            pstmt->executeUpdate();
        }
        catch (sql::SQLException &e)
        {
            throw DatabaseException("Erreur d'exécution de la requête de suppression : " + std::string(e.what()));
        }
    }

    // Implémentation de setParameters pour un seul argument
    template <typename T>
    void Database::setParameters(std::unique_ptr<sql::PreparedStatement> &pstmt, int index, T &&value)
    {
        setParameter(pstmt, index, std::forward<T>(value)); // Lier le paramètre actuel
    }

    // Implémentation de setParameters pour plusieurs arguments (variadic templates)
    template <typename T, typename... Args>
    void Database::setParameters(std::unique_ptr<sql::PreparedStatement> &pstmt, int index, T &&value, Args &&...args)
    {
        setParameter(pstmt, index, std::forward<T>(value));           // Lier le paramètre actuel
        setParameters(pstmt, index + 1, std::forward<Args>(args)...); // Appel récursif pour les paramètres restants
    }
}

#endif // DATABASE_H
