#ifndef CATEGORY_FACTORY_HPP
#define CATEGORY_FACTORY_HPP

#include <softadastra/commerce/categories/Category.hpp>
#include <softadastra/commerce/categories/CategoryBuilder.hpp>
#include <nlohmann/json.hpp>

namespace softadastra::commerce::categories
{
    class CategoryFactory
    {
    public:
        static Category fromJson(const nlohmann::json &data)
        {
            CategoryBuilder builder;

            if (data.contains("id"))
                builder.setId(data["id"].get<std::uint32_t>());

            if (data.contains("name"))
                builder.setName(data["name"].get<std::string>());

            if (data.contains("parent_id") && !data["parent_id"].is_null())
                builder.setParentId(data["parent_id"].get<std::uint32_t>());

            if (data.contains("image_url"))
                builder.setImageUrl(data["image_url"].get<std::string>());

            if (data.contains("product_count"))
                builder.setProductCount(data["product_count"].get<std::uint32_t>());

            return builder.build();
        }
    };
}

#endif // CATEGORY_FACTORY_HPP
