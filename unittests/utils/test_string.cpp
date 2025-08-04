#include <gtest/gtest.h>
#include <string>
#include <algorithm>

namespace adastra
{
    std::string to_upper(const std::string &input)
    {
        std::string result = input;
        std::transform(result.begin(), result.end(), result.begin(), ::toupper);
        return result;
    }
}

TEST(StringUtils, ToUppercase)
{
    std::string input = "softadastra";
    std::string result = adastra::to_upper(input);
    EXPECT_EQ(result, "SOFTADASTRA");
}
