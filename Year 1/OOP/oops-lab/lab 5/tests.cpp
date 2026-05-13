#include "q1.cpp"
#include "q2.cpp"
#include "q3.cpp"
#include "q4.cpp"
#include "q5.cpp"
#include <gtest/gtest.h>
//q1
TEST(FactorialTest, PositiveNos) {
    ASSERT_EQ(1, factorial(0));
    ASSERT_EQ(1, factorial(1));
    ASSERT_EQ(6, factorial(3));
    ASSERT_EQ(-1, factorial(-3));
}
//q2
TEST(findTargetTest, PositiveNos) {
    int arr1[5]={1,2,3,0,9};
    ASSERT_EQ(0, findTarget(arr1,5,1));
    int arr2[3]={1,15,-3};
    ASSERT_EQ(2, findTarget(arr2,2,-3));
    int arr3[3]={1,2,3};
    ASSERT_EQ(2, findTarget(arr3,2,3));
}
//q3
TEST(isPrimeNumTest, PositiveNos) {
    EXPECT_TRUE(isPrimeNum(2,2/2));
    EXPECT_TRUE(isPrimeNum(6,6/2));//does fail 
    EXPECT_FALSE(isPrimeNum(-1,-1/2));
}
//q4
TEST(consonantCountTest, PositiveNos) {
    string str1 = "islamabad";
    ASSERT_EQ(5, consonantCount(str1,0));
    string str2 = "this";
    ASSERT_EQ(3, consonantCount(str2,0));
    string str3 = "abebibobu";
    ASSERT_EQ(4, consonantCount(str3,0));
}
//q5
TEST(sumArrTest, PositiveNos) {
    int arr1[3]={1,2,3};
    ASSERT_EQ(6, sumArr(arr1,3,0));
    int arr2[5]={0,0,1,2,4};
    ASSERT_EQ(7, sumArr(arr2,5,0));
    int arr3[3]={1,1,-1};//negative value
    ASSERT_EQ(1, sumArr(arr3,3,0));
}
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
