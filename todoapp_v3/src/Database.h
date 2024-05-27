#pragma once

#include <string>

class Database {
public:
  virtual void write(std::string data) = 0;
  virtual std::string read() = 0;
};
