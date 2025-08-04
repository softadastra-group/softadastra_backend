#include <softadastra/commerce/products/ProductBuilder.hpp>

namespace softadastra::commerce::product
{
    ProductBuilder::ProductBuilder() : product() {}

    ProductBuilder &ProductBuilder::setId(uint32_t id)
    {
        product.setId(id);
        return *this;
    }

    ProductBuilder &ProductBuilder::setTitle(const std::string &title)
    {
        product.setTitle(title);
        return *this;
    }

    ProductBuilder &ProductBuilder::setImageUrl(const std::string &imageUrl)
    {
        product.setImageUrl(imageUrl);
        return *this;
    }

    ProductBuilder &ProductBuilder::setCityName(const std::string &cityName)
    {
        product.setCityName(cityName);
        return *this;
    }

    ProductBuilder &ProductBuilder::setCountryImageUrl(const std::string &countryImageUrl)
    {
        product.setCountryImageUrl(countryImageUrl);
        return *this;
    }

    ProductBuilder &ProductBuilder::setCurrency(const std::string &currency)
    {
        product.setCurrency(currency);
        return *this;
    }

    ProductBuilder &ProductBuilder::setFormattedPrice(const std::string &formattedPrice)
    {
        product.setFormattedPrice(formattedPrice);
        return *this;
    }

    ProductBuilder &ProductBuilder::setConvertedPrice(const std::string &convertedPrice)
    {
        product.setConvertedPrice(convertedPrice);
        return *this;
    }

    ProductBuilder &ProductBuilder::setSizes(const std::vector<std::string> &sizes)
    {
        product.setSizes(sizes);
        return *this;
    }

    ProductBuilder &ProductBuilder::setColors(const std::vector<std::string> &colors)
    {
        product.setColors(colors);
        return *this;
    }

    Product ProductBuilder::build() const
    {
        return product;
    }
}
