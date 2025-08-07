// AmbassadorService.cpp
#include <softadastra/commerce/products/AmbassadorService.hpp>

namespace softadastra::commerce::products
{
    AmbassadorService::AmbassadorService(std::shared_ptr<adastra::database::Database> db)
        : db_(std::move(db)) {}

    void AmbassadorService::checkAndReward(uint32_t userId)
    {
        auto result = db_->executePreparedQuery(
            "SELECT COUNT(*) AS total FROM products WHERE user_id = ? AND status = 'active'",
            {userId});

        if (result->next())
        {
            int count = result->getInt("total");
            if (count == 3)
            {
                db_->executeUpdate("UPDATE users SET ambassador_points = ambassador_points + 1 WHERE id = ?", {userId});

                std::string message = "🔥 One of your referrals has published 3 products. +1 point!";
                db_->executeUpdate(
                    "INSERT INTO user_notifications (user_id, sender_id, notification_type, message, is_read) VALUES (?, NULL, 'system', ?, 0)",
                    {userId, message});
            }
        }
    }

}
