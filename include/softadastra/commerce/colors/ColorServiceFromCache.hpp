#ifndef COLOR_SERVICE_FROM_CACHE_HPP
#define COLOR_SERVICE_FROM_CACHE_HPP

#include <softadastra/commerce/colors/Color.hpp>
#include <softadastra/commerce/colors/ColorCache.hpp>

#include <adastra/utils/string/StringUtils.hpp>

#include <optional>
#include <string>
#include <algorithm>

namespace softadastra::commerce::colors
{
    class ColorServiceFromCache
    {
    private:
        ColorCache &cache;

    public:
        ColorServiceFromCache(ColorCache &cache) : cache(cache) {}

        std::vector<Color> getAllColors() const
        {
            return cache.getAll();
        }

        std::optional<Color> findById(std::uint32_t id) const
        {
            const auto &all = cache.getAll();
            auto it = std::find_if(all.begin(), all.end(), [id](const Color &c)
                                   { return c.getId() == id; });
            if (it != all.end())
                return *it;
            return std::nullopt;
        }

        std::optional<Color> findByName(const std::string &name) const
        {
            const auto &all = cache.getAll();
            std::string searched = adastra::utils::string::trimAndToLower(name);

            auto it = std::find_if(all.begin(), all.end(), [&](const Color &c)
                                   {
                                       std::string cname = adastra::utils::string::trimAndToLower(c.getName());
                                       return cname == searched; });

            if (it != all.end())
                return *it;
            return std::nullopt;
        }
    };
}

#endif
