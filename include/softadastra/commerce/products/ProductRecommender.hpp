#ifndef PRODUCT_RECOMMENDER_HPP
#define PRODUCT_RECOMMENDER_HPP

#include <vector>
#include <softadastra/commerce/products/Product.hpp>

namespace softadastra::commerce::products
{
    class ProductRecommender
    {
    public:
        // Produit de référence + tous les produits disponibles
        static std::vector<Product> recommendSimilar(const Product &reference, const std::vector<Product> &allProducts, std::size_t limit = 10);
    };
}

#endif
