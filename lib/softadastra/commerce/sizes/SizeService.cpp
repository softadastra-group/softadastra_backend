#include <softadastra/commerce/sizes/SizeService.hpp>

namespace softadastra::commerce::sizes
{
    SizeService::SizeService(const std::string &jsonPath)
        : repository(jsonPath) {}

    std::vector<Size> SizeService::getAllSizes() const
    {
        return repository.getAllSizes();
    }
}