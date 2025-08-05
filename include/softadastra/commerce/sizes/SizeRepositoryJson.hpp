#ifndef SIZE_REPOSITORY_HPP
#define SIZE_REPOSITORY_HPP

#include <softadastra/commerce/sizes/Size.hpp>

#include <string>
#include <vector>

namespace softadastra::commerce::sizes
{
    class SizeRepository
    {
    public:
        explicit SizeRepository(const std::string &filePath);
        std::vector<Size> getAllSizes() const;

    private:
        std::string jsonFilePath;
    };
}

#endif