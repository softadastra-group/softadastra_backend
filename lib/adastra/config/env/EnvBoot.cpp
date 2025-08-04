#include <adastra/config/env/EnvBoot.hpp>
#include <cstdlib>
#include <fstream>

namespace adastra::config::env
{
    void loadDotEnv(const std::string &filepath)
    {
        std::ifstream file(filepath);
        if (!file.is_open())
            return;

        std::string line;
        while (std::getline(file, line))
        {
            if (line.empty() || line[0] == '#')
                continue;

            auto delim = line.find('=');
            if (delim == std::string::npos)
                continue;

            std::string key = line.substr(0, delim);
            std::string value = line.substr(delim + 1);

            setenv(key.c_str(), value.c_str(), 1); // overwrite = true
        }
    }
}
