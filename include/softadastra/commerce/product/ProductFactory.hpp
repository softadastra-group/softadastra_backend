#ifndef PRODUCT_FACTORY_HPP
#define PRODUCT_FACTORY_HPP

#include <memory>
#include <nlohmann/json.hpp>
#include <softadastra/commerce/product/Product.hpp>

namespace softadastra::commerce::product
{
    class ProductFactory
    {
    public:
        static std::unique_ptr<Product> createFromJson(const nlohmann::json &data);
    };
}

#endif // PRODUCT_FACTORY_HPP
