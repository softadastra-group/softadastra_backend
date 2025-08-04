#include <iostream>
#include <string>
#include <vector>
#include <crow.h>

#include <adastra/core/Core.hpp>
#include <softadastra/shop/ShopManager.hpp>
#include <softadastra/chat/ChatModule.hpp>

using namespace adastra::core::algorithms;

template <typename T>
void print(const std::vector<T> &v)
{
    std::cout << "---------------------" << std::endl;
    for (auto pos = v.begin(); pos != v.end(); ++pos)
    {
        if (pos != v.begin())
        {
            std::cout << ", ";
        }
        std::cout << *pos;
    }
    std::cout << std::endl;
}

int main()
{
    softadastra::shop::ShopManager manager;
    std::cout << "🟢 Backend Softadastra lancé..." << std::endl;
    std::cout << "📦 " << manager.getWelcomeMessage() << std::endl;

    crow::SimpleApp app;

    // ✅ Route de test : GET /api/hello
    CROW_ROUTE(app, "/api/hello").methods("GET"_method)([]
                                                        {
        crow::json::wvalue response;
        response["status"] = "ok";
        response["message"] = "Hello from Softadastra API 🚀";
        return response; });

    // 🚀 Lancer le serveur
    app.port(8080).multithreaded().run();

    return 0;
}
