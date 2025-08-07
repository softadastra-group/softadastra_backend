#include <softadastra/commerce/products/ProductFactory.hpp>
#include <softadastra/commerce/products/ProductBuilder.hpp>
#include <softadastra/commerce/products/ProductValidator.hpp>
#include <iostream>

namespace softadastra::commerce::products
{
    static std::vector<std::string> safeArray(const nlohmann::json &j, const std::string &key)
    {
        if (j.contains(key) && j[key].is_array())
        {
            return j.at(key).get<std::vector<std::string>>();
        }
        return {};
    }

    static std::vector<std::pair<std::string, std::string>> parseCustomFieldsFlexible(const nlohmann::json &customFields)
    {
        std::vector<std::pair<std::string, std::string>> result;

        for (const auto &item : customFields)
        {
            if (item.is_array() && item.size() == 2 && item[0].is_string() && item[1].is_string())
            {
                result.emplace_back(item[0], item[1]); // format API
            }
            else if (item.is_object() && item.contains("name") && item.contains("value") &&
                     item["name"].is_string() && item["value"].is_string())
            {
                result.emplace_back(item["name"], item["value"]); // format interne
            }
        }

        return result;
    }

    std::unique_ptr<Product> ProductFactory::createFromJson(const nlohmann::json &data)
    {
        try
        {
            std::cout << "📥 JSON reçu dans ProductFactory::createFromJson:\n"
                      << data.dump(2) << std::endl;

            ProductValidator::validate(data, "createFromJson");

            ProductBuilder builder;
            builder.setTitle(data.value("title", ""))
                .setImageUrl(data.value("image_url", ""))
                .setCityName(data.value("city_name", ""))
                .setCountryImageUrl(data.value("country_image_url", ""))
                .setCurrency(data.value("currency", ""))
                .setFormattedPrice(data.value("formatted_price", ""))
                .setConvertedPrice(data.value("converted_price", ""))
                .setPriceWithShipping(data.value("price_with_shipping_value", 0.0f))
                .setSizes(safeArray(data, "sizes"))
                .setColors(safeArray(data, "colors"))
                .setConditionName(data.value("condition_name", ""))
                .setBrandName(data.value("brand_name", ""))
                .setPackageFormatName(data.value("package_format_name", ""))
                .setCategoryId(data.value("category_id", 0))
                .setViews(data.value("views", 0))
                .setReviewCount(data.value("review_count", 0))
                .setBoost(data.value("boost", false))
                .setConvertedPriceValue(data.value("converted_price_value", 0.0f))
                .setOriginalPrice(data.value("original_price", ""))
                .setAverageRating(data.value("average_rating", 0.0f));

            if (data.contains("similar_products") && data["similar_products"].is_array())
            {
                builder.setSimilarProducts(data["similar_products"].get<std::vector<uint32_t>>());
            }

            if (data.contains("custom_fields") && data["custom_fields"].is_array())
            {
                builder.setCustomFields(parseCustomFieldsFlexible(data["custom_fields"]));
            }

            if (data.contains("images") && data["images"].is_array())
            {
                builder.setImages(data["images"].get<std::vector<std::string>>());
            }

            return std::make_unique<Product>(builder.build());
        }
        catch (const std::exception &ex)
        {
            std::cerr << "Erreur dans ProductFactory::createFromJson: " << ex.what() << std::endl;
            std::cerr << "🔎 JSON en erreur : " << data.dump(2) << std::endl;
            return nullptr;
        }
    }

    std::unique_ptr<Product> ProductFactory::createFromInternalJson(const nlohmann::json &data)
    {
        try
        {
            ProductBuilder builder;
            builder.setId(data.value("id", 0))
                .setTitle(data.value("title", ""))
                .setImageUrl(data.value("image_url", ""))
                .setCityName(data.value("city_name", ""))
                .setCountryImageUrl(data.value("country_image_url", ""))
                .setCurrency(data.value("currency", ""))
                .setFormattedPrice(data.value("formatted_price", ""))
                .setConvertedPrice(data.value("converted_price", ""))
                .setPriceWithShipping(data.value("price_with_shipping_value", 0.0f))
                .setSizes(safeArray(data, "sizes"))
                .setColors(safeArray(data, "colors"))
                .setConditionName(data.value("condition_name", ""))
                .setBrandName(data.value("brand_name", ""))
                .setPackageFormatName(data.value("package_format_name", ""))
                .setCategoryId(data.value("category_id", 0))
                .setViews(data.value("views", 0))
                .setReviewCount(data.value("review_count", 0))
                .setBoost(data.value("boost", false))
                .setConvertedPriceValue(data.value("converted_price_value", 0.0f))
                .setOriginalPrice(data.value("original_price", ""))
                .setAverageRating(data.value("average_rating", 0.0f));

            if (data.contains("similar_products") && data["similar_products"].is_array())
            {
                builder.setSimilarProducts(data["similar_products"].get<std::vector<uint32_t>>());
            }

            if (data.contains("custom_fields") && data["custom_fields"].is_array())
            {
                builder.setCustomFields(parseCustomFieldsFlexible(data["custom_fields"]));
            }

            if (data.contains("images") && data["images"].is_array())
            {
                builder.setImages(data["images"].get<std::vector<std::string>>());
            }

            return std::make_unique<Product>(builder.build());
        }
        catch (const std::exception &ex)
        {
            std::cerr << "Erreur dans ProductFactory::createFromInternalJson: " << ex.what() << std::endl;
            std::cerr << "🔎 JSON en erreur : " << data.dump(2) << std::endl;
            return nullptr;
        }
    }

    Product ProductFactory::fromJsonOrThrow(const nlohmann::json &data)
    {
        auto ptr = createFromJson(data);
        if (!ptr)
            throw std::runtime_error("ProductFactory::fromJsonOrThrow() → JSON invalide");
        return *ptr;
    }
}
