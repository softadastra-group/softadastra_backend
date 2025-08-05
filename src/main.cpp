#include <iostream>
#include <string>
#include <vector>
#include <crow.h>

#include <softadastra/commerce/products/ProductController.hpp>
#include <softadastra/commerce/categories/CategoryController.hpp>
#include <softadastra/commerce/colors/ColorController.hpp>

#include <adastra/config/env/EnvBoot.hpp>
#include <adastra/config/env/EnvLoader.hpp>

using namespace softadastra::commerce::product;

int main()
{
    adastra::config::env::loadDotEnv("../.env");
    int port = adastra::config::env::EnvLoader::getInt("SERVER_PORT", 18080);
    int threads = adastra::config::env::EnvLoader::getInt("SERVER_THREADS", 4);

    std::cout << "🟢 Backend Softadastra sur le port " << port
              << ", " << threads << " threads..." << std::endl;
    crow::App<crow::CORSHandler> app;

    auto &cors = app.get_middleware<crow::CORSHandler>();
    cors
        .global()
        .headers("Content-Type", "Authorization")
        .methods("GET"_method, "POST"_method, "PUT"_method, "DELETE"_method, "OPTIONS"_method)
        .max_age(86400);

    softadastra::commerce::product::ProductController(app);
    softadastra::commerce::categories::CategoryController(app);
    softadastra::commerce::colors::ColorController(app);

    app.port(port).concurrency(threads).run();

    return 0;
}
