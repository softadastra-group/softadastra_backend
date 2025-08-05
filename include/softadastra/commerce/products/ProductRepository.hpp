#ifndef PRODUCT_REPOSITORY_HPP
#define PRODUCT_REPOSITORY_HPP

#include <adastra/core/repository/JsonRepository.hpp>
#include <softadastra/commerce/products/Product.hpp>

namespace softadastra::commerce::product
{
    using ProductRepository = adastra::core::repository::JsonRepository<Product>;
}

#endif // PRODUCT_REPOSITORY_HPP
