#pragma once

#include "Database.h"
#include "Task.h"
#include "string_utils.h"
#include "utils.h"
#include <cstddef>
#include <iterator>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

class TodoService {
private:
  Database& m_database;
  std::map<std::string, Task> m_tasks;

  static inline const size_t ID_LENGTH { 4 };

  static std::string random_id()
  {
    return utils::random_id(ID_LENGTH);
  }

  static inline const std::string TASK_DELIMITER { "\n" };
  static inline const std::string TASK_FIELD_DELIMITER { "," };

  static std::string task_to_string(const Task& task)
  {
    return utils::join_strings(
      { task.get_id(), task.get_title(), task.get_completed() ? "1" : "0" },
      TASK_FIELD_DELIMITER);
  }

  static Task task_from_string(const std::string& task_str)
  {
    std::vector<std::string> task_items = utils::split_string(task_str, TASK_FIELD_DELIMITER);
    std::string id = task_items[0];
    std::string title = task_items[1];
    bool completed = task_items[2] == "0" ? false : true;
    return Task { id, title, completed };
  }

  void load_tasks()
  {
    std::string tasks_str = m_database.read();
    std::vector<std::string> tasks_lines = utils::split_string(tasks_str, TASK_DELIMITER);
    for (size_t i = 0; i < tasks_lines.size(); i++) {
      if (tasks_lines[i].empty())
        continue;
      Task task = task_from_string(tasks_lines[i]);
      m_tasks.insert({ task.get_id(), task });
    }
  }

  void save_tasks()
  {
    std::vector<std::string> task_lines;
    for (const auto& pair : m_tasks) {
      const Task& t = pair.second;
      task_lines.push_back(task_to_string(t));
    }
    std::string tasks_str = utils::join_strings(task_lines, TASK_DELIMITER);
    m_database.write(tasks_str);
  }

public:
  TodoService(Database& database)
    : m_database { database }
  {
    load_tasks();
  }

  ~TodoService()
  {
    save_tasks();
  }

  class TaskNotFoundError : public std::logic_error {
  public:
    TaskNotFoundError(const std::string& id)
      : std::logic_error { "task '" + id + "'not found" }
    {
    }
  };

  void add_task(const Task& t)
  {
    if (m_tasks.contains(t.get_id()))
      throw std::logic_error { "task id already in use" };

    m_tasks.insert({ t.get_id(), t });
  }

  Task create_task(const std::string& title)
  {
    auto id = random_id();
    while (m_tasks.contains(id))
      id = random_id();

    Task task { id, title };
    m_tasks.insert({ id, task });

    return task;
  }

  Task find(const std::string& id)
  {
    if (!m_tasks.contains(id))
      throw TaskNotFoundError { id };
    return m_tasks.at(id);
  }

  void delete_task(const std::string& id)
  {
    if (!m_tasks.contains(id))
      throw TaskNotFoundError { id };

    m_tasks.erase(id);
  }

  void complete_task(const std::string& id)
  {
    if (!m_tasks.contains(id))
      throw TaskNotFoundError { id };

    m_tasks.at(id).toggle_completed();
  }

  void set_task_title(const std::string& id, const std::string& title)
  {
    if (!m_tasks.contains(id))
      throw TaskNotFoundError { id };

    m_tasks.at(id).set_title(title);
  }

  std::vector<Task> get_tasks() const
  {
    std::vector<Task> out;
    for (auto&& pair : m_tasks)
      out.push_back(pair.second);
    return out;
  }

  std::vector<Task> get_tasks_v2() const
  {
    std::vector<Task> out;
    out.reserve(m_tasks.size());
    std::transform(
      m_tasks.begin(),
      m_tasks.end(),
      std::back_inserter(out),
      [](auto&& pair) { return pair.second; });
    return out;
  }

  std::vector<Task> get_completed_tasks() const
  {
    std::vector<Task> out;
    auto tasks = get_tasks();
    for (size_t i = 0; i < tasks.size(); i++)
      if (tasks[i].get_completed())
        out.push_back(tasks[i]);
    return out;
  }

  std::vector<Task> get_completed_tasks_v2() const
  {
    auto tasks = get_tasks();
    std::erase_if(tasks, [](auto&& t) { return !t.get_completed(); });
    return tasks;
  }

  std::vector<Task> get_not_completed_tasks() const
  {
    auto is_completed = [](auto&& t) { return t.get_completed(); };
    auto tasks = get_tasks();
    std::erase_if(tasks, is_completed);
    return tasks;
  }

  Task get_task_by_id(const std::string& id) const
  {
    if (!m_tasks.contains(id))
      throw TaskNotFoundError { id };

    return m_tasks.at(id);
  }

  void remove_completed_tasks()
  {
    std::erase_if(m_tasks, [](auto&& pair) { return pair.second.get_completed(); });
  }
};

inline std::ostream& operator<<(std::ostream& out, const TodoService& todo_service)
{
  out << "TodoService {\n"
      << " Tasks {\n";
  for (auto&& t : todo_service.get_tasks())
    out << "  " << t << "\n";
  out << " }\n"
      << "}\n";
  return out;
}
