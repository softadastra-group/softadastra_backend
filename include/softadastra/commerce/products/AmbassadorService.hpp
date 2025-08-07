// AmbassadorService.hpp
#ifndef AMBASSADOR_SERVICE_HPP
#define AMBASSADOR_SERVICE_HPP

#include <memory>
#include <adastra/database/Database.hpp>

namespace softadastra::commerce::products
{
    class AmbassadorService
    {
    public:
        explicit AmbassadorService(std::shared_ptr<adastra::database::Database> db);
        void checkAndReward(uint32_t userId);

    private:
        std::shared_ptr<adastra::database::Database> db_;
    };
}

#endif
