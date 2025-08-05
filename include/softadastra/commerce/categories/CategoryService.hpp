#ifndef CATEGORY_SERVICE_HPP
#define CATEGORY_SERVICE_HPP

#include <softadastra/commerce/categories/Category.hpp>
#include <softadastra/commerce/categories/CategoryRepository.hpp>
#include <string>
#include <vector>

namespace softadastra::commerce::categories
{
    class CategoryService
    {
    public:
        explicit CategoryService(const std::string &jsonPath);

        std::vector<Category> getAllCategories() const;
        std::vector<Category> getLeafCategories(std::size_t offset = 0, std::size_t limit = 1000) const;
        std::vector<Category> getTopLevelCategories() const;

    private:
        mutable CategoryRepository repository;
    };
}

#endif // CATEGORY_SERVICE_HPP
