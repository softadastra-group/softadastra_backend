#ifndef CITY_HPP
#define CITY_HPP

#include <cstdint>
#include <string>
#include <stdexcept>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace softadastra::commerce::cities
{
    class City
    {
    public:
        City()
            : id_(0), name_(""), country_id_(0) {}

        City(const std::string &name, std::uint32_t country_id)
            : id_(0), name_(name), country_id_(country_id) {}

        City(const City &) = default;
        City &operator=(const City &) = default;
        City(City &&) noexcept = default;
        City &operator=(City &&) noexcept = default;

        std::uint32_t getId() const { return id_; }
        const std::string getName() const { return name_; }
        std::uint32_t getCountryId() const { return country_id_; }

        void setId(std::uint32_t id) { id_ = id; }
        void setName(const std::string &name) { name_ = name; }
        void setCountryId(std::uint32_t country_id) { country_id_ = country_id; }

        json toJson() const
        {
            return {
                {"id", getId()},
                {"name", getName()},
                {"country_id", getCountryId()}};
        }

        static City fromJson(const json &j)
        {
            City c(j.at("name"), j.at("country_id"));
            c.setId(j["id"].get<std::uint32_t>());

            return c;
        }

    private:
        std::uint32_t id_;
        std::string name_;
        std::uint32_t country_id_;
    };
}

#endif