#pragma once

#include "TodoService.h"

class TodoUI {
private:
  TodoService m_todo_service;

  void show_tasks();

public:
  explicit TodoUI(TodoService& todo_service)
    : m_todo_service { todo_service }
  {
  }

  void show() { }
};
