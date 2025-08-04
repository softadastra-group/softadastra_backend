#include <iostream>
#include <string>
#include <vector>
#include <crow.h>

#include <adastra/core/Core.hpp>
#include <softadastra/shop/ShopManager.hpp>
#include <softadastra/chat/ChatModule.hpp>
#include <softadastra/commerce/product/ProductBuilder.hpp>

#include <softadastra/commerce/product/ProductController.hpp>

using namespace adastra::core::algorithms;
using namespace softadastra::commerce::product;

int main()
{
    softadastra::shop::ShopManager manager;
    std::cout << "🟢 Backend Softadastra lancé..." << std::endl;
    std::cout << "📦 " << manager.getWelcomeMessage() << std::endl;

    crow::App<crow::CORSHandler> app;
    softadastra::commerce::product::registerProductController(app);

    return 0;
}
