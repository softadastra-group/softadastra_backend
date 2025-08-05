#ifndef COLOR_BUILDER_HPP
#define COLOR_BUILDER_HPP

#include <softadastra/commerce/colors/Color.hpp>

namespace softadastra::commerce::colors
{
    class ColorBuilder
    {
    private:
        Color color;

    public:
        ColorBuilder &setId(std::uint32_t id)
        {
            color.setId(id);
            return *this;
        }

        ColorBuilder &setName(const std::string &name)
        {
            color.setName(name);
            return *this;
        }

        Color build() const
        {
            return color;
        }
    };
}

#endif