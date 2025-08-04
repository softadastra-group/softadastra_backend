#ifndef CATEGORY_REPOSITORY_JSON_HPP
#define CATEGORY_REPOSITORY_JSON_HPP

#include <softadastra/commerce/categories/Category.hpp>
#include <vector>
#include <string>
#include <cstddef>

namespace softadastra::commerce::categories
{
    class CategoryRepositoryJson
    {
    public:
        explicit CategoryRepositoryJson(const std::string &filepath);

        std::vector<Category> getLeafSubcategories(std::size_t offset = 0, std::size_t limit = 100);
        std::vector<Category> getTopLevelCategories();
        std::vector<Category> getAllCategories();

    private:
        std::string jsonFilePath;
    };
}

#endif // CATEGORY_REPOSITORY_JSON_HPP
