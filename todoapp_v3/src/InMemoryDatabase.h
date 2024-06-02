#pragma once

#include "Database.h"
#include <string>
#include <vector>

class InMemoryDatabase : public Database {
private:
  std::vector<std::string> m_data {};

public:
  void write(std::vector<std::string> data) override
  {
    m_data = data;
  }

  std::vector<std::string> read() override
  {
    return m_data;
  }
};
