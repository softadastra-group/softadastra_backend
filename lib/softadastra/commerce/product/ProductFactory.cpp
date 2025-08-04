#include <softadastra/commerce/product/ProductFactory.hpp>
#include <softadastra/commerce/product/ProductWithPromo.hpp>
#include <softadastra/commerce/product/DigitalProduct.hpp>
#include <iostream>

namespace softadastra::commerce::product
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
            const std::string type = data.value("type", "basic");

            if (type == "promo")
            {
                return std::make_unique<ProductWithPromo>(data);
            }
            else if (type == "digital")
            {
                return std::make_unique<DigitalProduct>(data);
            }

            // Produit par défaut (type: basic)
            return std::make_unique<Product>(
                data.value("title", ""),
                data.value("image_url", ""),
                data.value("city_name", ""),
                data.value("country_image_url", ""),
                data.value("currency", ""),
                data.value("formatted_price", ""),
                data.value("converted_price", ""),
                safeArray(data, "sizes"),
                safeArray(data, "colors"));
        }
        catch (const std::exception &ex)
        {
            std::cerr << "Erreur dans ProductFactory::createFromJson: " << ex.what() << std::endl;
            return nullptr;
        }
    }
}
