/**
 * @file BracketToken.hpp
 * @author yaishenka
 * @date 21.10.2021
 */
#include <limits>
#include "AbstractToken.hpp"

namespace calculator {
class BracketToken : public AbstractToken {
 public:
  explicit BracketToken(const std::string& string_token);

  [[nodiscard]] size_t GetPriority() const override;

  [[nodiscard]] size_t IsOpening() const;

  [[nodiscard]] static bool IsBracket(char symbol);
};
}