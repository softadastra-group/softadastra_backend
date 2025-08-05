#ifndef STRING_UTILS_HPP
#define STRING_UTILS_HPP

#include <string>
#include <algorithm>
#include <cctype>
#include <locale>

namespace adastra::utils::string
{
    // Supprime les espaces au début
    inline void ltrim(std::string &s)
    {
        s.erase(s.begin(),
                std::find_if(s.begin(), s.end(),
                             [](unsigned char ch)
                             { return !std::isspace(ch); }));
    }

    // Supprime les espaces à la fin
    inline void rtrim(std::string &s)
    {
        s.erase(
            std::find_if(s.rbegin(), s.rend(),
                         [](unsigned char ch)
                         { return !std::isspace(ch); })
                .base(),
            s.end());
    }

    // Supprime les espaces au début et à la fin
    inline void trim(std::string &s)
    {
        ltrim(s);
        rtrim(s);
    }

    // Convertit en minuscules
    inline void toLower(std::string &s)
    {
        std::transform(s.begin(), s.end(), s.begin(),
                       [](unsigned char c)
                       { return std::tolower(c); });
    }

    // Combine les deux : trim + toLower
    inline std::string trimAndToLower(const std::string &input)
    {
        std::string result = input;
        trim(result);
        toLower(result);
        return result;
    }

    // ✅ Capitalise la première lettre (ex: "red" -> "Red")
    inline std::string capitalizeFirstLetter(const std::string &input)
    {
        if (input.empty())
            return "";

        std::string result = input;
        result[0] = std::toupper(static_cast<unsigned char>(result[0]));
        return result;
    }

    inline std::string formatDisplayName(const std::string &input)
    {
        return capitalizeFirstLetter(trimAndToLower(input));
    }

}

#endif // STRING_UTILS_HPP
