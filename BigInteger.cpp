#include "BigInteger.hpp"

#include <cctype>
#include <exception>

BigInteger::BigInteger(const std::string& number) {
  ConstructFromString(number);
}

BigInteger::BigInteger(long long number) {
  if (number == 0) {
    return;
  }

  is_negative_ = number < 0;

  if (is_negative_) {
    number *= -1;
  }

  do {
    digits_.emplace_back(number % 10);
    number /= 10;
  } while (number > 0);
}

std::string BigInteger::ToString() const {
  if (IsZero()) {
    return "0";
  }

  std::string result;

  if (is_negative_) {
    result += '-';
  }

  for (ssize_t index = GetSize() - 1; index >= 0; --index) {
    result += digits_[index] + '0';
  }

  return result;
}

BigInteger& BigInteger::operator+=(const BigInteger& value) {
  if (!(is_negative_ ^ value.is_negative_)) {
    *this = BigInteger::SumPositives(*this, value);
    is_negative_ = value.is_negative_;
    return *this;
  }

  if (!is_negative_ && value.IsLessWithoutSign(*this)) {
    *this -= value;
    return *this;
  }

  if (!is_negative_ && IsLessWithoutSign(value)) {
    *this = BigInteger::SubstractPositives(value, *this);
    is_negative_ = true;
    return *this;
  }

  if (value.IsLessWithoutSign(*this)) {
    *this -= value;
    is_negative_ = true;
    return *this;
  }

  *this = BigInteger::SubstractPositives(value, *this);
  is_negative_ = false;
  return *this;
}

BigInteger& BigInteger::operator-=(const BigInteger& value) {
  if (!is_negative_ && !value.is_negative_) {
    if (value.IsLessWithoutSign(*this)) {
      *this = SubstractPositives(*this, value);
    } else {
      *this = SubstractPositives(value, *this);
      is_negative_ = true;
    }

    if (IsZero()) {
      is_negative_ = false;
    }

    return *this;
  }

  if (!is_negative_ && value.is_negative_) {
    *this = SumPositives(*this, value);

    if (IsZero()) {
      is_negative_ = false;
    }

    return *this;
  }

  if (value.is_negative_) {
    if (value.IsLessWithoutSign(*this)) {
      *this = SubstractPositives(*this, value);
      is_negative_ = true;
    } else {
      *this = SubstractPositives(value, *this);
    }

    if (IsZero()) {
      is_negative_ = false;
    }

    return *this;
  }

  *this = SumPositives(*this, value);
  is_negative_ = true;

  if (IsZero()) {
    is_negative_ = false;
  }

  return *this;
}

BigInteger& BigInteger::operator*=(const BigInteger& other) {
  auto result_sign = is_negative_ ^ other.is_negative_;
  *this = MultiplyPositives(*this, other);
  is_negative_ = result_sign;

  return *this;
}

BigInteger& BigInteger::operator/=(const BigInteger& other) {
  auto result_sign = is_negative_ ^ other.is_negative_;
  *this = DividePositives(*this, other);
  is_negative_ = result_sign;

  return *this;
}

[[nodiscard]] bool BigInteger::IsLessWithoutSign(
    const BigInteger& other) const {
  if (IsZero() && other.IsZero()) {
    return false;
  }

  if (GetSize() != other.GetSize()) {
    return GetSize() < other.GetSize();
  }

  for (ssize_t index = GetSize() - 1; index >= 0; --index) {
    if (digits_[index] != other.digits_[index]) {
      return digits_[index] < other.digits_[index];
    }
  }

  return false;
}

