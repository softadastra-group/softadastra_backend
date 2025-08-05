#include <softadastra/commerce/colors/ColorServiceFromCache.hpp>

namespace softadastra::commerce::colors
{
    ColorServiceFromCache::ColorServiceFromCache(const std::vector<Color> &colors)
        : data_(colors) {}

    std::vector<Color> ColorServiceFromCache::getAllColors() const
    {
        return data_;
    }
}