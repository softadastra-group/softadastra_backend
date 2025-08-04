#ifndef PRODUCT_CACHE_HPP
#define PRODUCT_CACHE_HPP

#include <string>
#include <mutex>

namespace softadastra::commerce::product
{
    class ProductCache
    {
    public:
        explicit ProductCache(const std::string &jsonPath);

        std::string getJsonResponse();
        void reload();

    private:
        void loadProducts();
        void saveToCacheFile();
        bool loadFromCacheFile();

        std::string jsonFilePath;
        std::string cachedJson;
        bool isLoaded;
        std::mutex mutex;
    };
};

#endif // PRODUCT_CACHE_HPP
