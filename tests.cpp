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

TEST(Multiply, CORRECT_1) {
  long long first_number = 100;
  long long second_number = 200;
  BigInteger composition(first_number * second_number);

  BigInteger first_number_big(first_number);
  BigInteger second_number_big(second_number);

  EXPECT_EQ(first_number_big * second_number_big, composition);
}

TEST(Multiply, CORRECT_2) {
  long long first_number = -100;
  long long second_number = 200;
  BigInteger composition(first_number * second_number);

  BigInteger first_number_big(first_number);
  BigInteger second_number_big(second_number);

  EXPECT_EQ(first_number_big * second_number_big, composition);
}

TEST(Multiply, CORRECT_3) {
  long long first_number = 0;
  long long second_number = 200;
  BigInteger composition(first_number * second_number);

  BigInteger first_number_big(first_number);
  BigInteger second_number_big(second_number);

  EXPECT_EQ(first_number_big * second_number_big, composition);
}

TEST(Multiply, CORRECT_4) {
  long long first_number = -1;
  long long second_number = 200;
  BigInteger composition(first_number * second_number);

  BigInteger first_number_big(first_number);
  BigInteger second_number_big(second_number);

  EXPECT_EQ(first_number_big * second_number_big, composition);
}

TEST(Divide, CORRECT_1) {
  EXPECT_EQ(100_bigint / 200_bigint, 100 / 200);
}

TEST(Divide, CORRECT_2) {
  EXPECT_EQ(1000_bigint / 300_bigint, 1000 / 300);
}

TEST(Divide, CORRECT_3) {
  EXPECT_EQ(24_bigint / 2_bigint, 24 / 2);
}

TEST(Mod, CORRECT_1) {
  EXPECT_EQ(100_bigint % 2, 100 % 2);
}

TEST(Mod, CORRECT_2) {
  EXPECT_EQ(101_bigint % 2, 101 % 2);
}

TEST(Mod, CORRECT_3) {
  EXPECT_EQ(24_bigint % 2, 24 % 2);
}


int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
