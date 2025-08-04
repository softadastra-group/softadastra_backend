#ifndef PRODUCT_CACHE_HPP
#define PRODUCT_CACHE_HPP

#include <softadastra/core/cache/GenericCache.hpp>
#include <softadastra/commerce/products/Product.hpp>

namespace softadastra::commerce::product
{
    using ProductCache = softadastra::core::cache::GenericCache<Product>;
}

#endif // PRODUCT_CACHE_HPP
