#ifndef CATEGORY_CACHE_HPP
#define CATEGORY_CACHE_HPP

#include <softadastra/core/cache/GenericCache.hpp>
#include <softadastra/commerce/categories/Category.hpp>

namespace softadastra::commerce::categories
{
    using CategoryCache = softadastra::core::cache::GenericCache<Category>;
}

#endif // CATEGORY_CACHE_HPP
