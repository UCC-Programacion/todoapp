#pragma once

#include <cstddef>
#include <sstream>
#include <string>
#include <vector>

namespace utils {

inline std::string join_strings(std::vector<std::string> strings, std::string delimiter)
{
  std::string out;
  for (int i = 0; i < strings.size(); i++) {
    if (i > 0)
      out += delimiter;
    out += strings[i];
  }
  return out;
}

inline std::vector<std::string> split_string(std::string str, std::string delimiter)
{
  // https://oceanai.mit.edu/ivpman/pdfs/lab_cpp_06_deserial.pdf
  std::vector<std::string> out;
  if (str.empty())
    return out;
  size_t start = 0;
  size_t pos = str.find(delimiter, start);
  while (pos != std::string::npos) {
    out.push_back(str.substr(start, pos - start));
    start = pos + delimiter.size();
    pos = str.find(delimiter, start);
  }
  out.push_back(str.substr(start));
  return out;
}

inline std::string join_strings_v2(std::vector<std::string> strings, char delimiter)
{
  std::ostringstream oss;
  for (size_t i = 0; i < strings.size(); i++) {
    if (i > 0)
      oss << delimiter;
    oss << strings[i];
  }
  return oss.str();
}

inline std::vector<std::string> split_string_v2(std::string str, char delimiter)
{
  std::vector<std::string> out;
  std::stringstream ss { str };
  std::string token;
  while (std::getline(ss, token, delimiter))
    out.push_back(token);
  return out;
}

}
