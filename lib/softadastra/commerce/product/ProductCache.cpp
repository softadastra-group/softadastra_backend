#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <chrono>
#include <filesystem>

#include <softadastra/commerce/product/ProductCache.hpp>
#include <softadastra/commerce/product/ProductService.hpp>

namespace softadastra::commerce::product
{
    using json = nlohmann::json;

    ProductCache::ProductCache(const std::string &path)
        : jsonFilePath(path), isLoaded(false) {}

    std::string ProductCache::getJsonResponse()
    {
        auto start = std::chrono::steady_clock::now();

        std::lock_guard<std::mutex> lock(mutex);
        if (!isLoaded)
        {
            loadProducts();
        }

        auto end = std::chrono::steady_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "⏱ getJsonResponse() : " << ms << "ms\n";

        return cachedJson;
    }

    void ProductCache::reload()
    {
        std::lock_guard<std::mutex> lock(mutex);
        loadProducts();
    }

    void ProductCache::loadProducts()
    {
        if (loadFromCacheFile())
        {
            std::cout << "Cache chargé depuis le fichier `.cache`\n";
            isLoaded = true;
            return;
        }

        std::cout << "️Rechargement complet depuis le JSON original...\n";
        ProductService service(jsonFilePath);
        auto products = service.getAllProducts();

        json response;
        response["data"] = json::array();

        for (const auto &p : products)
        {
            response["data"].push_back({{"id", p.id},
                                        {"title", p.title},
                                        {"image_url", p.image_url},
                                        {"city_name", p.city_name},
                                        {"country_image_url", p.country_image_url},
                                        {"currency", p.currency},
                                        {"formatted_price", p.formatted_price},
                                        {"converted_price", p.converted_price},
                                        {"sizes", p.sizes},
                                        {"colors", p.colors}});
        }

        cachedJson = response.dump();
        isLoaded = true;

        saveToCacheFile();
    }

    bool ProductCache::loadFromCacheFile()
    {
        const std::string cachePath = "products.cache";

        if (!std::filesystem::exists(cachePath))
        {
            return false;
        }

        std::ifstream cacheFile(cachePath);
        if (!cacheFile.is_open())
            return false;

        cachedJson.assign((std::istreambuf_iterator<char>(cacheFile)),
                          std::istreambuf_iterator<char>());

        return !cachedJson.empty();
    }

    void ProductCache::saveToCacheFile()
    {
        const std::string cachePath = "products.cache";
        std::ofstream out(cachePath);
        if (out.is_open())
        {
            out << cachedJson;
            std::cout << "📝 Cache sauvegardé dans `products.cache`\n";
        }
    }

};