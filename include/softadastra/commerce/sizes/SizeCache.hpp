#ifndef SIZE_CACHE_HPP
#define SIZE_CACHE_HPP

#include <softadastra/core/cache/GenericCache.hpp>
#include <softadastra/commerce/sizes/Size.hpp>

namespace softadastra::commerce::sizes
{
    using SizeCache = softadastra::core::cache::GenericCache<Size>;
}

#endif
