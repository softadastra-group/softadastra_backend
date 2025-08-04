#ifndef PRODUCT_SERVICE_HPP
#define PRODUCT_SERVICE_HPP

#include "Product.hpp"
#include <vector>
#include <string>

namespace softadastra::commerce::product
{
    class ProductService
    {
    public:
        ProductService(const std::string &jsonPath);
        std::vector<Product> getAllProducts();

    private:
        std::string jsonFilePath;
    };
};

#endif
