#ifndef GENERIC_CACHE_HPP
#define GENERIC_CACHE_HPP

#include <string>
#include <vector>
#include <functional>
#include <mutex>
#include <fstream>
#include <nlohmann/json.hpp>
#include <filesystem>
#include <iostream>

namespace softadastra::core::cache
{
    template <typename T>
    class GenericCache
    {
    public:
        GenericCache(const std::string &cacheFilePath,
                     std::function<std::vector<T>()> loader,
                     std::function<nlohmann::json(const std::vector<T> &)> serializer,
                     std::function<std::vector<T>(const nlohmann::json &)> deserializer = nullptr)
            : cachePath(cacheFilePath),
              loadData(loader),
              serialize(serializer),
              deserialize(deserializer),
              isLoaded(false) {}

        const std::vector<T> &getAll()
        {
            std::lock_guard<std::mutex> lock(mutex);
            if (!isLoaded)
            {
                load();
            }
            return data_;
        }

        std::string getJson()
        {
            std::lock_guard<std::mutex> lock(mutex);
            if (!isLoaded)
            {
                load();
            }
            return cachedJson;
        }

        void reload()
        {
            std::lock_guard<std::mutex> lock(mutex);

            if (!loadFromFile())
            {
                throw std::runtime_error("Échec du rechargement depuis le fichier cache : " + cachePath);
            }

            std::cout << "[GenericCache] 🔁 Cache rechargé depuis le fichier avec succès.\n";
        }

    private:
        std::string cachePath;
        std::string cachedJson;
        std::vector<T> data_;
        std::function<std::vector<T>()> loadData;
        std::function<nlohmann::json(const std::vector<T> &)> serialize;
        std::function<std::vector<T>(const nlohmann::json &)> deserialize;
        bool isLoaded;
        std::mutex mutex;

        void load(bool forceReload = false)
        {
            if (!forceReload && loadFromFile())
                return;

            // Charger à partir de la source (base de données, ou autre)
            data_ = loadData();

            if (serialize)
            {
                nlohmann::json jsonToSave = serialize(data_);
                cachedJson = jsonToSave.dump(2);
                saveToFile(); // on sauve seulement ce qu'on vient de charger manuellement
            }

            isLoaded = true;
        }

        bool loadFromFile()
        {
            std::cerr << "[Cache] 🔎 Chargement depuis : " << cachePath << "\n";

            if (!std::filesystem::exists(cachePath))
            {
                std::cerr << "[Cache] ❌ Fichier non trouvé\n";
                return false;
            }

            std::ifstream in(cachePath);
            if (!in.is_open())
            {
                std::cerr << "[Cache] ❌ Impossible d'ouvrir le fichier\n";
                return false;
            }

            std::string fileContent((std::istreambuf_iterator<char>(in)),
                                    std::istreambuf_iterator<char>());

            if (fileContent.empty())
            {
                std::cerr << "[Cache] ⚠️ Fichier vide\n";
                return false;
            }

            cachedJson = fileContent;

            try
            {
                auto j = nlohmann::json::parse(fileContent);
                if (deserialize)
                {
                    data_ = deserialize(j);
                }
                else
                {
                    std::cerr << "[Cache] ❌ Pas de fonction de désérialisation définie\n";
                    return false;
                }

                isLoaded = true;
                std::cerr << "[Cache] ✅ Cache rechargé depuis le fichier\n";
                return true;
            }
            catch (const std::exception &e)
            {
                std::cerr << "[Cache] ❌ Erreur de parsing JSON : " << e.what() << "\n";
                return false;
            }
        }

        void saveToFile()
        {
            if (serialize)
            {
                nlohmann::json jsonToSave = serialize(data_);
                cachedJson = jsonToSave.dump(2); // joli formatage pour debug

                std::ofstream out(cachePath, std::ios::out | std::ios::trunc);
                if (out.is_open())
                {
                    out.write(cachedJson.data(), cachedJson.size());
                    out.close();
                }
            }
        }
    };
}

#endif // GENERIC_CACHE_HPP
