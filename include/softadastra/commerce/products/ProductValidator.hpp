#ifndef PRODUCT_VALIDATOR_HPP
#define PRODUCT_VALIDATOR_HPP

#include <nlohmann/json.hpp>
#include <string>

namespace softadastra::commerce::products
{
    class ProductValidator
    {
    public:
        static void validate(const nlohmann::json &item, const std::string &source);
        static bool isValid(const nlohmann::json &item);
    };
}

#endif // PRODUCT_VALIDATOR_HPP
