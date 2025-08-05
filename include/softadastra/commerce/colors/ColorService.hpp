#ifndef COLOR_SERVICE_HPP
#define COLOR_SERVICE_HPP

#include <softadastra/commerce/colors/Color.hpp>
#include <softadastra/commerce/colors/ColorRepository.hpp>

namespace softadastra::commerce::colors
{
    class ColorService
    {
    public:
        explicit ColorService(const std::string &jsonPath);

        std::vector<Color> getAllColors() const;

    private:
        ColorRepository repository;
    };
}

#endif
