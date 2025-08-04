#include <iostream>
#include <string>
#include <vector>
#include <crow.h>

#include <adastra/core/Core.hpp>
#include <softadastra/shop/ShopManager.hpp>
#include <softadastra/chat/ChatModule.hpp>
#include <softadastra/commerce/product/ProductFactory.hpp>
#include <softadastra/commerce/product/ProductWithPromo.hpp>
#include <softadastra/commerce/product/DigitalProduct.hpp>

using namespace adastra::core::algorithms;
using namespace softadastra::commerce::product;

int main()
{
    softadastra::shop::ShopManager manager;
    std::cout << "🟢 Backend Softadastra lancé..." << std::endl;
    std::cout << "📦 " << manager.getWelcomeMessage() << std::endl;

    // 🛍 Produit avec promo
    nlohmann::json promoJson = {
        {"type", "promo"},
        {"title", "Sac de luxe"},
        {"formatted_price", "$99"},
        {"promo_text", "🔥 -50% aujourd'hui"},
        {"sizes", {"M"}},
        {"colors", {"black"}}};

    auto promoProduct = ProductFactory::createFromJson(promoJson);

    if (auto castedPromo = dynamic_cast<ProductWithPromo *>(promoProduct.get()))
    {
        std::cout << "🛒 Produit promo : " << castedPromo->getTitle()
                  << " — " << castedPromo->getFormattedPrice()
                  << " | Promo: " << castedPromo->getPromoText() << "\n";
    }

    // 📘 Produit numérique
    nlohmann::json digitalJson = {
        {"type", "digital"},
        {"title", "Guide PDF de Softadastra"},
        {"formatted_price", "$5"},
        {"download_url", "https://softadastra.com/files/ebook.pdf"},
        {"sizes", nlohmann::json::array()},
        {"colors", nlohmann::json::array()}};

    auto digitalProduct = ProductFactory::createFromJson(digitalJson);

    if (auto castedDigital = dynamic_cast<DigitalProduct *>(digitalProduct.get()))
    {
        std::cout << "📘 Produit digital : " << castedDigital->getTitle()
                  << " — " << castedDigital->getFormattedPrice()
                  << " | Lien : " << castedDigital->getDownloadUrl() << "\n";
    }

    return 0;
}
