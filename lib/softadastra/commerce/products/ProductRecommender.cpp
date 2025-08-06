#include <softadastra/commerce/products/ProductRecommender.hpp>
#include <algorithm>
#include <cmath>

namespace softadastra::commerce::products
{
    std::vector<Product> ProductRecommender::recommendSimilar(const Product &reference, const std::vector<Product> &allProducts, std::size_t limit)
    {
        constexpr int WEIGHT_CATEGORY = 5;
        constexpr int WEIGHT_BRAND = 3;
        constexpr int WEIGHT_CONDITION = 2;
        constexpr int WEIGHT_CITY = 1;
        constexpr int WEIGHT_PRICE_SIMILARITY = 2;
        constexpr int WEIGHT_BOOSTED = 1;
        constexpr int WEIGHT_RATING = 1;
        constexpr int WEIGHT_POPULARITY = 1;

        std::vector<std::pair<int, Product>> scored;

        for (const auto &candidate : allProducts)
        {
            if (candidate.getId() == reference.getId())
                continue;

            int score = 0;

            if (candidate.getCategoryId() == reference.getCategoryId())
                score += WEIGHT_CATEGORY;
            if (candidate.getBrandName() == reference.getBrandName())
                score += WEIGHT_BRAND;
            if (candidate.getConditionName() == reference.getConditionName())
                score += WEIGHT_CONDITION;
            if (candidate.getCityName() == reference.getCityName())
                score += WEIGHT_CITY;

            float refPrice = reference.getConvertedPriceValue();
            float candPrice = candidate.getConvertedPriceValue();
            if (refPrice > 0.0f && std::abs(candPrice - refPrice) <= (refPrice * 0.2f))
                score += WEIGHT_PRICE_SIMILARITY;

            if (candidate.isBoosted())
                score += WEIGHT_BOOSTED;
            if (candidate.getAverageRating() >= 4.0f)
                score += WEIGHT_RATING;
            if (candidate.getViews() >= 100)
                score += WEIGHT_POPULARITY;

            scored.emplace_back(score, candidate);
        }

        std::sort(scored.begin(), scored.end(), [](const auto &a, const auto &b)
                  { return a.first > b.first; });

        std::vector<Product> result;
        for (std::size_t i = 0; i < std::min(limit, scored.size()); ++i)
        {
            result.push_back(scored[i].second);
        }

        return result;
    }
}
