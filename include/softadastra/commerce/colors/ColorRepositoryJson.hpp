#ifndef COLOR_REPOSITORY_JSON_HPP
#define COLOR_REPOSITORY_JSON_HPP

#include <softadastra/commerce/colors/Color.hpp>

#include <string>
#include <vector>

namespace softadastra::commerce::colors
{
    class ColorRepositoryJson
    {
    public:
        explicit ColorRepositoryJson(const std::string &filePath);
        std::vector<Color> getAllColors() const;

    private:
        std::string jsonFilePath;
    };
}

#endif