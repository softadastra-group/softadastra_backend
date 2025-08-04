#include <softadastra/commerce/products/ProductValidator.hpp>
#include <stdexcept>

namespace softadastra::commerce::product
{
    void ProductValidator::validate(const nlohmann::json &item, const std::string &source)
    {
        if (!item.contains("id") || !item["id"].is_number_unsigned())
        {
            throw std::runtime_error("Produit sans ID valide dans : " + source);
        }
        if (!item.contains("title") || !item["title"].is_string())
        {
            throw std::runtime_error("Produit sans titre valide dans : " + source);
        }
        if (!item.contains("image_url") || !item["image_url"].is_string())
        {
            throw std::runtime_error("Produit sans image_url valide dans : " + source);
        }
        if (!item.contains("city_name") || !item["city_name"].is_string())
        {
            throw std::runtime_error("Produit sans city_name valide dans : " + source);
        }
        if (!item.contains("country_image_url") || !item["country_image_url"].is_string())
        {
            throw std::runtime_error("Produit sans country_image_url valide dans : " + source);
        }
        if (!item.contains("currency") || !item["currency"].is_string())
        {
            throw std::runtime_error("Produit sans currency valide dans : " + source);
        }
        if (!item.contains("formatted_price") || !item["formatted_price"].is_string())
        {
            throw std::runtime_error("Produit sans formatted_price valide dans : " + source);
        }
        if (!item.contains("converted_price") || !item["converted_price"].is_string())
        {
            throw std::runtime_error("Produit sans converted_price valide dans : " + source);
        }
        if (!item.contains("sizes") || !item["sizes"].is_array())
        {
            throw std::runtime_error("Produit sans sizes valide dans : " + source);
        }
        if (!item.contains("colors") || !item["colors"].is_array())
        {
            throw std::runtime_error("Produit sans colors valide dans : " + source);
        }
    }
}
