#ifndef JSON_UTILS_HPP
#define JSON_UTILS_HPP

#include <adastra/utils/json/JsonFileLoader.hpp>

#include <vector>
#include <nlohmann/json.hpp>
#include <iostream>

using namespace adastra::utils::json;

namespace adastra::utils::json
{
    // Sérialise un vecteur d'objets avec .toJson()
    template <typename T>
    inline nlohmann::json serializeVector(const std::string &key, const std::vector<T> &items)
    {
        nlohmann::json j;
        j[key] = nlohmann::json::array();

        for (const auto &item : items)
        {
            j[key].push_back(item.toJson());
        }

        return j;
    }

    // Désérialise un vecteur d'objets avec T::fromJson()
    template <typename T>
    inline std::vector<T> deserializeVector(const nlohmann::json &j, const std::string &key)
    {
        std::vector<T> result;

        if (!j.contains(key) || !j[key].is_array())
            return result;

        for (const auto &item : j[key])
        {
            result.push_back(T::fromJson(item));
        }

        return result;
    }

    template <typename T>
    void printJson(const T &obj)
    {
        std::cout << obj.toJson().dump(2) << std::endl;
    }

    inline const nlohmann::json &getJsonArrayOrThrow(const nlohmann::json &j, const std::string &key)
    {
        if (!j.contains(key) || !j[key].is_array())
        {
            throw std::runtime_error("Clé '" + key + "' manquante ou invalide (attendu : tableau JSON)");
        }
        return j.at(key);
    }

    template <typename T>
    inline std::vector<T> loadVectorFromJsonFile(const std::string &filePath, const std::string &key)
    {
        using nlohmann::json;
        json j = JsonFileLoader::loadJsonFromFile(filePath);
        const auto &array = getJsonArrayOrThrow(j, key);

        std::vector<T> result;
        for (const auto &item : array)
        {
            result.push_back(T::fromJson(item));
        }
        return result;
    }

}

#endif // JSON_UTILS_HPP
