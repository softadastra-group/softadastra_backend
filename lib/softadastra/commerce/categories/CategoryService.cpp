#include <softadastra/commerce/categories/CategoryService.hpp>

namespace softadastra::commerce::categories
{
    CategoryService::CategoryService(const std::string &jsonPath)
        : repository(jsonPath) {}

    std::vector<Category> CategoryService::getAllCategories() const
    {
        return repository.getAllCategories();
    }

    std::vector<Category> CategoryService::getLeafCategories(std::size_t offset, std::size_t limit) const
    {
        return repository.getLeafSubcategories(offset, limit);
    }

    std::vector<Category> CategoryService::getTopLevelCategories() const
    {
        return repository.getTopLevelCategories();
    }
}
