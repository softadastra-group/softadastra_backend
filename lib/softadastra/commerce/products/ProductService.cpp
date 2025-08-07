#include <softadastra/commerce/products/ProductService.hpp>

namespace softadastra::commerce::products
{
    ProductService::ProductService(const std::string &path)
        : repo(path, "data") {}

    std::vector<Product> ProductService::getAllProducts() const
    {
        return repo.getAll();
    }

    void ProductService::reload()
    {
        repo.reload();
    }

}
