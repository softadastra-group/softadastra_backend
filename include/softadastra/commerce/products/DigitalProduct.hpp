#ifndef DIGITAL_PRODUCT_HPP
#define DIGITAL_PRODUCT_HPP

#include <softadastra/commerce/products/Product.hpp>
#include <nlohmann/json.hpp>

namespace softadastra::commerce::product
{
    class DigitalProduct : public Product
    {
    private:
        std::string download_url;

    public:
        DigitalProduct(const nlohmann::json &data)
            : Product(
                  data.value("title", ""),
                  data.value("image_url", ""),
                  data.value("city_name", ""),
                  data.value("country_image_url", ""),
                  data.value("currency", ""),
                  data.value("formatted_price", ""),
                  data.value("converted_price", ""),
                  data.value("sizes", std::vector<std::string>{}),
                  data.value("colors", std::vector<std::string>{})),
              download_url(data.value("download_url", ""))
        {
        }

        const std::string &getDownloadUrl() const { return download_url; }
    };
}

#endif // DIGITAL_PRODUCT_HPP
