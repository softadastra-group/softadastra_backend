#include <softadastra/commerce/product/ProductController.hpp>
#include <softadastra/commerce/product/ProductCache.hpp>
#include <softadastra/commerce/product/ProductService.hpp>
#include <adastra/config/env/EnvLoader.hpp>

#include <crow.h>
#include <crow/middlewares/cors.h>
#include <cstdlib>
#include <memory>
#include <mutex>
#include <iostream>
#include <nlohmann/json.hpp>

namespace softadastra::commerce::product
{
    static std::unique_ptr<ProductCache> g_productCache;
    static std::once_flag init_flag;

    void ProductController(crow::App<crow::CORSHandler> &app)
    {
        std::string path = adastra::config::env::EnvLoader::require("PRODUCT_JSON_PATH");

        std::call_once(init_flag, [&]()
                       {
            g_productCache = std::make_unique<ProductCache>(
                path,
                [path]() -> std::vector<Product> {
                    ProductService service(path);
                    return service.getAllProducts();
                },
                [](const std::vector<Product>& products) -> nlohmann::json {
                    nlohmann::json j;
                    j["data"] = nlohmann::json::array();

                    for (const auto& p : products)
                    {
                        j["data"].push_back({
                            {"id", p.getId()},
                            {"title", p.getTitle()},
                            {"image_url", p.getImageUrl()},
                            {"city_name", p.getCityName()},
                            {"country_image_url", p.getCountryImageUrl()},
                            {"currency", p.getCurrency()},
                            {"formatted_price", p.getFormattedPrice()},
                            {"converted_price", p.getConvertedPrice()},
                            {"sizes", p.getSizes()},
                            {"colors", p.getColors()}
                        });
                    }

                    return j;
                }
            );

            g_productCache->getJson(); // Warm up
            std::cout << "[ProductController] Cache produit initialisé.\n"; });

        // Mini documentation
        CROW_ROUTE(app, "/api/products")
        ([]
         {
            nlohmann::json doc = {
                {"endpoints", {
                    {{"method", "GET"}, {"path", "/api/products"}, {"description", "Mini doc des routes produits"}},
                    {{"method", "GET"}, {"path", "/api/products/all"}, {"description", "Tous les produits depuis le cache"}},
                    {{"method", "POST"}, {"path", "/api/products/reload"}, {"description", "Recharge les produits"}},
                    {{"method", "GET"}, {"path", "/api/products/status"}, {"description", "Statut du cache"}}
                }}
            };

            crow::response res(doc.dump(2));
            res.set_header("Content-Type", "application/json");
            return res; });

        // Liste des produits
        CROW_ROUTE(app, "/api/products/all")
        ([]
         {
            try {
                auto& cache = *g_productCache;
                std::string responseStr = cache.getJson();

                crow::response res(responseStr);
                res.set_header("Content-Type", "application/json");
                res.set_header("Cache-Control", "public, max-age=60");
                return res;
            } catch (const std::exception& e) {
                return crow::response(500, std::string("Erreur : ") + e.what());
            } });

        // Rechargement du cache
        CROW_ROUTE(app, "/api/products/reload").methods("POST"_method)([]
                                                                       {
            if (!g_productCache)
            {
                return crow::response(500, "Cache non initialisé");
            }

            try {
                g_productCache->reload();
                std::cout << "[ProductController] Cache produit rechargé.\n";
                return crow::response(200, "Cache rechargé avec succès");
            } catch (const std::exception& e) {
                return crow::response(500, std::string("Erreur lors du rechargement : ") + e.what());
            } });

        // Statut du cache
        CROW_ROUTE(app, "/api/products/status")
        ([]
         {
            if (!g_productCache)
            {
                return crow::response(500, "Cache non initialisé");
            }

            try {
                std::string jsonStr = g_productCache->getJson();
                nlohmann::json parsed = nlohmann::json::parse(jsonStr);
                size_t total = parsed["data"].size();

                nlohmann::json status = {
                    {"status", "🟢 OK"},
                    {"products", total},
                    {"json_size", jsonStr.size()},
                    {"message", "Le cache est chargé et prêt."}
                };

                crow::response res(status.dump(2));
                res.set_header("Content-Type", "application/json");
                res.set_header("Cache-Control", "public, max-age=30");
                return res;
            } catch (const std::exception& e) {
                return crow::response(500, std::string("Erreur lors du diagnostic du cache : ") + e.what());
            } });
    }
}
