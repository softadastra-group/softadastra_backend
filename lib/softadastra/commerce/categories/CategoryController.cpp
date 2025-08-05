#include <softadastra/commerce/categories/CategoryController.hpp>
#include <softadastra/commerce/categories/CategoryCache.hpp>
#include <softadastra/commerce/categories/CategoryService.hpp>
#include <softadastra/commerce/categories/CategoryServiceFromCache.hpp>
#include <softadastra/commerce/categories/CategoryJsonParser.hpp>

#include <adastra/config/env/EnvLoader.hpp>

#include <nlohmann/json.hpp>
#include <memory>
#include <mutex>
#include <iostream>

namespace softadastra::commerce::categories
{
    static std::unique_ptr<CategoryCache> g_categoryCache;
    static std::once_flag init_flag;

    void CategoryController(crow::App<crow::CORSHandler> &app)
    {
        const std::string jsonPathAll = adastra::config::env::EnvLoader::require("CATEGORY_JSON_PATH_ALL");

        std::call_once(init_flag, [&]()
                       {
            std::vector<Category> loaded = CategoryService(jsonPathAll).getAllCategories();
            std::cout << "📦 Catégories chargées à l'initialisation : " << loaded.size() << "\n";

            g_categoryCache = std::make_unique<CategoryCache>(
                jsonPathAll,
                [loaded]() -> std::vector<Category> {
                    return loaded;
                },
                [](const std::vector<Category>& categories) -> nlohmann::json {
                    nlohmann::json j;
                    j["categories"] = nlohmann::json::array();
                    for (const auto& c : categories) {
                        nlohmann::json item = {
                            {"id", c.getId()},
                            {"name", c.getName()},
                            {"image_url", c.getImageUrl()},
                            {"product_count", c.getProductCount()}
                        };

                        if (c.getParentId().has_value())
                            item["parent_id"] = c.getParentId().value();
                        else
                            item["parent_id"] = nullptr;

                        j["categories"].push_back(item);
                    }
                    return j;
                },
                parseCategoryJson 
            );

            g_categoryCache->getJson(); // warm-up
            std::cout << "✅ [CategoryController] Cache initialisé à partir de all_categories.json\n"; });

        CROW_ROUTE(app, "/api/categories/all")
        ([]
         {
            try {
                auto& cache = *g_categoryCache;
                std::string responseStr = cache.getJson();

                crow::response res(responseStr);
                res.set_header("Content-Type", "application/json");
                res.set_header("Cache-Control", "public, max-age=60");
                return res;
            } catch (const std::exception& e) {
                return crow::response(500, std::string("Erreur : ") + e.what());
            } });

        CROW_ROUTE(app, "/api/categories/reload").methods("POST"_method)([]
                                                                         {
            try {
                if (!g_categoryCache)
                    return crow::response(500, "Cache non initialisé");

                g_categoryCache->reload();
                std::cout << "[CategoryController] Cache rechargé.\n";
                return crow::response(200, "Cache rechargé avec succès");
            } catch (const std::exception& e) {
                return crow::response(500, std::string("Erreur lors du rechargement : ") + e.what());
            } });

        CROW_ROUTE(app, "/api/categories/status")
        ([]
         {
            if (!g_categoryCache)
                return crow::response(500, "Cache non initialisé");

            try {
                std::string jsonStr = g_categoryCache->getJson();
                nlohmann::json parsed = nlohmann::json::parse(jsonStr);
                size_t total = parsed["categories"].size();

                nlohmann::json status = {
                    {"status", "🟢 OK"},
                    {"categories", total},
                    {"json_size", jsonStr.size()},
                    {"message", "Le cache est chargé et prêt."}
                };

                crow::response res(status.dump(2));
                res.set_header("Content-Type", "application/json");
                res.set_header("Cache-Control", "public, max-age=30");
                return res;
            } catch (const std::exception& e) {
                return crow::response(500, std::string("Erreur diagnostic : ") + e.what());
            } });

        CROW_ROUTE(app, "/api/categories/top")
        ([]
         {
            try {
                if (!g_categoryCache)
                    throw std::runtime_error("Cache non initialisé");

                const auto& all = g_categoryCache->getAll();

                softadastra::commerce::categories::CategoryServiceFromCache service(all);
                auto top = service.getTopLevelCategories();

                nlohmann::json j;
                j["categories"] = nlohmann::json::array();

                for (const auto& c : top) {
                    j["categories"].push_back({
                        {"id", c.getId()},
                        {"name", c.getName()},
                        {"image", c.getImageUrl()},
                        {"product_count", c.getProductCount()},
                        {"parent_id", nullptr}
                    });
                }

                crow::response res(j.dump(2));
                res.set_header("Content-Type", "application/json");
                res.set_header("Cache-Control", "public, max-age=60");
                return res;

            } catch (const std::exception& e) {
                return crow::response(500, std::string("Erreur top-level : ") + e.what());
            } });

        CROW_ROUTE(app, "/api/categories/leaf")
        ([]
         {
            try {
                if (!g_categoryCache)
                    throw std::runtime_error("Cache non initialisé");

                const auto& all = g_categoryCache->getAll();

                softadastra::commerce::categories::CategoryServiceFromCache service(all);
                auto leaves = service.getLeafCategories();

                nlohmann::json j;
                j["categories"] = nlohmann::json::array();

                for (const auto& c : leaves) {
                    nlohmann::json item = {
                        {"id", c.getId()},
                        {"name", c.getName()},
                        {"image", c.getImageUrl()},
                        {"product_count", c.getProductCount()}
                    };

                    if (c.getParentId().has_value())
                        item["parent_id"] = c.getParentId().value();
                    else
                        item["parent_id"] = nullptr;

                    j["categories"].push_back(item);
                }

                crow::response res(j.dump(2));
                res.set_header("Content-Type", "application/json");
                res.set_header("Cache-Control", "public, max-age=60");
                return res;

            } catch (const std::exception& e) {
                return crow::response(500, std::string("Erreur leaf-categories : ") + e.what());
            } });

        CROW_ROUTE(app, "/api/categories")
        ([]
         {
            nlohmann::json doc = {
                {"endpoints", {
                    {
                        {"method", "GET"},
                        {"path", "/api/categories"},
                        {"description", "Mini doc des routes catégories"}
                    },
                    {
                        {"method", "GET"},
                        {"path", "/api/categories/all"},
                        {"description", "Toutes les catégories depuis le cache"}
                    },
                    {
                        {"method", "POST"},
                        {"path", "/api/categories/reload"},
                        {"description", "Recharge les catégories depuis le fichier JSON"}
                    },
                    {
                        {"method", "GET"},
                        {"path", "/api/categories/status"},
                        {"description", "Statut du cache catégorie"}
                    },
                    {
                        {"method", "GET"},
                        {"path", "/api/categories/leaf"},
                        {"description", "Toutes les sous-catégories finales (leaf)"}
                    },
                    {
                        {"method", "GET"},
                        {"path", "/api/categories/top"},
                        {"description", "Catégories top-level (racines sans parent)"}
                    }
                }}
            };

            crow::response res(doc.dump(2));
            res.set_header("Content-Type", "application/json");
            return res; });
    }
}
