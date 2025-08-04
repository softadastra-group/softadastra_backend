#ifndef ENV_BOOT_HPP
#define ENV_BOOT_HPP

#include <string>

namespace adastra::config::env
{
    void loadDotEnv(const std::string &filepath = ".env");
}

#endif // ENV_BOOT_HPP
