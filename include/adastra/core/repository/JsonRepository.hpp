#ifndef JSON_REPOSITORY_HPP
#define JSON_REPOSITORY_HPP

#include <string>
#include <vector>
#include <mutex>
#include <optional>
#include <adastra/utils/json/JsonUtils.hpp>

namespace adastra::core::repository
{
    template <typename T>
    class JsonRepository
    {
    public:
        JsonRepository(const std::string &filePath, const std::string &sectionKey)
            : path_(filePath), key_(sectionKey), isLoaded_(false) {}

        const std::vector<T> &getAll() const
        {
            std::lock_guard<std::mutex> lock(mutex_);

            if (!isLoaded_)
            {
                data_ = adastra::utils::json::loadVectorFromJsonFile<T>(path_, key_);
                isLoaded_ = true;
            }

            return data_;
        }

        void reload()
        {
            std::lock_guard<std::mutex> lock(mutex_);
            data_ = adastra::utils::json::loadVectorFromJsonFile<T>(path_, key_);
            isLoaded_ = true;
        }

    private:
        std::string path_;
        std::string key_;
        mutable std::vector<T> data_;
        mutable bool isLoaded_;
        mutable std::mutex mutex_;
    };
}

#endif // JSON_REPOSITORY_HPP
