/**
 * @file Utils.hpp
 * @author yaishenka
 * @date 19.10.2021
 */
#include <iostream>

namespace utils {
template <class Class>
struct HasIstreamOperatorImpl {
 public:
  template <class V>
  static auto HasIstreamOperatorCheck(V*)
  -> decltype(std::declval<std::istream&>() >> std::declval<V&>());

  template <typename>
  static auto HasIstreamOperatorCheck(...) -> std::false_type;

  using Type = typename std::is_same<
      std::istream&, decltype(HasIstreamOperatorCheck<Class>(nullptr))>::type;
};

template <class Class>
const bool HasIstreamOperatorV = HasIstreamOperatorImpl<Class>::Type::value;

template <class Class>
struct HasOstreamOperatorImpl {
 public:
  template <class V>
  static auto HasOstreamOperatorCheck(V*)
  -> decltype(std::declval<std::ostream&>() << std::declval<V>());

  template <typename>
  static auto HasOstreamOperatorCheck(...) -> std::false_type;

  using Type = typename std::is_same<
      std::ostream&, decltype(HasOstreamOperatorCheck<Class>(nullptr))>::type;
};

template <class Class>
const bool HasOstreamOperatorV = HasOstreamOperatorImpl<Class>::Type::value;
}
