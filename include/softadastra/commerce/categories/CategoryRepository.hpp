#ifndef CATEGORY_REPOSITORY_HPP
#define CATEGORY_REPOSITORY_HPP

#include <softadastra/commerce/categories/Category.hpp>
#include <adastra/core/repository/JsonRepository.hpp>
#include <vector>
#include <string>
#include <algorithm>

namespace softadastra::commerce::categories
{
    using CategoryRepositoryBase = adastra::core::repository::JsonRepository<Category>;

    class CategoryRepository
    {
    public:
        explicit CategoryRepository(const std::string &jsonPath)
            : baseRepo(jsonPath, "categories") {}

        std::vector<Category> getAllCategories() const
        {
            return baseRepo.getAll();
        }

        std::vector<Category> getTopLevelCategories() const
        {
            std::vector<Category> all = baseRepo.getAll();
            std::vector<Category> result;

            std::copy_if(all.begin(), all.end(), std::back_inserter(result),
                         [](const Category &cat)
                         {
                             return !cat.getParentId().has_value();
                         });

            return result;
        }

        std::vector<Category> getLeafSubcategories(std::size_t offset = 0, std::size_t limit = 100) const
        {
            std::vector<Category> all = baseRepo.getAll();
            std::vector<Category> result;

            std::size_t total = all.size();
            std::size_t end = std::min(offset + limit, total);

            for (std::size_t i = offset; i < end; ++i)
            {
                const auto &cat = all[i];
                if (cat.getParentId().has_value())
                {
                    result.push_back(cat);
                }
            }

            return result;
        }

        void reload()
        {
            baseRepo.reload();
        }

    private:
        CategoryRepositoryBase baseRepo;
    };
}

#endif // CATEGORY_REPOSITORY_HPP
