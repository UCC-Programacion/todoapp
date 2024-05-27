#pragma once

#include <iostream>
#include <random>

namespace utils {

inline std::string random_id(std::size_t length)
{
  static const std::string_view hex_chars = "0123456789abcdef";

  auto const seed = std::random_device {}();
  std::mt19937 engine { seed };
  std::uniform_int_distribution<size_t> distribution { 0, 15 };

  std::string id;
  id.reserve(length);
  for (auto i = 0; i < length; i++)
    id.push_back(hex_chars.at(distribution(engine)));

  return id;
}

inline void reset_cin()
{
  // clear all error status bits
  std::cin.clear();
  // clear input buffer
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

}
