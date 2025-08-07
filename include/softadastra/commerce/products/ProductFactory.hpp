#ifndef PRODUCT_FACTORY_HPP
#define PRODUCT_FACTORY_HPP

#include <memory>
#include <nlohmann/json.hpp>
#include <softadastra/commerce/products/Product.hpp>

namespace softadastra::commerce::products
{
    class ProductFactory
    {
    public:
        static std::unique_ptr<Product> createFromJson(const nlohmann::json &data);
        static std::unique_ptr<Product> createFromInternalJson(const nlohmann::json &data); // ✅ AJOUTER ICI
        static Product fromJsonOrThrow(const nlohmann::json &data);
    };
}

#endif
