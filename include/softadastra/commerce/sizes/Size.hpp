#ifndef SIZE_HPP
#define SIZE_HPP

#include <string>
#include <cstdint>
#include <stdexcept>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace softadastra::commerce::sizes
{
    class Size
    {
    public:
        Size()
            : id_(0), name_("") {}

        Size(const std::string &name)
            : id_(0), name_(name) {}

        Size(const Size &) = default;
        Size &operator=(const Size &) = default;

        Size(Size &&) noexcept = default;
        Size &operator=(Size &&) noexcept = default;

        std::uint32_t getId() const { return id_; }
        const std::string &getName() const { return name_; }

        void setId(std::uint32_t id) { id_ = id; }
        void setName(const std::string &name) { name_ = name; }

        json toJson() const
        {
            return {
                {"id", id_},
                {"name", name_}};
        }

        static Size fromJson(const json &j)
        {
            Size s(j.at("name").get<std::string>());
            s.setId(j.at("id").get<std::uint32_t>());
            return s;
        }

    private:
        std::uint32_t id_;
        std::string name_;
    };
}

#endif