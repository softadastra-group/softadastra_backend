#include "adastra/config/manage/ConfigManager.hpp"

ConfigManager &ConfigManager::getInstance()
{
    static ConfigManager instance;
    return instance;
}

void ConfigManager::set(const std::string &key, const std::string &value)
{
    std::lock_guard<std::mutex> lock(mutex);
    params[key] = value;
}

std::string ConfigManager::get(const std::string &key) const
{
    std::lock_guard<std::mutex> lock(mutex);

    auto it = params.find(key);

    if (it != params.end())
    {
        return it->second;
    }

    return "";
}
