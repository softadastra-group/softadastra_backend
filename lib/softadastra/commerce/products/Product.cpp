#include <softadastra/commerce/products/Product.hpp>
#include <softadastra/commerce/products/ProductFactory.hpp>

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
          colors(std::move(other.colors))
    {
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

    Product Product::fromJson(const nlohmann::json &j)
    {
        auto ptr = ProductFactory::createFromJson(j);
        if (!ptr)
        {
            throw std::runtime_error("Invalid product JSON structure");
        }
        return *ptr;
    }
}
