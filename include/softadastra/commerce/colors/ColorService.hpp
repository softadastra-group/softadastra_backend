#ifndef COLOR_SERVICE_HPP
#define COLOR_SERVICE_HPP

#include <softadastra/commerce/colors/ColorRepositoryJson.hpp>

namespace softadastra::commerce::colors
{
    class ColorService
    {
    public:
        explicit ColorService(const std::string &jsonPath);

        std::vector<Color> getAllColors() const;

    private:
        ColorRepositoryJson repository;
    };
}

#endif