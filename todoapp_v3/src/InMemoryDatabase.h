#pragma once

#include "Database.h"
#include <string>

class InMemoryDatabase : public Database {
private:
  std::string m_data;

public:
  void write(std::string data) override
  {
    m_data = data;
  }

  std::string read() override
  {
    return m_data;
  }
};
