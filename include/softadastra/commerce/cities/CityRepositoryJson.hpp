#ifndef CITY_REPOSITORY_HPP
#define CITY_REPOSITORY_HPP

#include <softadastra/commerce/cities/City.hpp>
#include <adastra/core/repository/JsonRepository.hpp>

namespace softadastra::commerce::cities
{
    using CityRepositoryJson = adastra::core::repository::JsonRepository<City>;
}

#endif // CITY_REPOSITORY_HPP
