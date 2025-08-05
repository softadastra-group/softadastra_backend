#include <softadastra/commerce/colors/ColorRepositoryJson.hpp>
#include <adastra/utils/string/StringUtils.hpp>

#include <nlohmann/json.hpp>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>

using json = nlohmann::json;
using namespace adastra::utils::string;

namespace softadastra::commerce::colors
{
    ColorRepositoryJson::ColorRepositoryJson(const std::string &filePath)
        : jsonFilePath(filePath) {}

    std::vector<Color> ColorRepositoryJson::getAllColors() const
    {
        // Ouverture du fichier
        std::ifstream file(jsonFilePath);
        if (!file.is_open())
        {
            throw std::runtime_error("Impossible d'ouvrir le fichier JSON: " + jsonFilePath);
        }

        // Lecture complete du contenu
        std::stringstream buffer;
        buffer << file.rdbuf();
        json j = json::parse(buffer.str());

        // Verification de la structure
        if (!j.contains("colors") || !j["colors"].is_array())
        {
            throw std::runtime_error("La cle 'colors' manquante ou invalide");
        }

        // Acces aux donnees
        const auto &all = j["colors"];
        std::vector<Color> result;

        // Boucle sur chaque element
        for (const auto &item : all)
        {
            // Verification des champs necessaires
            if (!item.contains("id") || !item.contains("name"))
            {
                continue;
            }

            // Construction de l'objet Color
            Color color(formatDisplayName(item["name"]));
            // Affectation de l'ID
            color.setId(item["id"].get<std::uint32_t>());
            // Retour final
            result.push_back(color);
        }

        return result;
    }
}