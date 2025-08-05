#ifndef CATEGORY_JSON_PARSER_HPP
#define CATEGORY_JSON_PARSER_HPP

#include <nlohmann/json.hpp>
#include <softadastra/commerce/categories/Category.hpp>
#include <vector>

namespace softadastra::commerce::categories
{
    inline std::vector<Category> parseCategoryJson(const nlohmann::json &j)
    {
        std::vector<Category> result;
        if (!j.contains("categories"))
            return result;

        for (const auto &item : j["categories"])
        {
            Category c;
            if (item.contains("id"))
                c.setId(item["id"]);
            if (item.contains("name"))
                c.setName(item["name"]);
            if (item.contains("image_url"))
                c.setImageUrl(item["image_url"]);
            if (item.contains("parent_id") && !item["parent_id"].is_null())
                c.setParentId(item["parent_id"]);

            result.push_back(c);
        }

        return result;
    }
}

#endif // CATEGORY_JSON_PARSER_HPP
