#include <softadastra/commerce/sizes/SizeController.hpp>
#include <softadastra/commerce/sizes/SizeCache.hpp>
#include <softadastra/commerce/sizes/SizeService.hpp>
#include <softadastra/commerce/sizes/SizeServiceFromCache.hpp>

#include <adastra/utils/string/StringUtils.hpp>
#include <adastra/config/env/EnvLoader.hpp>
#include <adastra/utils/json/JsonUtils.hpp>

#include <memory>

using namespace adastra::utils::json;

namespace softadastra::commerce::sizes
{
    static std::unique_ptr<SizeCache> g_sizeCache;
    static std::once_flag init_flag;

    void SizeController(crow::App<crow::CORSHandler> &app)
    {
        std::string jsonPath = adastra::config::env::EnvLoader::require("SIZE_JSON_PATH_ALL");

        std::call_once(init_flag, [&]()
                       {
            std::vector<Size> loaded = SizeService(jsonPath).getAllSizes();
            std::cout << "Size charges: " << loaded.size() << std::endl;

            g_sizeCache = std::make_unique<SizeCache>(
                jsonPath,
                [loaded]() -> std::vector<Size>{
                    return loaded;
                },
                [](const std::vector<Size>& sizes){
                    return serializeVector("sizes", sizes);
                },
                [](const nlohmann::json& j){
                    return deserializeVector<Size>(j, "sizes");
                });
                g_sizeCache->getJson(); });

        CROW_ROUTE(app, "/api/sizes/all")
        ([]
         {
            try
            {
                auto &cache = *g_sizeCache;
                const std::string response = cache.getJson();

                crow::response res(response);
                res.set_header("Content-type", "application/json");
                res.set_header("Cache-Control", "public, max-age=60");
                return res;
            }
            catch (const std::exception &e)
            {
                return crow::response(500, std::string("Erreur: ") + e.what());
            } });

        CROW_ROUTE(app, "/api/sizes/id/<int>")
        ([](int id)
         {
            try{
                SizeServiceFromCache service(*g_sizeCache);
                auto sizeOpt = service.findById(id);

                if(!sizeOpt.has_value()){
                    return crow::response(404, "Size not found");
                }

                crow::response res(sizeOpt->toJson().dump());
                res.set_header("Content-type", "application/json");
                return res;

            }catch(const std::exception& e){
                return crow::response(500, std::string("Erreur: ") + e.what());
            } });

        CROW_ROUTE(app, "/api/sizes/name/<string>")
        ([](const std::string &name)
         {
            try{
                SizeServiceFromCache service(*g_sizeCache);
                auto sizeOpt = service.findByName(name);

                if(!sizeOpt.has_value()){
                    return crow::response(404, "Size not found");
                }

                crow::response res(sizeOpt->toJson().dump());
                res.set_header("Content-type", "application/json");
                return res;

            }catch(const std::exception& e){
                return crow::response(500, std::string("Erreur: ") + e.what());
            } });
    }
}