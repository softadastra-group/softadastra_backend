#include <softadastra/commerce/products/ProductBuilder.hpp>

namespace softadastra::commerce::products
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
    ProductBuilder &ProductBuilder::setConvertedPriceValue(float value)
    {
        product.setConvertedPriceValue(value);
        return *this;
    }
    ProductBuilder &ProductBuilder::setPriceWithShipping(float value)
    {
        product.setPriceWithShipping(value);
        return *this;
    }
    ProductBuilder &ProductBuilder::setCurrency(const std::string &currency)
    {
        product.setCurrency(currency);
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
    ProductBuilder &ProductBuilder::setConditionName(const std::string &conditionName)
    {
        product.setConditionName(conditionName);
        return *this;
    }
    ProductBuilder &ProductBuilder::setBrandName(const std::string &brandName)
    {
        product.setBrandName(brandName);
        return *this;
    }
    ProductBuilder &ProductBuilder::setPackageFormatName(const std::string &packageFormatName)
    {
        product.setPackageFormatName(packageFormatName);
        return *this;
    }
    ProductBuilder &ProductBuilder::setCategoryId(uint32_t categoryId)
    {
        product.setCategoryId(categoryId);
        return *this;
    }
    ProductBuilder &ProductBuilder::setViews(uint32_t views)
    {
        product.setViews(views);
        return *this;
    }
    ProductBuilder &ProductBuilder::setAverageRating(float rating)
    {
        product.setAverageRating(rating);
        return *this;
    }
    ProductBuilder &ProductBuilder::setReviewCount(uint32_t count)
    {
        product.setReviewCount(count);
        return *this;
    }
    ProductBuilder &ProductBuilder::setBoost(bool boost)
    {
        product.setBoost(boost);
        return *this;
    }
    ProductBuilder &ProductBuilder::setOriginalPrice(const std::optional<std::string> &originalPrice)
    {
        product.setOriginalPrice(originalPrice);
        return *this;
    }
    ProductBuilder &ProductBuilder::setBrandId(const std::optional<uint32_t> &brandId)
    {
        product.setBrandId(brandId);
        return *this;
    }
    ProductBuilder &ProductBuilder::setLocation(const std::string &city, const std::string &countryImage)
    {
        product.setCityName(city);
        product.setCountryImageUrl(countryImage);
        return *this;
    }

    ProductBuilder &ProductBuilder::setSimilarProducts(const std::vector<uint32_t> &similarProducts)
    {
        product.setSimilarProducts(similarProducts);
        return *this;
    }

    ProductBuilder &ProductBuilder::setCustomFields(const std::vector<std::pair<std::string, std::string>> &fields)
    {
        product.setCustomFields(fields);
        return *this;
    }

    ProductBuilder &ProductBuilder::setImages(const std::vector<std::string> &images)
    {
        product.setImages(images);
        return *this;
    }

    ProductBuilder &ProductBuilder::clear()
    {
        product = Product();
        return *this;
    }

    Product ProductBuilder::build() const { return product; }
    std::unique_ptr<Product> ProductBuilder::buildUnique() { return std::make_unique<Product>(std::move(product)); }
} // namespace softadastra::commerce::product
