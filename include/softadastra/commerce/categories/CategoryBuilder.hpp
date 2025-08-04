#ifndef CATEGORY_BUILDER_HPP
#define CATEGORY_BUILDER_HPP

#include <softadastra/commerce/categories/Category.hpp>

namespace softadastra::commerce::categories
{
    class CategoryBuilder
    {
    private:
        Category category;

    public:
        CategoryBuilder &setId(std::uint32_t id)
        {
            category.setId(id);
            return *this;
        }

        CategoryBuilder &setName(const std::string &name)
        {
            category.setName(name);
            return *this;
        }

        CategoryBuilder &setParentId(const std::optional<std::uint32_t> &parentId)
        {
            category.setParentId(parentId);
            return *this;
        }

        CategoryBuilder &setImageUrl(const std::string &url)
        {
            category.setImageUrl(url);
            return *this;
        }

        CategoryBuilder &setProductCount(std::uint32_t count)
        {
            category.setProductCount(count);
            return *this;
        }

        Category build() const
        {
            return category;
        }
    };
}

#endif // CATEGORY_BUILDER_HPP
