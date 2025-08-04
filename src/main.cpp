#include <iostream>
#include <string>
#include <vector>
#include <crow.h>

#include <softadastra/commerce/product/ProductBuilder.hpp>
#include <softadastra/commerce/product/ProductController.hpp>
#include <adastra/config/env/EnvBoot.hpp>

using namespace softadastra::commerce::product;

int main()
{
    adastra::config::env::loadDotEnv("../.env");

    std::cout << "🟢 Backend Softadastra lancé..." << std::endl;
    crow::App<crow::CORSHandler> app;

    auto &cors = app.get_middleware<crow::CORSHandler>();
    cors
        .global()
        .headers("Content-Type", "Authorization")
        .methods("GET"_method, "POST"_method, "PUT"_method, "DELETE"_method, "OPTIONS"_method)
        .max_age(86400);

    softadastra::commerce::product::ProductController(app);

    app.port(18080).multithreaded().run();

    return 0;
}
