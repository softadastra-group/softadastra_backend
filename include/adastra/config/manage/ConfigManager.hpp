#ifndef CONFIG_MANAGER_HPP
#define CONFIG_MANAGER_HPP

#include <mutex>
#include <map>
#include <string>

class ConfigManager
{
private:
    ConfigManager() = default;
    ~ConfigManager() = default;

    ConfigManager(const ConfigManager &) = delete;
    ConfigManager &operator=(const ConfigManager &) = delete;

    mutable std::mutex mutex;
    std::map<std::string, std::string> params;

public:
    static ConfigManager &getInstance();
    void set(const std::string &key, const std::string &value);
    std::string get(const std::string &key) const;
};

#endif