BigInteger BigInteger::SumPositives(const BigInteger& left,
                                    const BigInteger& right) {
  BigInteger result;
  if (left.IsZero() && right.IsZero()) {
    return result;
  }
  size_t index = 0;
  uint8_t transfer = 0;
  for (; index < std::min(left.GetSize(), right.GetSize()); ++index) {
    auto left_digit = left.digits_[index];
    auto right_digit = right.digits_[index];
    auto result_sum = left_digit + right_digit + transfer;
    result.digits_.emplace_back((result_sum) % 10);
    transfer = result_sum / 10;
  }

  for (; index < std::max(left.GetSize(), right.GetSize()); ++index) {
    uint8_t result_sum = 0;
    if (index < left.GetSize()) {
      result_sum = left.digits_[index] + transfer;
    } else {
      result_sum = right.digits_[index] + transfer;
    }

    result.digits_.emplace_back(result_sum % 10);
    transfer = result_sum / 10;
  }

  if (transfer > 0) {
    result.digits_.emplace_back(transfer);
  }

  result.RemoveLeadingZeros();

  return result;
}

BigInteger BigInteger::SubstractPositives(const BigInteger& left,
                                          const BigInteger& right) {
  BigInteger result;
  if (left.IsZero() && right.IsZero()) {
    return result;
  }

  size_t index = 0;
  uint8_t left_digit = left.digits_[index];
  for (; index < std::max(left.GetSize(), right.GetSize()); ++index) {
    if (index >= right.GetSize()) {
      result.digits_.emplace_back(left_digit);
      if (index != std::max(left.GetSize(), right.GetSize()) - 1) {
        left_digit = left.digits_[index + 1];
      }
      continue;
    }
    if (left_digit < right.digits_[index]) {
      result.digits_.push_back(left_digit + 10 - right.digits_[index]);
      ++index;
      left_digit = left.digits_[index];
      while (left.digits_[index] == 0) {
        left_digit = left.digits_[index];
        if (index < right.GetSize()) {
          result.digits_.push_back(left_digit + 9 - right.digits_[index]);
        } else {
          result.digits_.push_back(left_digit + 9);
        }
        ++index;
      }
      left_digit = left.digits_[index];
      left_digit -= 1;
      index -= 1;
      continue;
    }

    result.digits_.push_back(left_digit - right.digits_[index]);

    if (index != std::max(left.GetSize(), right.GetSize()) - 1) {
      left_digit = left.digits_[index + 1];
    }
  }

  result.RemoveLeadingZeros();

  return result;
}

BigInteger BigInteger::MultiplyPositives(const BigInteger& left,
                                         const BigInteger& right) {
  BigInteger result;
  if (left.IsZero() || right.IsZero()) {
    return result;
  }

  result.digits_.resize(left.GetSize() + right.GetSize() + 2);

  for (size_t i = 0; i < left.GetSize(); ++i) {
    uint8_t transfer = 0;
    for (size_t j = 0; j < right.GetSize() || transfer != 0; ++j) {
      uint8_t current = 0;
      if (j == right.GetSize()) {
        current = 0;
      } else {
        current = left.digits_[i] * right.digits_[j];
      }
      uint8_t current_compos = result.digits_[i + j] + current + transfer;
      result.digits_[i + j] = current_compos % 10;
      transfer = current_compos / 10;
    }
  }

  result.RemoveLeadingZeros();
  return result;
}

BigInteger BigInteger::DividePositives(const BigInteger& left,
                                       const BigInteger& right) {
  if (right.IsZero()) {
    throw std::overflow_error("Divide by zero exception");
  }

  BigInteger result;

  if (left.IsLessWithoutSign(right)) {
    return result;
  }

  result.digits_.resize(left.GetSize());
  BigInteger curr_value;

  for (ssize_t i = left.GetSize() - 1; i >= 0; --i) {
    curr_value.digits_.insert(curr_value.digits_.begin(), 0);
    while (curr_value.GetSize() > 1 && *(--curr_value.digits_.end()) == 0) {
      curr_value.digits_.pop_back();
    }
    curr_value.digits_[0] = left.digits_[i];
    int x = 0;
    int left_border = 0;
    int right_border = 9;
    while (left_border <= right_border) {
      int mid = (left_border + right_border) / 2;
      BigInteger current;
      current = right * mid;
      if (current <= curr_value) {
        x = mid;
        left_border = mid + 1;
      } else
        right_border = mid - 1;
    }
    result.digits_[i] = x;
    curr_value -= right * x;
  }
  result.RemoveLeadingZeros();
  return result;
}

