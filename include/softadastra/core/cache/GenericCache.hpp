#ifndef GENERIC_CACHE_HPP
#define GENERIC_CACHE_HPP

#include <string>
#include <vector>
#include <functional>
#include <mutex>
#include <fstream>
#include <nlohmann/json.hpp>
#include <filesystem>

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
            load(true);
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

            data_ = loadData();
            cachedJson = serialize(data_).dump();
            isLoaded = true;
            saveToFile();
        }

        bool loadFromFile()
        {
            if (!std::filesystem::exists(cachePath))
                return false;

            std::ifstream in(cachePath);
            if (!in.is_open())
                return false;

            std::string fileContent((std::istreambuf_iterator<char>(in)),
                                    std::istreambuf_iterator<char>());

            if (fileContent.empty())
                return false;

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
                    return false;
                }

                isLoaded = true;
                return true;
            }
            catch (...)
            {
                return false;
            }
        }

        void saveToFile()
        {
            std::ofstream out(cachePath, std::ios::out | std::ios::trunc);
            if (out.is_open())
            {
                out.write(cachedJson.data(), cachedJson.size());
                out.close();
            }
        }
    };
}

#endif // GENERIC_CACHE_HPP
