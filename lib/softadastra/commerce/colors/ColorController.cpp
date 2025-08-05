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
        std::string jsonPath = adastra::config::env::EnvLoader::require("COLORS_JSON_PATH_ALL");

        std::call_once(init_flag, [&]()
                       {
            std::vector<Color> loaded = ColorService(jsonPath).getAllColors();
            std::cout << "✅ Couleurs chargées : " << loaded.size() << "\n";

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
    }
}
