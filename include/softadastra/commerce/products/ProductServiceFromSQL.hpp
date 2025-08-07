#ifndef PRODUCT_SERVICE_FROM_SQL_HPP
#define PRODUCT_SERVICE_FROM_SQL_HPP

#include <softadastra/commerce/products/Product.hpp>
#include <softadastra/commerce/products/ProductRepositorySQL.hpp>
#include <softadastra/commerce/products/AmbassadorService.hpp>
#include <adastra/database/Database.hpp>

#include <memory>
#include <vector>

namespace softadastra::commerce::products
{
    class ProductServiceFromSQL
    {
    public:
        explicit ProductServiceFromSQL(std::shared_ptr<adastra::database::Database> db);

        std::vector<Product> getAllProducts() const;
        void create(Product &product);

    private:
        std::shared_ptr<adastra::database::Database> db_;      // ✅ base de données
        std::shared_ptr<ProductRepositorySQL> repository_;     // ✅ repository produit
        std::shared_ptr<AmbassadorService> ambassadorService_; // ✅ service ambassadeur
    };
}

#endif
