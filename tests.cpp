/** @author yaishenka
    @date 22.09.2021 */
#include <gtest/gtest.h>
#include "BigInteger.hpp"

TEST(CONSTRUCT_FROM_STRING, CORRECT_1) {
  std::string number = "1000";
  BigInteger integer(number);
  EXPECT_EQ(integer.ToString(), number);
}

TEST(CONSTRUCT_FROM_STRING, CORRECT_2) {
  std::string number = "-1000";
  BigInteger integer(number);
  EXPECT_EQ(integer.ToString(), number);
}

TEST(CONSTRUCT_FROM_STRING, CORRECT_3) {
  std::string number = "+1000";
  BigInteger integer(number);
  EXPECT_EQ(integer.ToString(), "1000");
}

TEST(CONSTRUCT_FROM_STRING, INCORRECT) {
  std::string number = "test1000";
  EXPECT_THROW(BigInteger integer(number), InvalidIntegerFormat);
}

TEST(COMPARE, LESS_1) {
  BigInteger first(1000);
  BigInteger second(10000);

  EXPECT_EQ(first < second, true);
}

TEST(COMPARE, LESS_2) {
  BigInteger first(-10000);
  BigInteger second(-100);

  EXPECT_EQ(first < second, true);
}

TEST(COMPARE, LESS_3) {
  BigInteger first(-10000);
  BigInteger second(100);

  EXPECT_EQ(first < second, true);
}

TEST(COMPARE, LESS_4) {
  BigInteger first(0);
  BigInteger second(0);

  EXPECT_EQ(first < second, false);
}

TEST(COMPARE, LESS_5) {
  BigInteger first(1000);
  BigInteger second(100);

  EXPECT_EQ(first < second, false);
}

TEST(PLUS_EQ, CORRECT_1) {
  long long first_number = 1000;
  long long second_number = 9999;
  BigInteger sum(first_number + second_number);

  BigInteger first_number_big(first_number);
  first_number_big += second_number;

  EXPECT_EQ(first_number_big, sum);
}

TEST(PLUS_EQ, CORRECT_2) {
  long long first_number = -1000;
  long long second_number = 9999;
  BigInteger sum(first_number + second_number);

  BigInteger first_number_big(first_number);
  first_number_big += second_number;

  EXPECT_EQ(first_number_big, sum);
}

TEST(PLUS_EQ, CORRECT_3) {
  long long first_number = 1000;
  long long second_number = -9999;
  BigInteger sum(first_number + second_number);

  BigInteger first_number_big(first_number);
  first_number_big += second_number;

  EXPECT_EQ(first_number_big, sum);
}

TEST(PLUS_EQ, CORRECT_4) {
  long long first_number = -1000;
  long long second_number = -9999;
  BigInteger sum(first_number + second_number);

  BigInteger first_number_big(first_number);
  first_number_big += second_number;

  EXPECT_EQ(first_number_big, sum);
}

TEST(MINUS_EQ, CORRECT_1) {
  long long first_number = 1000;
  long long second_number = 9999;
  BigInteger sum(first_number - second_number);

  BigInteger first_number_big(first_number);
  first_number_big -= second_number;

  EXPECT_EQ(first_number_big, sum);
}

TEST(MINUS_EQ, CORRECT_2) {
  long long first_number = -1000;
  long long second_number = 9999;
  BigInteger sum(first_number - second_number);

  BigInteger first_number_big(first_number);
  first_number_big -= second_number;

  EXPECT_EQ(first_number_big, sum);
}

TEST(MINUS_EQ, CORRECT_3) {
  long long first_number = 1000;
  long long second_number = -9999;
  BigInteger sum(first_number - second_number);

  BigInteger first_number_big(first_number);
  first_number_big -= second_number;

  EXPECT_EQ(first_number_big, sum);
}

TEST(MINUS_EQ, CORRECT_4) {
  long long first_number = -1000;
  long long second_number = -9999;
  BigInteger sum(first_number - second_number);

  BigInteger first_number_big(first_number);
  first_number_big -= second_number;

  EXPECT_EQ(first_number_big, sum);
}

TEST(PLUS, CORRECT_1) {
  long long first_number = 1000;
  long long second_number = 9999;
  BigInteger sum(first_number + second_number);

  BigInteger first_number_big(first_number);
  BigInteger second_number_big(second_number);

  EXPECT_EQ(first_number_big + second_number_big, sum);
}

TEST(PLUS, CORRECT_2) {
  long long first_number = 100;
  long long second_number = 200;
  BigInteger sum(first_number + second_number);

  BigInteger first_number_big(first_number);
  BigInteger second_number_big(second_number);

  EXPECT_EQ(first_number_big + second_number_big, sum);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
