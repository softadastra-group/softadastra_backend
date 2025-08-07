#include <softadastra/commerce/products/ProductController.hpp>
#include <softadastra/commerce/products/ProductCache.hpp>
#include <softadastra/commerce/products/ProductService.hpp>
#include <softadastra/commerce/products/ProductRecommender.hpp>
#include <softadastra/commerce/products/ProductValidator.hpp>
#include <softadastra/commerce/products/ProductFactory.hpp>
#include <softadastra/commerce/products/ProductServiceFromSQL.hpp>

#include <adastra/config/env/EnvLoader.hpp>
#include <adastra/utils/json/JsonUtils.hpp>
#include <adastra/database/Database.hpp>

#include <crow.h>
#include <crow/middlewares/cors.h>
#include <cstdlib>
#include <memory>
#include <mutex>
#include <iostream>
#include <nlohmann/json.hpp>

using namespace adastra::utils::json;

namespace softadastra::commerce::products
{
    static std::unique_ptr<ProductCache> g_productCache;
    static std::once_flag init_flag;
    constexpr int DEFAULT_LIMIT = 10;
    constexpr int DEFAULT_OFFSET = 0;

    void ProductController(crow::App<crow::CORSHandler> &app)
    {
        std::string path = adastra::config::env::EnvLoader::require("PRODUCT_JSON_PATH");

        std::call_once(init_flag, [&]()
                       {
                           auto deserializer = [](const nlohmann::json &json) -> std::vector<Product>
                           {
                               if (!json.contains("data") || !json["data"].is_array())
                               {
                                   throw std::runtime_error("Clé 'data' manquante ou invalide (attendu : tableau JSON)");
                               }

                               std::vector<Product> products;
                               for (const auto &item : json["data"])
                               {
                                   try
                                   {
                                       products.push_back(ProductFactory::fromJsonOrThrow(item));
                                   }
                                   catch (const std::exception &e)
                                   {
                                       std::cerr << "Produit ignoré : " << e.what() << std::endl;
                                   }
                               }

                               return products;
                           };

                           auto serializer = [](const std::vector<Product> &products) -> nlohmann::json
                           {
                               nlohmann::json j;
                               j["data"] = nlohmann::json::array();
                               for (const auto &p : products)
                               {
                                   j["data"].push_back(p.toJson());
                               }
                               return j;
                           };

                           g_productCache = std::make_unique<ProductCache>(
                               path,
                               []() -> std::vector<Product>
                               {
                                   return {};
                               },
                               serializer,
                               deserializer);

                           g_productCache->reload();
                           // std::cout << "[ProductController] Cache produit initialisé depuis le fichier.\n";
                       });

        CROW_ROUTE(app, "/api/products/create").methods("POST"_method)([](const crow::request &req)
                                                                       {
        try
        {
            auto json = nlohmann::json::parse(req.body);
            Product product = ProductFactory::fromJsonOrThrow(json);

            // 🛢 Connexion à la base via getInstance
            auto &db = adastra::database::Database::getRef(
                adastra::config::env::EnvLoader::require("DB_HOST"),
                adastra::config::env::EnvLoader::require("DB_USER"),
                adastra::config::env::EnvLoader::require("DB_PASS"),
                adastra::config::env::EnvLoader::require("DB_NAME"));

            // 🔐 Encapsuler la référence dans un shared_ptr sans la détruire
            auto dbPtr = std::shared_ptr<adastra::database::Database>(&db, [](adastra::database::Database *) {
                // 🔒 Ne rien faire pour éviter la destruction de l'instance globale
            });

            ProductServiceFromSQL service(dbPtr);
            service.create(product);

            crow::response res(nlohmann::json{
                                   {"status", "success"},
                                   {"message", "Produit créé avec succès"}}.dump(2));

            res.set_header("Content-Type", "application/json");
            return res;
        }
        catch (const std::exception &e)
        {
            return crow::response(500, nlohmann::json{
                                             {"status", "error"},
                                             {"message", std::string("Exception: ") + e.what()}}
                                             .dump(2));
        } });

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

        CROW_ROUTE(app, "/api/products/recommend")
            .methods("POST"_method)([](const crow::request &req)
                                    {
            try {
                nlohmann::json requestJson = nlohmann::json::parse(req.body);

                std::unique_ptr<Product> referencePtr = ProductFactory::createFromInternalJson(requestJson);
                if (!referencePtr) {
                    return crow::response(400, R"({"status":"error","message":"Invalid product JSON."})");
                }

                const Product &reference = *referencePtr;
                auto &cache = *g_productCache;
                std::vector<Product> allProducts = cache.getAll();

                std::vector<Product> recommendations = ProductRecommender::recommendSimilar(reference, allProducts, 10);

                nlohmann::json responseJson = {
                    {"status", "success"},
                    {"recommendations", serializeVector("products", recommendations)},
                    {"total_recommendations", recommendations.size()},
                    {"limit", 10},
                    {"offset", 0}
                };

                crow::response res(responseJson.dump(2));
                res.set_header("Content-Type", "application/json");
                return res;

            } catch (const std::exception &e) {
                return crow::response(500, R"({"status":"error","message":"Exception in POST /recommend: )" + std::string(e.what()) + R"("})");
            } });

        CROW_ROUTE(app, "/api/products/recommend/<int>")
            .methods("GET"_method)([](const crow::request &req, int id)
                                   {
            try {
                auto &cache = *g_productCache;
                std::vector<Product> allProducts = cache.getAll();
                // std::cout << "🔎 Recherche produit ID " << id << " dans cache de taille " << allProducts.size() << std::endl;
                // for (const auto& p : allProducts) {
                //     std::cout << "→ ID dans cache: " << p.getId() << std::endl;
                // }

                auto it = std::find_if(allProducts.begin(), allProducts.end(), [id](const Product &p) {
                    return p.getId() == static_cast<std::uint32_t>(id);
                });

                if (it == allProducts.end()) {
                    return crow::response(404, crow::json::wvalue({
                        {"status", "error"},
                        {"message", "Product not found for recommendation"},
                        {"product_id", id}
                    }));
                }

                const Product &referenceProduct = *it;

                constexpr int DEFAULT_LIMIT = 10;
                constexpr int DEFAULT_OFFSET = 0;

                int limit = req.url_params.get("limit") ? std::atoi(req.url_params.get("limit")) : DEFAULT_LIMIT;
                int offset = req.url_params.get("offset") ? std::atoi(req.url_params.get("offset")) : DEFAULT_OFFSET;

                std::vector<Product> recommendations = ProductRecommender::recommendSimilar(referenceProduct, allProducts, offset + limit);

                int total = static_cast<int>(recommendations.size());
                int start = std::clamp(offset, 0, total);
                int end = std::clamp(offset + limit, 0, total);

                std::vector<Product> paginated(recommendations.begin() + start, recommendations.begin() + end);

                nlohmann::json responseJson = {
                    {"status", "success"},
                    {"reference_product_id", id},
                    {"limit", limit},
                    {"offset", offset},
                    {"total_recommendations", total},
                    {"recommendations", serializeVector("products", paginated)}
                };

                crow::response res(responseJson.dump(2));
                res.set_header("Content-Type", "application/json");
                return res;

            } catch (const std::exception &e) {
                return crow::response(500, R"({"status":"error","message":"Exception in GET /recommend: )" + std::string(e.what()) + R"("})");
            } });

        CROW_ROUTE(app, "/api/products/recommend/reload")
            .methods("GET"_method)([]
                                   {
        try {
            const char* path = std::getenv("PRODUCT_JSON_PATH");
            if (!path) {
                throw std::runtime_error("PRODUCT_JSON_PATH non défini !");
            }

            g_productCache = std::make_unique<ProductCache>(
                path,
                []() -> std::vector<Product> { return {}; },
                [](const std::vector<Product>& products) {
                    nlohmann::json j;
                    j["data"] = nlohmann::json::array();
                    for (const auto& p : products)
                        j["data"].push_back(p.toJson());
                    return j;
                },
                [](const nlohmann::json& json) {
                    std::vector<Product> products;
                    if (!json.contains("data") || !json["data"].is_array()) {
                        throw std::runtime_error("Clé 'data' manquante ou invalide (attendu : tableau JSON)");
                    }

                    for (const auto& item : json["data"]) {
                        try {
                            products.push_back(ProductFactory::fromJsonOrThrow(item));
                        } catch (const std::exception& e) {
                            std::cerr << "⚠️ Produit ignoré : " << e.what() << std::endl;
                        }
                    }

                    return products;
                }
            );

            g_productCache->reload();

            // std::cout << "[ProductController] Cache produit rechargé depuis le fichier JSON.\n";
            return crow::response(R"({"status":"success","message":"Cache produit rechargé avec succès"})");

        } catch (const std::exception& e) {
            return crow::response(500, R"({"status":"error","message":"Erreur : )" + std::string(e.what()) + R"("})");
        } });

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
