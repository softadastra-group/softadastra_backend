#ifndef COLOR_SERVICE_FROM_CACHE_HPP
#define COLOR_SERVICE_FROM_CACHE_HPP

#include <softadastra/commerce/colors/Color.hpp>
#include <vector>

namespace softadastra::commerce::colors
{
    class ColorServiceFromCache
    {
    public:
        explicit ColorServiceFromCache(const std::vector<Color> &colors);
        std::vector<Color> getAllColors() const;

    private:
        std::vector<Color> data_;
    };

}

#endif