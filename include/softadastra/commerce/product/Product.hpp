#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <string>
#include <vector>
#include <cstdint>

namespace softadastra::commerce::product
{
    class Product
    {
    public:
        uint32_t id;
        std::string title;
        std::string image_url;
        std::string city_name;
        std::string country_image_url;
        std::string currency;
        std::string formatted_price;
        std::string converted_price;
        std::vector<std::string> sizes;
        std::vector<std::string> colors;

        Product(const std::string &title, const std::string &image_url,
                const std::string &city_name, const std::string &country_image_url,
                const std::string &currency, const std::string &formatted_price,
                const std::string &converted_price,
                const std::vector<std::string> &sizes,
                const std::vector<std::string> &colors)
            : id(0),
              title(title), image_url(image_url), city_name(city_name),
              country_image_url(country_image_url), currency(currency),
              formatted_price(formatted_price), converted_price(converted_price),
              sizes(sizes), colors(colors)
        {
        }

        Product(const Product &other) = default;
        Product(Product &&other) noexcept;
        Product &operator=(const Product &other);
        Product &operator=(Product &&other) noexcept;
        virtual ~Product() = default;

        uint32_t getId() const { return id; }
        const std::string &getTitle() const { return title; }
        const std::string &getImageUrl() const { return image_url; }
        const std::string &getCityName() const { return city_name; }
        const std::string &getCountryImageUrl() const { return country_image_url; }
        const std::string &getCurrency() const { return currency; }
        const std::string &getFormattedPrice() const { return formatted_price; }
        const std::string &getConvertedPrice() const { return converted_price; }
        const std::vector<std::string> &getSizes() const { return sizes; }
        const std::vector<std::string> &getColors() const { return colors; }

        void setId(uint32_t new_id) { id = new_id; }
        void setTitle(const std::string &new_title) { title = new_title; }
        void setImageUrl(const std::string &new_image_url) { image_url = new_image_url; }
        void setCityName(const std::string &new_city_name) { city_name = new_city_name; }
        void setCountryImageUrl(const std::string &new_country_image_url) { country_image_url = new_country_image_url; }
        void setCurrency(const std::string &new_currency) { currency = new_currency; }
        void setFormattedPrice(const std::string &new_formatted_price) { formatted_price = new_formatted_price; }
        void setConvertedPrice(const std::string &new_converted_price) { converted_price = new_converted_price; }
        void setSizes(const std::vector<std::string> &new_sizes) { sizes = new_sizes; }
        void setColors(const std::vector<std::string> &new_colors) { colors = new_colors; }
    };
};

#endif // PRODUCT_HPP
