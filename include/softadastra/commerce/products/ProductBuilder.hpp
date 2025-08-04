#ifndef PRODUCT_BUILDER_HPP
#define PRODUCT_BUILDER_HPP

#include <softadastra/commerce/products/Product.hpp>

namespace softadastra::commerce::product
{
    class ProductBuilder
    {
    private:
        Product product;

    public:
        ProductBuilder(); // Appelle Product()

        ProductBuilder &setId(uint32_t id);
        ProductBuilder &setTitle(const std::string &title);
        ProductBuilder &setImageUrl(const std::string &imageUrl);
        ProductBuilder &setCityName(const std::string &cityName);
        ProductBuilder &setCountryImageUrl(const std::string &countryImageUrl);
        ProductBuilder &setCurrency(const std::string &currency);
        ProductBuilder &setFormattedPrice(const std::string &formattedPrice);
        ProductBuilder &setConvertedPrice(const std::string &convertedPrice);
        ProductBuilder &setSizes(const std::vector<std::string> &sizes);
        ProductBuilder &setColors(const std::vector<std::string> &colors);

        Product build() const;
    };
}

#endif // PRODUCT_BUILDER_HPP
