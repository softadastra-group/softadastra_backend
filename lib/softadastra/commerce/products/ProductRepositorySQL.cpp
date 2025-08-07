#include <softadastra/commerce/products/ProductRepositorySQL.hpp>
#include <softadastra/commerce/products/ProductBuilder.hpp>

namespace softadastra::commerce::products
{
    ProductRepositorySQL::ProductRepositorySQL(std::shared_ptr<adastra::database::Database> db)
        : db_(std::move(db)) {}

    void ProductRepositorySQL::insert(Product &product)
    {
        std::vector<std::string> columns = {
            "title", "image_url", "city_name", "country_image_url", "currency",
            "formatted_price", "converted_price", "price_with_shipping_value",
            "condition_name", "brand_name", "package_format_name", "category_id",
            "views", "review_count", "boost", "converted_price_value",
            "original_price", "average_rating"};

        db_->create(
            "products", columns,
            product.getTitle(),
            product.getImageUrl(),
            product.getCityName(),
            product.getCountryImageUrl(),
            product.getCurrency(),
            product.getFormattedPrice(),
            product.getConvertedPrice(),
            product.getPriceWithShipping(),
            product.getConditionName(),
            product.getBrandName(),
            product.getPackageFormatName(),
            product.getCategoryId(),
            static_cast<int>(product.getViews()),
            static_cast<int>(product.getReviewCount()),
            static_cast<bool>(product.isBoosted()),
            static_cast<float>(product.getConvertedPriceValue()),
            product.getOriginalPrice().value_or(""),
            product.getAverageRating().value_or(0.0f));

        // 🔁 Récupérer l'ID auto-incrémenté
        product.setId(db_->lastInsertId());
    }

    void ProductRepositorySQL::batchInsert(const std::string &table, uint32_t productId, const std::vector<std::string> &values, const std::string &column)
    {
        if (values.empty())
            return;

        std::string query = "INSERT INTO " + table + " (product_id, " + column + ") VALUES ";

        std::vector<std::any> params;
        for (size_t i = 0; i < values.size(); ++i)
        {
            query += "(?, ?)";
            if (i != values.size() - 1)
                query += ", ";

            params.push_back(productId);
            params.push_back(values[i]);
        }

        db_->executeUpdate(query, params);
    }

    void ProductRepositorySQL::batchInsert(const std::string &table, uint32_t productId, const std::vector<uint32_t> &values, const std::string &column)
    {
        if (values.empty())
            return;

        std::string query = "INSERT INTO " + table + " (product_id, " + column + ") VALUES ";

        std::vector<std::any> params;

        for (size_t i = 0; i < values.size(); ++i)
        {
            query += "(?, ?)";
            if (i != values.size() - 1)
                query += ", ";

            params.push_back(productId);
            params.push_back(static_cast<int>(values[i])); // Cast explicite si nécessaire
        }

        db_->executeUpdate(query, params);
    }

    void ProductRepositorySQL::batchInsertWithStrings(const std::string &table, uint32_t productId, const std::vector<std::string> &values, const std::string &column)
    {
        batchInsert(table, productId, values, column);
    }

    void ProductRepositorySQL::batchInsertCustomFields(const std::string &table, uint32_t productId, const std::vector<std::pair<std::string, std::string>> &fields)
    {
        if (fields.empty())
            return;

        std::string query = "INSERT INTO " + table + " (product_id, name, value) VALUES ";

        std::vector<std::any> params;
        for (size_t i = 0; i < fields.size(); ++i)
        {
            query += "(?, ?, ?)";
            if (i != fields.size() - 1)
                query += ", ";

            params.push_back(productId);
            params.push_back(fields[i].first);
            params.push_back(fields[i].second);
        }

        db_->executeUpdate(query, params);
    }

    std::vector<Product> ProductRepositorySQL::findAll()
    {
        std::vector<Product> products;

        const std::string sql = R"(SELECT
            id, title, image_url, city_name, country_image_url, currency,
            formatted_price, converted_price, price_with_shipping_value,
            condition_name, brand_name, package_format_name, category_id,
            views, review_count, boost, converted_price_value,
            original_price, average_rating
            FROM products
        )";

        auto results = db_->executeQuery(sql);

        while (results->next())
        {
            ProductBuilder builder;
            builder.setId(results->getUInt("id"))
                .setTitle(results->getString("title"))
                .setImageUrl(results->getString("image_url"))
                .setCityName(results->getString("city_name"))
                .setCountryImageUrl(results->getString("country_image_url"))
                .setCurrency(results->getString("currency"))
                .setFormattedPrice(results->getString("formatted_price"))
                .setConvertedPrice(results->getString("converted_price"))
                .setPriceWithShipping(results->getDouble("price_with_shipping_value"))
                .setConditionName(results->getString("condition_name"))
                .setBrandName(results->getString("brand_name"))
                .setPackageFormatName(results->getString("package_format_name"))
                .setCategoryId(results->getUInt("category_id"))
                .setViews(results->getUInt("views"))
                .setReviewCount(results->getUInt("review_count"))
                .setBoost(results->getBoolean("boost"))
                .setConvertedPriceValue(results->getDouble("converted_price_value"))
                .setOriginalPrice(results->isNull("original_price")
                                      ? std::nullopt
                                      : std::make_optional(results->getString("original_price")))
                .setAverageRating(results->getDouble("average_rating"));

            products.emplace_back(builder.build());
        }

        return products;
    }
}
