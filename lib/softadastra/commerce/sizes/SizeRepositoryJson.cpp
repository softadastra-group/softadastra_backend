#include <softadastra/commerce/sizes/SizeRepositoryJson.hpp>
#include <adastra/utils/string/StringUtils.hpp>

#include <fstream>
#include <sstream>
#include <stdexcept>

#include <nlohmann/json.hpp>

using namespace adastra::utils::string;

namespace softadastra::commerce::sizes
{
    SizeRepository::SizeRepository(const std::string &filePath)
        : jsonFilePath(filePath) {}

    std::vector<Size> SizeRepository::getAllSizes() const
    {
        std::fstream file(jsonFilePath);
        if (!file.is_open())
        {
            throw std::runtime_error("Impossible d'ouvrir le JSON : " + jsonFilePath);
        }

        std::stringstream buffer;
        buffer << file.rdbuf();

        nlohmann::json j = json::parse(buffer.str());

        if (!j.contains("sizes") || !j["sizes"].is_array())
        {
            throw std::runtime_error("La cle 'sizes' manquante ou invalid");
        }

        const auto &all = j["sizes"];
        std::vector<Size> result;

        for (const auto &color : all)
        {
            if (!color.contains("id") || !color.contains("name"))
            {
                continue;
            }

            Size s(formatDisplayName(color["name"]));
            s.setId(color["id"].get<std::uint32_t>());

            result.push_back(s);
        }

        return result;
    }
}