#ifndef PRODUCT_SERVICE_HPP
#define PRODUCT_SERVICE_HPP

#include <softadastra/commerce/products/Product.hpp>
#include <softadastra/commerce/products/ProductRepository.hpp>
#include <vector>
#include <string>

namespace softadastra::commerce::product
{
    class ProductService
    {
    public:
        explicit ProductService(const std::string &jsonPath);

        std::vector<Product> getAllProducts() const;
        void reload();

    private:
        mutable ProductRepository repo;
    };
}

#endif
