#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <string_view>

#include "calculator-protocol/utils/switch-strings-by-hash.h"

namespace CalculatorProtocol::Types {

using Utils::lower_hash;
using Utils::operator""_lw;

enum class ResultSource : std::uint8_t { UNKNOWN, CALCULATED, CACHE, DATABASE };

inline std::string to_string(const ResultSource source) {
  switch (source) {
  case ResultSource::CALCULATED:
    return "calculated";
  case ResultSource::CACHE:
    return "cache";
  case ResultSource::DATABASE:
    return "database";
  case ResultSource::UNKNOWN:
  default:
    return "unknown";
  }
}

inline std::optional<ResultSource> result_source_from_string(const std::string_view value) noexcept {
  switch (lower_hash(value)) {
  case "calculated"_lw:
    return ResultSource::CALCULATED;
  case "cache"_lw:
    return ResultSource::CACHE;
  case "database"_lw:
    return ResultSource::DATABASE;
  case "unknown"_lw:
    return ResultSource::UNKNOWN;
  default:
    return std::nullopt;
  }
}

} // namespace CalculatorProtocol::Types
