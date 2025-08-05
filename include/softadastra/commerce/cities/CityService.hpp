#ifndef CITY_SERVICE_HPP
#define CITY_SERVICE_HPP

#include <softadastra/commerce/cities/CityRepositoryJson.hpp>

#include <string>

namespace softadastra::commerce::cities
{
    class CityService
    {
    public:
        explicit CityService(const std::string &filePath);
        std::vector<City> getAll() const;

    private:
        CityRepositoryJson repository;
    };
}

#endif