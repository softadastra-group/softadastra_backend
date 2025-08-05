#include <softadastra/commerce/colors/ColorController.hpp>
#include <softadastra/commerce/colors/ColorCache.hpp>
#include <softadastra/commerce/colors/ColorService.hpp>
#include <softadastra/commerce/colors/ColorServiceFromCache.hpp>

#include <adastra/config/env/EnvLoader.hpp>
#include <adastra/utils/json/JsonUtils.hpp>

using namespace adastra::utils::json;

namespace softadastra::commerce::colors
{
    static std::unique_ptr<ColorCache> g_colorCache;
    static std::once_flag init_flag;

    void ColorController(crow::App<crow::CORSHandler> &app)
    {
        std::string jsonPath = adastra::config::env::EnvLoader::require("COLOR_JSON_PATH_ALL");

        std::call_once(init_flag, [&]()
                       {
            std::vector<Color> loaded = ColorService(jsonPath).getAllColors();
            std::cout << "Couleurs chargées : " << loaded.size() << "\n";

            g_colorCache = std::make_unique<ColorCache>(
                jsonPath,
                [loaded]() -> std::vector<Color>
                {
                    return loaded;
                },
                [](const std::vector<Color> &colors)
                {
                    return serializeVector("colors", colors);
                },
                [](const nlohmann::json &j)
                {
                    return deserializeVector<Color>(j, "colors");
                });

            g_colorCache->getJson(); });

        CROW_ROUTE(app, "/api/colors/all")
        ([]
         {
            try{
                auto& cache = *g_colorCache;
                const std::string responseStr = cache.getJson();

                crow::response res(responseStr);
                res.set_header("Content-type", "application/json");
                res.set_header("Cache-Control", "public, max-age=60");
                return res;
            }catch(const std::exception& e){
                return crow::response(500, std::string("Erreur : ") + e.what());
            } });

        CROW_ROUTE(app, "/api/colors/id/<int>")
        ([](int id)
         {
            try
            {
                ColorServiceFromCache service(*g_colorCache);
                auto colorOpt = service.findById(id);

                if (!colorOpt.has_value())
                    return crow::response(404, "Color not found");

                crow::response res(colorOpt->toJson().dump());
                res.set_header("Content-Type", "application/json");
                return res;
            }
            catch (const std::exception &e)
            {
                return crow::response(500, std::string("Erreur : ") + e.what());
            } });

        CROW_ROUTE(app, "/api/colors/name/<string>")
        ([](const std::string &name)
         {
            try
            {
                ColorServiceFromCache service(*g_colorCache);
                auto colorOpt = service.findByName(name);

                if (!colorOpt.has_value())
                    return crow::response(404, "Color not found");

                crow::response res(colorOpt->toJson().dump());
                res.set_header("Content-Type", "application/json");
                return res;
            }
            catch (const std::exception &e)
            {
                return crow::response(500, std::string("Erreur : ") + e.what());
            } });
    }

}
