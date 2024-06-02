#pragma once

#include <string>
#include <vector>

class Database {
public:
  virtual void write(std::vector<std::string> data) = 0;
  virtual std::vector<std::string> read() = 0;
};
