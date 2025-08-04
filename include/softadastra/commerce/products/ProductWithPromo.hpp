#ifndef PRODUCT_WITH_PROMO_HPP
#define PRODUCT_WITH_PROMO_HPP

#include <softadastra/commerce/products/Product.hpp>
#include <nlohmann/json.hpp>

namespace softadastra::commerce::product
{
    class ProductWithPromo : public Product
    {
    public:
        std::string promo_text;

        ProductWithPromo(const nlohmann::json &data)
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
              promo_text(data.value("promo_text", ""))
        {
        }

        const std::string &getPromoText() const { return promo_text; }
    };
}

#endif // PRODUCT_WITH_PROMO_HPP
