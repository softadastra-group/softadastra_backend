#ifndef PRODUCT_VALIDATOR_HPP
#define PRODUCT_VALIDATOR_HPP

#include <nlohmann/json.hpp>
#include <string>

namespace softadastra::commerce::product
{
    class ProductValidator
    {
    public:
        static void validate(const nlohmann::json &item, const std::string &source = "unknown");
    };
}

#endif // PRODUCT_VALIDATOR_HPP
