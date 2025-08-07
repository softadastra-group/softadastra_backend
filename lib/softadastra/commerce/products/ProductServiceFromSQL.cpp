#include <softadastra/commerce/products/ProductServiceFromSQL.hpp>

namespace softadastra::commerce::products
{
    ProductServiceFromSQL::ProductServiceFromSQL(std::shared_ptr<adastra::database::Database> db)
        : db_(db),
          repository_(std::make_shared<ProductRepositorySQL>(db)),
          ambassadorService_(std::make_shared<AmbassadorService>(db)) // ⬅️ tu dois avoir créé cette classe
    {
    }

    std::vector<Product> ProductServiceFromSQL::getAllProducts() const
    {
        return repository_->findAll();
    }

    void ProductServiceFromSQL::create(Product &product)
    {
        try
        {
            db_->beginTransaction(); // ⬅️ active le mode transaction (désactive autocommit)

            repository_->insert(product); // insertion principale (et récupère l'ID)

            if (!product.getSizes().empty())
                repository_->batchInsert("product_sizes", product.getId(), product.getSizes(), "size_id");

            if (!product.getColors().empty())
                repository_->batchInsert("product_colors", product.getId(), product.getColors(), "color_id");

            if (!product.getCustomFields().empty())
                repository_->batchInsertCustomFields("product_custom_fields", product.getId(), product.getCustomFields());

            if (!product.getImages().empty())
                repository_->batchInsertWithStrings("images", product.getId(), product.getImages(), "image_url");

            if (!product.getSimilarProducts().empty())
                repository_->batchInsert("product_similar", product.getId(), product.getSimilarProducts(), "similar_product_id");

            ambassadorService_->checkAndReward(product.getId());

            db_->commit(); // ⬅️ valide et remet l'autocommit à true
        }
        catch (const std::exception &ex)
        {
            db_->rollback(); // ⬅️ annule tout et remet l'autocommit à true
            throw std::runtime_error(std::string("❌ Erreur lors de la création du produit : ") + ex.what());
        }
    }

}
