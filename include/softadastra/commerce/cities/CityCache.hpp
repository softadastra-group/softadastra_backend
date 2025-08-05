#ifndef CITY_CACHE_HPP
#define CITY_CACHE_HPP

#include <softadastra/core/cache/GenericCache.hpp>
#include <softadastra/commerce/cities/City.hpp>

namespace softadastra::commerce::cities
{
    using CityCache = softadastra::core::cache::GenericCache<City>;
}

#endif