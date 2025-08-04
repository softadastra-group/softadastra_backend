#include <softadastra/commerce/products/ProductFactory.hpp>
#include <softadastra/commerce/products/ProductWithPromo.hpp>
#include <softadastra/commerce/products/DigitalProduct.hpp>
#include <softadastra/commerce/products/ProductBuilder.hpp>
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

            Product product = ProductBuilder()
                                  .setTitle(data.value("title", ""))
                                  .setImageUrl(data.value("image_url", ""))
                                  .setCityName(data.value("city_name", ""))
                                  .setCountryImageUrl(data.value("country_image_url", ""))
                                  .setCurrency(data.value("currency", ""))
                                  .setFormattedPrice(data.value("formatted_price", ""))
                                  .setConvertedPrice(data.value("converted_price", ""))
                                  .setSizes(safeArray(data, "sizes"))
                                  .setColors(safeArray(data, "colors"))
                                  .build();

            return std::make_unique<Product>(std::move(product));
        }
        catch (const std::exception &ex)
        {
            std::cerr << "Erreur dans ProductFactory::createFromJson: " << ex.what() << std::endl;
            return nullptr;
        }
    }
}
