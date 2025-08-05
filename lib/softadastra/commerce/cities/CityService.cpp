#include <softadastra/commerce/cities/CityService.hpp>

namespace softadastra::commerce::cities
{
    CityService::CityService(const std::string &filePath)
        : repository(filePath, "cities") {}

    std::vector<City> CityService::getAll() const
    {
        return repository.getAll();
    }
}