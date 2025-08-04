#include <softadastra/commerce/categories/CategoryRepositoryJson.hpp>
#include <nlohmann/json.hpp>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <iostream>

using json = nlohmann::json;

namespace softadastra::commerce::categories
{
    CategoryRepositoryJson::CategoryRepositoryJson(const std::string &filepath)
        : jsonFilePath(filepath) {}

    std::vector<Category> CategoryRepositoryJson::getLeafSubcategories(std::size_t offset, std::size_t limit)
    {
        std::ifstream file(jsonFilePath);
        if (!file)
        {
            throw std::runtime_error("Impossible d'ouvrir le fichier JSON : " + jsonFilePath);
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        json j = json::parse(buffer.str());

        if (!j.contains("categories") || !j["categories"].is_array())
        {
            throw std::runtime_error("Clé 'categories' manquante ou invalide");
        }

        const auto &all = j["categories"];
        std::vector<Category> result;

        std::size_t total = all.size();
        std::size_t end = std::min(offset + limit, total);

        std::cout << "🍃 Chargement des feuilles : offset=" << offset << ", limit=" << limit
                  << ", total=" << total << std::endl;

        for (std::size_t i = offset; i < end; ++i)
        {
            const auto &item = all[i];

            if (!item.contains("id") || !item.contains("name") || !item.contains("image"))
                continue;

            std::optional<uint32_t> parentId;
            if (item.contains("parent_id") && !item["parent_id"].is_null())
            {
                parentId = item["parent_id"].get<uint32_t>();
            }

            Category cat(
                item["name"].get<std::string>(),
                parentId,
                item["image"].get<std::string>());

            cat.setId(item["id"].get<std::uint32_t>());

            if (item.contains("product_count") && item["product_count"].is_number())
            {
                cat.setProductCount(item["product_count"].get<std::uint32_t>());
            }

            result.push_back(cat);
        }

        return result;
    }

    std::vector<Category> CategoryRepositoryJson::getTopLevelCategories()
    {
        std::ifstream file(jsonFilePath);
        if (!file.is_open())
        {
            throw std::runtime_error("Impossible d'ouvrir le fichier JSON : " + jsonFilePath);
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        json j = json::parse(buffer.str());

        if (!j.contains("categories") || !j["categories"].is_array())
        {
            throw std::runtime_error("Clé 'categories' manquante ou invalide");
        }

        const auto &all = j["categories"];
        std::vector<Category> result;

        std::cout << "Recherche des catégories racines sur " << all.size() << " éléments." << std::endl;

        for (const auto &item : all)
        {
            if (!item.contains("id") || !item.contains("name") || !item.contains("image"))
                continue;

            bool isTopLevel = !item.contains("parent_id") || item["parent_id"].is_null();
            std::cout << "Catégorie ID " << item["id"] << " => top-level ? " << std::boolalpha << isTopLevel << std::endl;

            if (isTopLevel)
            {
                Category cat(
                    item["name"].get<std::string>(),
                    std::nullopt,
                    item["image"].get<std::string>());
                cat.setId(item["id"].get<std::uint32_t>());

                if (item.contains("product_count"))
                {
                    cat.setProductCount(item["product_count"].get<std::uint32_t>());
                }

                result.push_back(cat);
            }
        }

        std::cout << "Catégories racines trouvées : " << result.size() << std::endl;

        return result;
    }

    std::vector<Category> CategoryRepositoryJson::getAllCategories()
    {
        return getLeafSubcategories(0, 10000);
    }
}
