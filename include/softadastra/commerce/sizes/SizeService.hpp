#ifndef SIZE_SERVICE_HPP
#define SIZE_SERVICE_HPP

#include <softadastra/commerce/sizes/SizeRepositoryJson.hpp>

namespace softadastra::commerce::sizes
{
    class SizeService
    {
    public:
        SizeService(const std::string &jsonPath);
        std::vector<Size> getAllSizes() const;

    private:
        SizeRepository repository;
    };
}

#endif