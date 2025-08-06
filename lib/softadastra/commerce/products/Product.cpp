#include <softadastra/commerce/products/Product.hpp>
#include <softadastra/commerce/products/ProductFactory.hpp>

namespace softadastra::commerce::products
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
          converted_price_value(other.converted_price_value),
          price_with_shipping_value(other.price_with_shipping_value),
          original_price(std::move(other.original_price)),
          brand_id(std::move(other.brand_id)),
          average_rating(other.average_rating),
          sizes(std::move(other.sizes)),
          colors(std::move(other.colors)),
          condition_name(std::move(other.condition_name)),
          brand_name(std::move(other.brand_name)),
          package_format_name(std::move(other.package_format_name)),
          category_id(other.category_id),
          views(other.views),
          review_count(other.review_count),
          boost(other.boost)
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
            converted_price_value = other.converted_price_value;
            price_with_shipping_value = other.price_with_shipping_value;
            original_price = std::move(other.original_price);
            sizes = std::move(other.sizes);
            colors = std::move(other.colors);
            condition_name = std::move(other.condition_name);
            brand_name = std::move(other.brand_name);
            package_format_name = std::move(other.package_format_name);
            category_id = other.category_id;
            views = other.views;
            average_rating = other.average_rating;
            review_count = other.review_count;
            boost = other.boost;
        }
        return *this;
    }

    Product Product::fromJson(const nlohmann::json &j)
    {
        return ProductFactory::fromJsonOrThrow(j);
    }

}
