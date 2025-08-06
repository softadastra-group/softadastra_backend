#include <softadastra/commerce/products/ProductValidator.hpp>
#include <stdexcept>
#include <iostream>

namespace softadastra::commerce::products
{
    void ProductValidator::validate(const nlohmann::json &item, const std::string &source)
    {
        auto require_string = [&](const std::string &key)
        {
            if (!item.contains(key) || !item[key].is_string())
                throw std::runtime_error("Produit invalide : clé '" + key + "' manquante ou invalide dans : " + source);
        };

        auto require_uint = [&](const std::string &key)
        {
            if (!item.contains(key) || !item[key].is_number_unsigned())
                throw std::runtime_error("Produit invalide : clé '" + key + "' manquante ou invalide dans : " + source);
        };

        auto require_array = [&](const std::string &key)
        {
            if (!item.contains(key) || !item[key].is_array())
                throw std::runtime_error("Produit invalide : clé '" + key + "' manquante ou invalide dans : " + source);
        };

        auto require_bool_like = [&](const std::string &key)
        {
            if (!item.contains(key) ||
                !(item[key].is_boolean() ||
                  (item[key].is_number_integer() && (item[key] == 0 || item[key] == 1))))
            {
                throw std::runtime_error("Produit invalide : clé '" + key + "' manquante ou invalide dans : " + source);
            }
        };

        require_uint("id");
        require_string("title");
        require_string("image_url");
        require_string("city_name");
        require_string("country_image_url");
        require_string("currency");
        require_string("formatted_price");
        require_string("converted_price");
        require_array("sizes");
        require_array("colors");
        require_string("condition_name");
        require_string("brand_name");
        require_string("package_format_name");
        require_uint("category_id");
        require_uint("views");
        require_uint("review_count");
        require_bool_like("boost");

        if (item.contains("converted_price_value") && !item["converted_price_value"].is_number())
        {
            throw std::runtime_error("Produit invalide : 'converted_price_value' présent mais invalide dans : " + source);
        }

        if (item.contains("price_with_shipping_value") && !item["price_with_shipping_value"].is_number())
        {
            throw std::runtime_error("Produit invalide : 'price_with_shipping_value' présent mais invalide dans : " + source);
        }

        if (item.contains("average_rating") && !item["average_rating"].is_null() && !item["average_rating"].is_number())
        {
            throw std::runtime_error("Produit invalide : 'average_rating' présent mais invalide dans : " + source);
        }
    }

    bool ProductValidator::isValid(const nlohmann::json &item)
    {
        try
        {
            validate(item, "isValid() check");
            return true;
        }
        catch (const std::exception &e)
        {
            std::cerr << "[ProductValidator] ⚠ Produit rejeté : " << e.what() << std::endl;
            return false;
        }
    }
}
