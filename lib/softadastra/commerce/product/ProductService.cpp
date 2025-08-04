#include <nlohmann/json.hpp>
#include <fstream>
#include <stdexcept>

#include <softadastra/commerce/product/ProductService.hpp>
#include <softadastra/commerce/product/ProductValidator.hpp>
#include <softadastra/commerce/product/ProductBuilder.hpp>

namespace softadastra::commerce::product
{
    using json = nlohmann::json;

    ProductService::ProductService(const std::string &path)
        : jsonFilePath(path) {}

    std::vector<Product> ProductService::getAllProducts()
    {
        std::ifstream file(jsonFilePath);
        if (!file.is_open())
        {
            throw std::runtime_error("Impossible d'ouvrir le fichier produits : " + jsonFilePath);
        }

        json j;
        file >> j;

        std::vector<Product> products;
        const auto &items = j["data"];

        for (const auto &item : items)
        {
            ProductValidator::validate(item, jsonFilePath);

            Product p = ProductBuilder()
                            .setTitle(item["title"].get<std::string>())
                            .setImageUrl(item["image_url"].get<std::string>())
                            .setCityName(item["city_name"].get<std::string>())
                            .setCountryImageUrl(item["country_image_url"].get<std::string>())
                            .setCurrency(item["currency"].get<std::string>())
                            .setFormattedPrice(item["formatted_price"].get<std::string>())
                            .setConvertedPrice(item["converted_price"].get<std::string>())
                            .setSizes(item["sizes"].get<std::vector<std::string>>())
                            .setColors(item["colors"].get<std::vector<std::string>>())
                            .build();

            p.setId(item["id"].get<uint32_t>());
            products.push_back(std::move(p));
        }

        return products;
    }

};