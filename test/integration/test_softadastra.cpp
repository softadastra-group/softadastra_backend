#include <gtest/gtest.h>
#include <softadastra/chat/ChatModule.hpp>
#include <softadastra/box/BoxModule.hpp>

TEST(SoftadastraModules, InitModules) {
    EXPECT_NO_THROW(softadastra::chat::init());
    EXPECT_NO_THROW(softadastra::box::init());
}
