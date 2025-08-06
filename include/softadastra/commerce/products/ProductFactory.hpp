#ifndef PRODUCT_FACTORY_HPP
#define PRODUCT_FACTORY_HPP

#include <softadastra/commerce/products/Product.hpp>

#include <memory>
#include <nlohmann/json.hpp>

namespace softadastra::commerce::products
{
    class ProductFactory
    {
    public:
        static std::unique_ptr<Product> createFromJson(const nlohmann::json &data);
        static Product fromJsonOrThrow(const nlohmann::json &data);
    };
}

#endif // PRODUCT_FACTORY_HPP
