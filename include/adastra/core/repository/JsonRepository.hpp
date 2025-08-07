#ifndef JSON_REPOSITORY_HPP
#define JSON_REPOSITORY_HPP

#include <string>
#include <vector>
#include <mutex>
#include <optional>
#include <fstream>
#include <nlohmann/json.hpp>
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
            loadIfNeeded();
            return data_;
        }

        void reload()
        {
            std::lock_guard<std::mutex> lock(mutex_);
            data_ = adastra::utils::json::loadVectorFromJsonFile<T>(path_, key_);
            isLoaded_ = true;
        }

        void add(const T &item)
        {
            std::lock_guard<std::mutex> lock(mutex_);
            loadIfNeeded();
            data_.push_back(item);
        }

        void flush() const
        {
            std::lock_guard<std::mutex> lock(mutex_);
            nlohmann::json root;
            root[key_] = nlohmann::json::array();
            for (const auto &item : data_)
            {
                root[key_].push_back(item.toJson());
            }

            std::ofstream out(path_);
            if (!out)
            {
                throw std::runtime_error("Erreur lors de l'ouverture du fichier JSON en écriture : " + path_);
            }

            out << root.dump(2);
        }

    private:
        void loadIfNeeded() const
        {
            if (!isLoaded_)
            {
                data_ = adastra::utils::json::loadVectorFromJsonFile<T>(path_, key_);
                isLoaded_ = true;
            }
        }

        std::string path_;
        std::string key_;
        mutable std::vector<T> data_;
        mutable bool isLoaded_;
        mutable std::mutex mutex_;
    };
}

#endif // JSON_REPOSITORY_HPP
