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

    std::unique_ptr<Product> ProductFactory::createFromJson(const nlohmann::json &data)
    {
        try
        {
            std::cerr << "Tentative de chargement produit ID : " << data.value("id", -1) << std::endl;
            ProductValidator::validate(data, "createFromJson");

            ProductBuilder builder;
            builder.setId(data.value("id", 0))
                .setTitle(data.value("title", ""))
                .setImageUrl(data.contains("image_url") && data["image_url"].is_string()
                                 ? data["image_url"].get<std::string>()
                                 : "")
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
                .setBoost(data.contains("boost")
                              ? static_cast<bool>(data["boost"].get<int>())
                              : false);

            if (data.contains("converted_price_value") && data["converted_price_value"].is_number())
                builder.setConvertedPriceValue(data["converted_price_value"].get<float>());
            else
                builder.setConvertedPriceValue(0.0f);

            if (data.contains("original_price") && data["original_price"].is_string())
                builder.setOriginalPrice(data["original_price"].get<std::string>());
            else
                builder.setOriginalPrice("");

            if (data.contains("average_rating") && data["average_rating"].is_number())
                builder.setAverageRating(data["average_rating"].get<float>());
            else
                builder.setAverageRating(0.0f);

            Product product = builder.build();
            return std::make_unique<Product>(std::move(product));
        }
        catch (const std::exception &ex)
        {
            std::cerr << "❌ Erreur dans ProductFactory::createFromJson: " << ex.what() << std::endl;
            // std::cerr << "🔎 JSON en erreur : " << data.dump(2) << std::endl;
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
