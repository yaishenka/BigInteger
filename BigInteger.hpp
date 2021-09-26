/**
 * @file BitInteger.hpp
 * @author yaishenka
 * @date 19.09.2021
 */
#pragma once
#include <iostream>
#include <string>
#include <vector>

/**
 * @struct InvalidIntegerFormat
 * @brief Exception is throwing when we can't convert string to BigInteger
 */
struct InvalidIntegerFormat : std::exception {
  [[nodiscard]] const char *what() const noexcept override {
    return "Invalid integer format!";
  }
};

/**
 * @class BigInteger
 * @brief class to store big integers
 */
class BigInteger {
 public:
  BigInteger() = default;
  explicit BigInteger(const std::string& number);
  BigInteger(long long number);

  ~BigInteger() = default;

  [[nodiscard]] size_t GetSize() const { return digits_.size(); }
  [[nodiscard]] bool IsZero() const { return GetSize() == 0; }

  [[nodiscard]] std::string ToString() const;

  BigInteger& operator+=(const BigInteger& value);
  BigInteger& operator-=(const BigInteger& value);
  BigInteger& operator*=(const BigInteger& value);
  BigInteger& operator/=(const BigInteger& value);

  [[nodiscard]] bool IsLessWithoutSign(const BigInteger& other) const;

  [[nodiscard]] bool IsNegative() const {return is_negative_; };

  BigInteger& operator++() {
    *this += 1;
    return *this;
  }

  const BigInteger operator++(int) {
    BigInteger copy = *this;
    *this += 1;
    return copy;
  }

  BigInteger& operator--() {
    *this -= 1;
    return *this;
  }

  const BigInteger operator--(int) {
    BigInteger copy = *this;
    *this -= 1;
    return copy;
  }

  BigInteger operator+() {
    return *this;
  }

  BigInteger operator-() {
    if (IsZero()) {
      return *this;
    }
    auto result = *this;
    result.is_negative_ = !is_negative_;
    return result;
  }

  explicit operator bool() const {
    return !IsZero();
  }

  friend std::istream& operator>>(std::istream& is, BigInteger& number);
 private:
  /**
   *
   * @param left
   * @param right
   * @return left + right
   * @warning This function ignoring signs
   */
  static BigInteger SumPositives(const BigInteger& left,
                                 const BigInteger& right);
  /**
   * @param left
   * @param right
   * @return left - right
   * @warning This function ignoring signs
   */
  static BigInteger SubstractPositives(const BigInteger& left,
                                       const BigInteger& right);

  static BigInteger MultiplyPositives(const BigInteger& left,
                                      const BigInteger& right);

  static BigInteger DividePositives(const BigInteger& left,
                                    const BigInteger& right);

  void RemoveLeadingZeros();

  void ConstructFromString(const std::string& number);

  std::vector<uint8_t> digits_;
  bool is_negative_ = false;
};

BigInteger operator ""_bigint(unsigned long long number);

BigInteger operator+(const BigInteger& left, const BigInteger& right);
BigInteger operator-(const BigInteger& left, const BigInteger& right);
BigInteger operator*(const BigInteger& left, const BigInteger& right);
BigInteger operator/(const BigInteger& left, const BigInteger& right);
BigInteger operator%(const BigInteger& left, const BigInteger& right);

bool operator<(const BigInteger& left, const BigInteger& right);
bool operator>(const BigInteger& left, const BigInteger& right);
bool operator==(const BigInteger& left, const BigInteger& right);
bool operator!=(const BigInteger& left, const BigInteger& right);
bool operator>=(const BigInteger& left, const BigInteger& right);
bool operator<=(const BigInteger& left, const BigInteger& right);

std::istream& operator>>(std::istream& is, BigInteger& number);
std::ostream& operator<<(std::ostream& os, const BigInteger& number);