void BigInteger::RemoveLeadingZeros() {
  if (GetSize() == 0) {
    return;
  }

  ssize_t index = GetSize() - 1;

  for (; index >= 0; --index) {
    if (digits_[index] != 0) {
      break;
    }
  }

  digits_.resize(index + 1);
}

void BigInteger::ConstructFromString(const std::string& number) {
  digits_.clear();
  is_negative_ = false;

  if (number.empty()) {
    return;
  }

  ssize_t begin_to_parse_index = 0;

  if (!std::isdigit(number[begin_to_parse_index])) {
    if (number[begin_to_parse_index] == '-') {
      is_negative_ = true;
    } else if (number[begin_to_parse_index] == '+') {
      is_negative_ = false;
    } else {
      throw InvalidIntegerFormat();
    }

    begin_to_parse_index += 1;
  }

  for (; begin_to_parse_index < number.length(); ++begin_to_parse_index) {
    if (number[begin_to_parse_index] != '0') {
      break;
    }
  }

  for (ssize_t current_position = number.length() - 1;
       current_position >= begin_to_parse_index; --current_position) {
    char current_symbol = number[current_position];

    if (!std::isdigit(current_symbol)) {
      throw InvalidIntegerFormat();
    }

    digits_.push_back(current_symbol - '0');
  }

  if (IsZero()) {
    is_negative_ = false;
  }
}

BigInteger operator""_bigint(unsigned long long number) {
  return BigInteger(number);
}

BigInteger operator+(const BigInteger& left, const BigInteger& right) {
  BigInteger copy = left;
  copy += right;
  return copy;
}

BigInteger operator-(const BigInteger& left, const BigInteger& right) {
  BigInteger copy = left;
  copy -= right;
  return copy;
}

BigInteger operator*(const BigInteger& left, const BigInteger& right) {
  BigInteger copy = left;
  copy *= right;
  return copy;
}

BigInteger operator/(const BigInteger& left, const BigInteger& right) {
  BigInteger copy = left;
  copy /= right;
  return copy;
}

BigInteger operator%(const BigInteger& left, const BigInteger& right) {
  auto divide = left / right;
  auto product = divide * right;
  auto result = left - product;
  return result;
}

bool operator<(const BigInteger& left, const BigInteger& right) {
  if (left.IsZero() && right.IsZero()) {
    return false;
  }

  if (left.IsNegative() && !right.IsNegative()) {
    return true;
  }

  if (!left.IsNegative() && right.IsNegative()) {
    return false;
  }

  if (left.IsNegative() && right.IsNegative()) {
    return right.IsLessWithoutSign(left);
  }

  if (!left.IsNegative() && !right.IsNegative()) {
    return left.IsLessWithoutSign(right);
  }

  return false;
}

bool operator>(const BigInteger& left, const BigInteger& right) {
  return right < left;
}

bool operator==(const BigInteger& left, const BigInteger& right) {
  return !(left < right || right < left);
}

bool operator!=(const BigInteger& left, const BigInteger& right) {
  return !(left == right);
}

bool operator>=(const BigInteger& left, const BigInteger& right) {
  return left > right || left == right;
}
bool operator<=(const BigInteger& left, const BigInteger& right) {
  return left < right || left == right;
}

std::istream& operator>>(std::istream& is, BigInteger& number) {
  std::string number_str;
  is >> number_str;
  number.ConstructFromString(number_str);
  return is;
}

std::ostream& operator<<(std::ostream& os, const BigInteger& number) {
  os << number.ToString();
  return os;
}