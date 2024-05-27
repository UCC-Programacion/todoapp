#pragma once

#include "Database.h"
#include <cassert>
#include <cstddef>
#include <fstream>
#include <stdexcept>
#include <string>

class TextFileDatabase : public Database {
private:
  std::string m_path;

public:
  TextFileDatabase(std::string path)
    : m_path(path)
  {
  }

  void write(std::string data) override
  {
    std::ofstream os;
    os.open(m_path);
    if (!os.is_open())
      throw std::runtime_error { "unable to open file" };
    // os.write(data.c_str(), data.size());
    os << data;
  }

  std::string read() override
  {
    std::ifstream is;
    is.open(m_path);
    if (!is.is_open())
      return "";
    std::string out;
    std::string line;
    while (std::getline(is, line))
      out += line + "\n";
    return out;
  }
};
