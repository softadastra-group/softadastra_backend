#ifndef CATEGORY_SERVICE_FROM_CACHE_HPP
#define CATEGORY_SERVICE_FROM_CACHE_HPP

#include <softadastra/commerce/categories/Category.hpp>
#include <vector>
#include <cstdint>

namespace softadastra::commerce::categories
{
    class CategoryServiceFromCache
    {
    public:
        explicit CategoryServiceFromCache(const std::vector<Category> &categories);

        std::vector<Category> getAllCategories() const;
        std::vector<Category> getTopLevelCategories() const;
        std::vector<Category> getLeafCategories(std::size_t offset = 0, std::size_t limit = 1000) const;

        void reloadData(const std::vector<Category> &newData); // pour recharger les catégories

    private:
        std::vector<Category> data_;

        // 🔁 Caches internes
        mutable std::vector<Category> topLevelCache_;
        mutable std::vector<Category> leafCache_;
        mutable bool isTopLevelCacheBuilt_ = false;
        mutable bool isLeafCacheBuilt_ = false;
    };
}

#endif // CATEGORY_SERVICE_FROM_CACHE_HPP
