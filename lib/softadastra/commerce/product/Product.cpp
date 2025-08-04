#include <softadastra/commerce/product/Product.hpp>

namespace softadastra::commerce::product
{
    Product::Product(Product &&other) noexcept
        : id(other.id),
          title(std::move(other.title)),
          image_url(std::move(other.image_url)),
          city_name(std::move(other.city_name)),
          country_image_url(std::move(other.country_image_url)),
          currency(std::move(other.currency)),
          formatted_price(std::move(other.formatted_price)),
          converted_price(std::move(other.converted_price)),
          sizes(std::move(other.sizes)),
          colors(std::move(other.colors)) {}

    Product &Product::operator=(const Product &other)
    {
        if (this != &other)
        {
            id = other.id;
            title = other.title;
            image_url = other.image_url;
            city_name = other.city_name;
            country_image_url = other.country_image_url;
            currency = other.currency;
            formatted_price = other.formatted_price;
            converted_price = other.converted_price;
            sizes = other.sizes;
            colors = other.colors;
        }
        return *this;
    }

    Product &Product::operator=(Product &&other) noexcept
    {
        if (this != &other)
        {
            id = other.id;
            title = std::move(other.title);
            image_url = std::move(other.image_url);
            city_name = std::move(other.city_name);
            country_image_url = std::move(other.country_image_url);
            currency = std::move(other.currency);
            formatted_price = std::move(other.formatted_price);
            converted_price = std::move(other.converted_price);
            sizes = std::move(other.sizes);
            colors = std::move(other.colors);
        }
        return *this;
    }

};