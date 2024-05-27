#pragma once

#include <format>
#include <iostream>
#include <stdexcept>
#include <string>

class Task {
private:
  std::string m_id;
  std::string m_title;
  bool m_completed;

public:
  Task(const std::string& id, const std::string& title, bool completed = false)
    : m_id { id }
    , m_title { title }
    , m_completed { completed }
  {
    if (id.empty())
      throw std::invalid_argument { "id is empty" };
    if (title.empty())
      throw std::invalid_argument { "title is empty" };
  }

  std::string get_id() const
  {
    return m_id;
  }

  std::string get_title() const
  {
    return m_title;
  }

  bool get_completed() const
  {
    return m_completed;
  }

  void toggle_completed()
  {
    m_completed = !m_completed;
  }

  void set_title(const std::string& title)
  {
    if (title.empty())
      throw std::invalid_argument { "title is empty" };
    m_title = title;
  }
};

inline std::ostream& operator<<(std::ostream& out, const Task& task)
{
  out << std::format("Task ({}, {}, {})", task.get_id(), task.get_title(), task.get_completed());
  return out;
}
