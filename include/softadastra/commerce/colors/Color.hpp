#ifndef COLOR_HPP
#define COLOR_HPP

#include <nlohmann/json.hpp>
#include <string>
#include <cstdint>

using json = nlohmann::json;

namespace softadastra::commerce::colors
{
    class Color
    {
    public:
        Color()
            : id_(0), name_("") {}

        Color(const std::string name)
            : id_(0), name_(name) {}

        Color(const Color &) = default;
        Color &operator=(const Color &) = default;

        Color(Color &&) noexcept = default;
        Color &operator=(Color &&) noexcept = default;

        std::uint32_t getId() const { return id_; }
        const std::string getName() const { return name_; }

        void setId(std::uint32_t id) { id_ = id; }
        void setName(const std::string &name) { name_ = name; }

        json toJson() const
        {
            return {
                {"id", id_},
                {"name", name_}};
        }

        static Color fromJson(const json &j)
        {
            Color c(j.at("name").get<std::string>());
            c.setId(j.at("id").get<std::uint32_t>());
            return c;
        }

    private:
        std::uint32_t id_;
        std::string name_;
    };
}

#endif