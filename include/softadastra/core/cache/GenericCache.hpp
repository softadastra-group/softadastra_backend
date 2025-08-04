#ifndef GENERIC_CACHE_HPP
#define GENERIC_CACHE_HPP

#include <string>
#include <vector>
#include <functional>
#include <mutex>
#include <nlohmann/json.hpp>

namespace softadastra::core::cache
{
    template <typename T>
    class GenericCache
    {
    public:
        GenericCache(const std::string &cacheFilePath,
                     std::function<std::vector<T>()> loader,
                     std::function<nlohmann::json(const std::vector<T> &)> serializer)
            : cachePath(cacheFilePath),
              loadData(loader),
              serialize(serializer),
              isLoaded(false) {}

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
        std::function<std::vector<T>()> loadData;
        std::function<nlohmann::json(const std::vector<T> &)> serialize;
        bool isLoaded;
        std::mutex mutex;

        void load(bool forceReload = false)
        {
            if (!forceReload && loadFromFile())
                return;

            auto data = loadData();
            cachedJson = serialize(data).dump();
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

            cachedJson.assign((std::istreambuf_iterator<char>(in)),
                              std::istreambuf_iterator<char>());

            return !cachedJson.empty();
        }

        void saveToFile()
        {
            std::ofstream out(cachePath);
            if (out.is_open())
            {
                out << cachedJson;
            }
        }
    };
}

#endif // GENERIC_CACHE_HPP
