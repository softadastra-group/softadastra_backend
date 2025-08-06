#include <softadastra/commerce/categories/CategoryServiceFromCache.hpp>
#include <unordered_set>
#include <algorithm>

namespace softadastra::commerce::categories
{
    CategoryServiceFromCache::CategoryServiceFromCache(const std::vector<Category> &categories)
        : data_(categories) {}

    std::vector<Category> CategoryServiceFromCache::getAllCategories() const
    {
        return data_;
    }

    std::vector<Category> CategoryServiceFromCache::getTopLevelCategories() const
    {
        if (!isTopLevelCacheBuilt_)
        {
            topLevelCache_.clear();
            for (const auto &c : data_)
            {
                if (!c.getParentId().has_value())
                {
                    topLevelCache_.push_back(c);
                }
            }
            isTopLevelCacheBuilt_ = true;
        }
        return topLevelCache_;
    }

    std::vector<Category> CategoryServiceFromCache::getLeafCategories(std::size_t offset, std::size_t limit) const
    {
        if (!isLeafCacheBuilt_)
        {
            std::unordered_set<std::uint32_t> parentIds;
            for (const auto &c : data_)
            {
                if (c.getParentId().has_value())
                {
                    parentIds.insert(c.getParentId().value());
                }
            }

            leafCache_.clear();
            for (const auto &c : data_)
            {
                if (parentIds.count(c.getId()) == 0)
                {
                    leafCache_.push_back(c);
                }
            }

            isLeafCacheBuilt_ = true;
        }

        if (offset >= leafCache_.size())
            return {};

        auto end = std::min(leafCache_.size(), offset + limit);
        return std::vector<Category>(leafCache_.begin() + offset, leafCache_.begin() + end);
    }

    void CategoryServiceFromCache::reloadData(const std::vector<Category> &newData)
    {
        data_ = newData;

        // Invalider les caches
        topLevelCache_.clear();
        leafCache_.clear();
        isTopLevelCacheBuilt_ = false;
        isLeafCacheBuilt_ = false;
    }
}
