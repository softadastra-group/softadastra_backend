#include <gtest/gtest.h>
#include <softadastra/pay/PayModule.hpp>

TEST(SoftadastraPay, InitDoesNotThrow)
{
    EXPECT_NO_THROW(softadastra::pay::init());
}
