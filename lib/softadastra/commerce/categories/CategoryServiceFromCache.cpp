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
        std::vector<Category> result;
        for (const auto &c : data_)
        {
            if (!c.getParentId().has_value())
            {
                result.push_back(c);
            }
        }
        return result;
    }

    std::vector<Category> CategoryServiceFromCache::getLeafCategories(std::size_t offset, std::size_t limit) const
    {
        std::unordered_set<std::uint32_t> parentIds;
        for (const auto &c : data_)
        {
            if (c.getParentId().has_value())
            {
                parentIds.insert(c.getParentId().value());
            }
        }

        std::vector<Category> result;
        for (const auto &c : data_)
        {
            if (parentIds.count(c.getId()) == 0)
            {
                result.push_back(c);
            }
        }

        if (offset >= result.size())
            return {};

        auto end = std::min(result.size(), offset + limit);
        return std::vector<Category>(result.begin() + offset, result.begin() + end);
    }
}
