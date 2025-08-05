#ifndef JSON_FILE_LOADER_HPP
#define JSON_FILE_LOADER_HPP

#include <nlohmann/json.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <unordered_map>
#include <mutex>

namespace adastra::utils::json
{
    using nlohmann::json;

    class JsonFileLoader
    {
    public:
        static json loadJsonFromFile(const std::string &path)
        {
            std::lock_guard<std::mutex> lock(cache_mutex_);

            auto it = cache_.find(path);
            if (it != cache_.end())
            {
                return it->second;
            }

            std::ifstream file(path);
            if (!file.is_open())
            {
                throw std::runtime_error("Impossible d'ouvrir le fichier JSON : " + path);
            }

            std::stringstream buffer;
            buffer << file.rdbuf();

            try
            {
                json parsed = json::parse(buffer.str());
                cache_[path] = parsed;
                return parsed;
            }
            catch (const json::parse_error &e)
            {
                throw std::runtime_error("Erreur de parsing JSON : " + std::string(e.what()));
            }
        }

        static void saveJsonToFile(const std::string &path, const json &data)
        {
            std::ofstream file(path);
            if (!file.is_open())
            {
                throw std::runtime_error("Impossible d’écrire dans le fichier JSON : " + path);
            }

            file << data.dump(4);
            file.close();

            std::lock_guard<std::mutex> lock(cache_mutex_);
            cache_[path] = data;
        }

        static json loadJsonSection(const std::string &path, const std::string &key)
        {
            json j = loadJsonFromFile(path);
            if (!j.contains(key))
            {
                throw std::runtime_error("Clé '" + key + "' manquante dans : " + path);
            }

            return j[key];
        }

        static void clearCache()
        {
            std::lock_guard<std::mutex> lock(cache_mutex_);
            cache_.clear();
        }

    private:
        static inline std::unordered_map<std::string, json> cache_;
        static inline std::mutex cache_mutex_;
    };
}

#endif // JSON_FILE_LOADER_HPP
