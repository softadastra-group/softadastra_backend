#ifndef PRODUCT_REPOSITORY_SQL_HPP
#define PRODUCT_REPOSITORY_SQL_HPP

#include <softadastra/commerce/products/Product.hpp>
#include <adastra/database/Database.hpp>

#include <vector>
#include <memory>
#include <string>

namespace softadastra::commerce::products
{
    class ProductRepositorySQL
    {
    public:
        explicit ProductRepositorySQL(std::shared_ptr<adastra::database::Database> db);

        void insert(Product &product); // ⬅️ maintenant on modifie product pour y mettre l'id
        std::vector<Product> findAll();

        void batchInsert(const std::string &table, uint32_t productId, const std::vector<std::string> &values, const std::string &column);
        void batchInsert(const std::string &tableName, uint32_t productId, const std::vector<uint32_t> &values, const std::string &columnName);

        void batchInsertWithStrings(const std::string &table, uint32_t productId, const std::vector<std::string> &values, const std::string &column);
        void batchInsertCustomFields(const std::string &table, uint32_t productId, const std::vector<std::pair<std::string, std::string>> &fields);

    private:
        std::shared_ptr<adastra::database::Database> db_;
    };
}

#endif // PRODUCT_REPOSITORY_SQL_HPP
