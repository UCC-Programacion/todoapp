#pragma once

#include "Database.h"
#include <cstddef>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

class TextFileDatabase : public Database {
private:
  std::string m_path;
  char m_delimiter;

public:
  TextFileDatabase(std::string path, char delimiter = '\n')
    : m_path { path }
    , m_delimiter { delimiter }
  {
  }

  void write(std::vector<std::string> lines) override
  {
    std::ofstream os;
    os.open(m_path);
    if (!os.is_open())
      throw std::runtime_error { "unable to open file" };
    // os.write(data.c_str(), data.size());
    for (auto& line : lines)
      os << line << m_delimiter;
  }

  std::vector<std::string> read() override
  {
    std::vector<std::string> lines {};
    std::ifstream is;
    is.open(m_path);
    if (!is.is_open())
      return lines;
    std::string line;
    while (std::getline(is, line, m_delimiter))
      lines.push_back(line);
    return lines;
  }
};
