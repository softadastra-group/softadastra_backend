#ifndef SIZE_FROM_CACHE_HPP
#define SIZE_FROM_CACHE_HPP

#include <softadastra/commerce/sizes/SizeCache.hpp>
#include <softadastra/commerce/sizes/Size.hpp>
#include <adastra/utils/string/StringUtils.hpp>

#include <string>
#include <optional>
#include <algorithm>

namespace softadastra::commerce::sizes
{
    class SizeServiceFromCache
    {
    public:
        SizeServiceFromCache(SizeCache &cacheSize)
            : cache(cacheSize) {}

        std::vector<Size> getAllSizes() const
        {
            return cache.getAll();
        }

        std::optional<Size> findById(std::uint32_t id)
        {
            const auto &all = cache.getAll();
            auto it = std::find_if(all.begin(), all.end(), [id](const Size &s)
                                   { return s.getId() == id; });

            if (it != all.end())
            {
                return *it;
            }
            return std::nullopt;
        }

        std::optional<Size> findByName(std::string name) const
        {
            const auto &all = cache.getAll();
            std::string searched = adastra::utils::string::trimAndToLower(name);

            auto it = std::find_if(all.begin(), all.end(), [&](const Size &s)
                                   {
                std::string cname = adastra::utils::string::trimAndToLower(s.getName());
                return cname == searched; });

            if (it != all.end())
            {
                return *it;
            }
            return std::nullopt;
        }

    private:
        SizeCache &cache;
    };
}

#endif