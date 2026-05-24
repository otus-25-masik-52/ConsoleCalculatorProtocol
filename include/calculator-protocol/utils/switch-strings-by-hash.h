#pragma once

#include <cstdint>
#include <string_view>

namespace CalculatorProtocol::Utils {

constexpr unsigned char to_lower_ascii(const unsigned char c) noexcept {
  return (c >= 'A' && c <= 'Z') ? static_cast<unsigned char>(c + ('a' - 'A')) : c;
}

constexpr std::uint64_t lower_hash(const std::string_view value) noexcept {
  std::uint64_t hash = 14695981039346656037ULL; // FNV-1a offset basis

  for (unsigned char symbol : value) {
    symbol = to_lower_ascii(symbol);
    hash ^= symbol;
    hash *= 1099511628211ULL; // FNV-1a prime
  }

  return hash;
}

consteval std::uint64_t operator""_lw(const char* value, const std::size_t size) noexcept {
  return lower_hash(std::string_view{value, size});
}

} // namespace CalculatorProtocol::Utils