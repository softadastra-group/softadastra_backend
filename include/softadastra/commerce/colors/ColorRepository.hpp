#ifndef COLOR_REPOSITORY_HPP
#define COLOR_REPOSITORY_HPP

#include <softadastra/commerce/colors/Color.hpp>
#include <adastra/core/repository/JsonRepository.hpp>

namespace softadastra::commerce::colors
{
    using ColorRepository = adastra::core::repository::JsonRepository<Color>;
}

#endif // COLOR_REPOSITORY_HPP
