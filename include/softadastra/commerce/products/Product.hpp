#ifndef PRODUCT_HPP
#define PRODUCT_HPP

#include <string>
#include <vector>
#include <cstdint>
#include <nlohmann/json.hpp>
#include <optional>

using json = nlohmann::json;

namespace softadastra::commerce::products
{
    class ProductBuilder;

    class Product
    {
    public:
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
        const std::string &getFormattedPrice() const { return formatted_price; }
        const std::string &getConvertedPrice() const { return converted_price; }
        const std::vector<std::string> &getSizes() const { return sizes; }
        const std::vector<std::string> &getColors() const { return colors; }
        const std::string &getConditionName() const { return condition_name; }
        const std::string &getBrandName() const { return brand_name; }
        const std::string &getPackageFormatName() const { return package_format_name; }
        const std::string &getCurrency() const { return currency; }
        float getConvertedPriceValue() const { return converted_price_value; }
        float getPriceWithShipping() const { return price_with_shipping_value; }
        uint32_t getCategoryId() const { return category_id; }
        uint32_t getViews() const { return views; }
        std::optional<float> getAverageRating() const { return average_rating; }
        std::optional<uint32_t> getBrandId() const { return brand_id; }
        std::optional<std::string> getOriginalPrice() const { return original_price; }
        uint32_t getReviewCount() const { return review_count; }
        bool isBoosted() const { return boost; }

        void setId(uint32_t value) { id = value; }
        void setTitle(const std::string &value) { title = value; }
        void setImageUrl(const std::string &value) { image_url = value; }
        void setCityName(const std::string &value) { city_name = value; }
        void setCountryImageUrl(const std::string &value) { country_image_url = value; }
        void setFormattedPrice(const std::string &value) { formatted_price = value; }
        void setConvertedPrice(const std::string &value) { converted_price = value; }
        void setConvertedPriceValue(float value) { converted_price_value = value; }
        void setPriceWithShipping(float value) { price_with_shipping_value = value; }
        void setSizes(const std::vector<std::string> &value) { sizes = value; }
        void setColors(const std::vector<std::string> &value) { colors = value; }
        void setConditionName(const std::string &value) { condition_name = value; }
        void setBrandName(const std::string &value) { brand_name = value; }
        void setPackageFormatName(const std::string &value) { package_format_name = value; }
        void setCurrency(const std::string &value) { currency = value; }
        void setCategoryId(uint32_t value) { category_id = value; }
        void setViews(uint32_t value) { views = value; }
        void setAverageRating(std::optional<float> value) { average_rating = value; }
        void setBrandId(std::optional<uint32_t> value) { brand_id = value; }
        void setOriginalPrice(std::optional<std::string> value) { original_price = value; }
        void setReviewCount(uint32_t value) { review_count = value; }
        void setBoost(bool value) { boost = value; }

        static Product fromJson(const nlohmann::json &j);

        nlohmann::json toJson() const
        {
            nlohmann::json j;
            j["id"] = id;
            j["title"] = title;
            j["image_url"] = image_url;
            j["city_name"] = city_name;
            j["country_image_url"] = country_image_url;
            j["currency"] = currency;
            j["formatted_price"] = formatted_price;
            j["converted_price"] = converted_price;

            if (converted_price_value > 0.0f)
                j["converted_price_value"] = converted_price_value;
            if (price_with_shipping_value > 0.0f)
                j["price_with_shipping_value"] = price_with_shipping_value;
            if (original_price.has_value())
                j["original_price"] = original_price.value();
            if (brand_id.has_value())
                j["brand_id"] = brand_id.value();
            if (average_rating.has_value())
                j["average_rating"] = average_rating.value();

            if (!sizes.empty())
                j["sizes"] = sizes;
            if (!colors.empty())
                j["colors"] = colors;
            if (!condition_name.empty())
                j["condition_name"] = condition_name;
            if (!brand_name.empty())
                j["brand_name"] = brand_name;
            if (!package_format_name.empty())
                j["package_format_name"] = package_format_name;
            if (category_id != 0)
                j["category_id"] = category_id;
            if (views > 0)
                j["views"] = views;
            if (review_count > 0)
                j["review_count"] = review_count;

            j["boost"] = boost;
            return j;
        }

    private:
        std::uint32_t id;
        std::string title;
        std::string image_url;
        std::string city_name;
        std::string country_image_url;
        std::string currency;
        std::string formatted_price;
        std::string converted_price;
        float converted_price_value;
        float price_with_shipping_value;
        std::optional<std::string> original_price;
        std::optional<uint32_t> brand_id;
        std::optional<float> average_rating;
        std::vector<std::string> sizes;
        std::vector<std::string> colors;
        std::string condition_name;
        std::string brand_name;
        std::string package_format_name;
        std::uint32_t category_id;
        std::uint32_t views;
        std::uint32_t review_count;
        bool boost;

        Product() : id(0), converted_price_value(0), price_with_shipping_value(0),
                    category_id(0), views(0), review_count(0), boost(false) {}

        friend class ProductBuilder;
    };
}

#endif // PRODUCT_HPP
