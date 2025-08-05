#include <softadastra/commerce/colors/ColorService.hpp>

namespace softadastra::commerce::colors
{
    ColorService::ColorService(const std::string &jsonPath)
        : repository(jsonPath, "colors") {}

    std::vector<Color> ColorService::getAllColors() const
    {
        return repository.getAll();
    }

}