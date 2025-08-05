#include <softadastra/commerce/cities/CityController.hpp>
#include <softadastra/commerce/cities/City.hpp>
#include <softadastra/commerce/cities/CityService.hpp>
#include <softadastra/commerce/cities/CityCache.hpp>

#include <adastra/config/env/EnvLoader.hpp>
#include <adastra/utils/json/JsonUtils.hpp>

#include <nlohmann/json.hpp>
#include <vector>

using namespace adastra::config::env;
using namespace adastra::utils::json;
using json = nlohmann::json;

namespace softadastra::commerce::cities
{
    static std::unique_ptr<CityCache> g_cityCache;
    static std::once_flag init_flag;

    void CityController(crow::App<crow::CORSHandler> &app)
    {
        std::string jsonPath = EnvLoader::require("CITY_JSON_PATH_ALL");

        std::call_once(init_flag,
                       [&]()
                       { 
            std::vector<City> loaded = CityService(jsonPath).getAll(); 
            g_cityCache = std::make_unique<CityCache>(
                jsonPath,
                [loaded]() -> std::vector<City>{
                    return loaded;
                },
                [](const std::vector<City>& cities){
                    return serializeVector("cities", cities);
                },
                [](const json& j){
                    return deserializeVector<City>(j, "cities");
                }
            ); 
        g_cityCache->getJson(); });

        CROW_ROUTE(app, "/api/cities/all")
        ([]
         {
            auto& cache = *g_cityCache;
            const std::string responseStr = cache.getJson();
            
            crow::response res(responseStr);
            res.set_header("Content-type", "application/json");
            res.set_header("Cache-Control", "public, max-age=60");

            return res; });
    }
}