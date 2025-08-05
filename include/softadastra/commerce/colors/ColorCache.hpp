#ifndef COLOR_CACHE_HPP
#define COLOR_CACHE_HPP

#include <softadastra/core/cache/GenericCache.hpp>
#include <softadastra/commerce/colors/Color.hpp>

namespace softadastra::commerce::colors
{
    using ColorCache = softadastra::core::cache::GenericCache<Color>;
}

#endif