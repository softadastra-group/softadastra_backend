#include "adastra/utils/string/StringUtils.hpp"
#include <algorithm>

std::string adastra::utils::to_upper(const std::string& input) {
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}
