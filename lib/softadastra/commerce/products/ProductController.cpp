#include <softadastra/commerce/products/ProductController.hpp>
#include <softadastra/commerce/products/ProductCache.hpp>
#include <softadastra/commerce/products/ProductService.hpp>
#include <adastra/config/env/EnvLoader.hpp>

#include <adastra/utils/json/JsonUtils.hpp>

#include <crow.h>
#include <crow/middlewares/cors.h>
#include <cstdlib>
#include <memory>
#include <mutex>
#include <iostream>
#include <nlohmann/json.hpp>

using namespace adastra::utils::json;

namespace softadastra::commerce::product
{
    static std::unique_ptr<ProductCache> g_productCache;
    static std::once_flag init_flag;

    void ProductController(crow::App<crow::CORSHandler> &app)
    {
        std::string path = adastra::config::env::EnvLoader::require("PRODUCT_JSON_PATH");

        std::call_once(init_flag, [&]()
                       {
                        std::vector<Product> loaded = ProductService(path).getAllProducts();

            g_productCache = std::make_unique<ProductCache>(
                path,
                [loaded]() -> std::vector<Product> {
                    return  loaded;
                },
                [](const std::vector<Product>& products) -> nlohmann::json {
                    return serializeVector("product", products);
                },
                [](const nlohmann::json& j){
                    return deserializeVector<Product>(j, "products");
                }
            );

            g_productCache->getJson(); // Warm up
            std::cout << "[ProductController] Cache produit initialisé.\n"; });

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
