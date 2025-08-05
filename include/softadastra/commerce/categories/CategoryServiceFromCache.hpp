#ifndef CATEGORY_SERVICE_FROM_CACHE_HPP
#define CATEGORY_SERVICE_FROM_CACHE_HPP

#include <softadastra/commerce/categories/Category.hpp>
#include <vector>

namespace softadastra::commerce::categories
{
    class CategoryServiceFromCache
    {
    public:
        explicit CategoryServiceFromCache(const std::vector<Category> &categories);

        std::vector<Category> getAllCategories() const;
        std::vector<Category> getTopLevelCategories() const;
        std::vector<Category> getLeafCategories(std::size_t offset = 0, std::size_t limit = 1000) const;

    private:
        std::vector<Category> data_;
    };
}

#endif // CATEGORY_SERVICE_FROM_CACHE_HPP
