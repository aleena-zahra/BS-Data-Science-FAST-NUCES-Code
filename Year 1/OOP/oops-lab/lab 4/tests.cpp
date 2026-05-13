#include "q1.cpp"
#include "q3.cpp"
#include <gtest/gtest.h>

TEST(FactorialTest, PositiveNos) {
    ASSERT_EQ(1, factorial(0));
    ASSERT_EQ(1, factorial(1));
    ASSERT_EQ(6, factorial(3));
}
TEST(isPrimeNumTest, PositiveNos) {
    EXPECT_TRUE(isPrimeNum(2,1));
    EXPECT_TRUE(isPrimeNum(6,3));
}



int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}