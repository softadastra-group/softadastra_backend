#ifndef ENV_LOADER_HPP
#define ENV_LOADER_HPP

#include <string>
#include <cstdlib>
#include <stdexcept>
#include <sstream>
#include <algorithm>

namespace adastra::config::env
{
    class EnvLoader
    {
    public:
        // Récupère une variable requise ou lance une exception
        static std::string require(const std::string &key)
        {
            const char *val = std::getenv(key.c_str());
            if (!val)
            {
                throw std::runtime_error("La variable d'environnement '" + key + "' est requise mais non définie.");
            }
            return std::string(val);
        }

        // Récupère une variable avec une valeur par défaut si elle n'existe pas
        static std::string get(const std::string &key, const std::string &defaultValue = "")
        {
            const char *val = std::getenv(key.c_str());
            return val ? std::string(val) : defaultValue;
        }

        // Version typée pour int
        static int getInt(const std::string &key, int defaultValue = 0)
        {
            const char *val = std::getenv(key.c_str());
            if (!val)
                return defaultValue;

            return std::stoi(val);
        }

        // Version typée pour bool (1, true, oui → true)
        static bool getBool(const std::string &key, bool defaultValue = false)
        {
            const char *val = std::getenv(key.c_str());
            if (!val)
                return defaultValue;

            std::string s = val;
            std::transform(s.begin(), s.end(), s.begin(), ::tolower);
            return (s == "1" || s == "true" || s == "yes" || s == "oui");
        }
    };
}

#endif // ENV_LOADER_HPP
