#ifndef JSON_SERIALIZABLE_HPP
#define JSON_SERIALIZABLE_HPP

#include <nlohmann/json.hpp>

namespace adastra::core::interfaces
{
    class JsonSerializable
    {
    public:
        virtual ~JsonSerializable() = default;
        virtual nlohmann::json toJson() const = 0;
        virtual void fromJson(const nlohmann::json &j) = 0;
    };
}

#endif // JSON_SERIALIZABLE_HPP
