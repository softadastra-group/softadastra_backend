// ProductBuilder.hpp
#ifndef PRODUCT_BUILDER_HPP
#define PRODUCT_BUILDER_HPP

#include <string>
#include <vector>
#include <memory>
#include <optional>
#include <cstdint>
#include <softadastra/commerce/products/Product.hpp>

namespace softadastra::commerce::products
{
    class ProductBuilder
    {
    public:
        ProductBuilder();

        ProductBuilder &setId(uint32_t id);
        ProductBuilder &setTitle(const std::string &title);
        ProductBuilder &setImageUrl(const std::string &imageUrl);
        ProductBuilder &setCityName(const std::string &cityName);
        ProductBuilder &setCountryImageUrl(const std::string &countryImageUrl);
        ProductBuilder &setFormattedPrice(const std::string &formattedPrice);
        ProductBuilder &setConvertedPrice(const std::string &convertedPrice);
        ProductBuilder &setConvertedPriceValue(float value);
        ProductBuilder &setPriceWithShipping(float value);
        ProductBuilder &setCurrency(const std::string &currency);
        ProductBuilder &setSizes(const std::vector<std::string> &sizes);
        ProductBuilder &setColors(const std::vector<std::string> &colors);
        ProductBuilder &setConditionName(const std::string &conditionName);
        ProductBuilder &setBrandName(const std::string &brandName);
        ProductBuilder &setPackageFormatName(const std::string &packageFormatName);
        ProductBuilder &setCategoryId(uint32_t categoryId);
        ProductBuilder &setViews(uint32_t views);
        ProductBuilder &setAverageRating(float rating);
        ProductBuilder &setReviewCount(uint32_t count);
        ProductBuilder &setBoost(bool boost);
        ProductBuilder &setOriginalPrice(const std::optional<std::string> &originalPrice);
        ProductBuilder &setBrandId(const std::optional<uint32_t> &brandId);

        ProductBuilder &setLocation(const std::string &city, const std::string &countryImage);
        ProductBuilder &clear();

        Product build() const;
        std::unique_ptr<Product> buildUnique();

    private:
        Product product;
    };
}

#endif // PRODUCT_BUILDER_HPP
