#include "tableOfSquares.cpp"
#include "findPower.cpp"
#include <gtest/gtest.h>

// Function to capture output from cout
testing::AssertionResult CaptureStdout(void(*code)(), const std::string& expected_output) {
    testing::internal::CaptureStdout();
    code();
    std::string output = testing::internal::GetCapturedStdout();
    if (output == expected_output) {
        return testing::AssertionSuccess();
    }
    return testing::AssertionFailure() << "Expected output: " << expected_output << "\nActual output: " << output;
}

TEST(tableOfSquaresTest, TestOutput) {
    std::string expectedOutput =
        "1 1\n"
        "2 4\n"
        "3 9\n"
        "4 16\n"
        "5 25\n";

    ASSERT_TRUE(CaptureStdout([](){ tableOfSquares(5, 1); }, expectedOutput));
}
TEST(PowerTest, PowerOfZero) {
   // EXPECT_EQ(Power(2, 0), 1); // 2^0 = 1
    EXPECT_EQ(Power(0, 0), -1); // 0^0 = Invalid input
}

TEST(PowerTest, PowerOfOne) {
    EXPECT_EQ(Power(2, 1), 2); // 2^1 = 2
    EXPECT_EQ(Power(0, 1), 0); // 0^1 = 1
}

TEST(PowerTest, NegativePower) {
    EXPECT_EQ(Power(2, -2), -1); // Invalid input: power is negative
}
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}