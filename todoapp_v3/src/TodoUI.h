#pragma once

#include "Task.h"
#include "TodoService.h"
#include "utils_io.h"
#include <format>
#include <stdexcept>
#include <string>
#include <vector>

class TodoUI {
private:
  TodoService& m_todo_service;

  void create_task()
  {
    std::cout << "Crear tarea\n"
              << "===========\n";

    try {
      std::cout << "Ingrese el titulo: ";
      std::string title;
      std::getline(std::cin, title);

      Task task = m_todo_service.create_task(title);
      std::cout << "Se creo la tarea " << task.get_id() << "\n";
    } catch (const std::invalid_argument& e) {
      std::cout << "Error al crear la tarea: " << e.what() << ". Intente de nuevo.\n";
    }
  }

  void show_task(const Task& task)
  {
    std::cout << "Id: " << task.get_id() << "\n"
              << "Titulo: " << task.get_title() << "\n"
              << "Completada: " << (task.get_completed() ? "si" : "no") << "\n"
              << "\n";
  }

  void search_task()
  {
    std::cout << "Buscar tarea\n"
              << "============\n";
    try {
      std::cout << "Ingrese el id: ";
      std::string id;
      std::cin >> id;

      show_task(m_todo_service.find(id));
    } catch (const TodoService::TaskNotFoundError& e) {
      std::cout << "No se encontro la tarea. Intente de nuevo.\n";
    }
  }

  void complete_task()
  {
    std::cout << "Completar tarea\n"
              << "===============\n";
    try {
      std::cout << "Ingrese el id: ";
      std::string id;
      std::cin >> id;

      m_todo_service.complete_task(id);
    } catch (const TodoService::TaskNotFoundError& e) {
      std::cout << "No se encontro la tarea. Intente de nuevo.\n";
    }
  }

  void remove_task()
  {
    std::cout << "Borrar tarea\n"
              << "===============\n";
    try {
      std::cout << "Ingrese el id: ";
      std::string id;
      std::cin >> id;

      m_todo_service.delete_task(id);

      std::cout << "Se borro la tarea " + id << "\n";
    } catch (const TodoService::TaskNotFoundError& e) {
      std::cout << "No se encontro la tarea. Intente de nuevo.\n";
    }
  }

  void update_task_title()
  {
    std::cout << "Actualizar tarea\n"
              << "================\n";
    try {
      std::cout << "Ingrese el id: ";
      std::string id;
      std::cin >> id;
      utils::ignoreLine();

      std::cout << "Ingrese el titulo: ";
      std::string title;
      std::getline(std::cin, title);

      m_todo_service.set_task_title(id, title);
    } catch (const TodoService::TaskNotFoundError& e) {
      std::cout << "No se encontro la tarea. Intente de nuevo.\n";
    }
  }

  void remove_completed_tasks()
  {
    int completed_task_count = m_todo_service.get_completed_tasks().size();
    m_todo_service.remove_completed_tasks();
    std::cout << "Se borraron " << completed_task_count << " tareas completadas\n";
  }

  void show_tasks_table(const std::vector<Task>& tasks)
  {
    std::cout << std::format("{:8}", "Id")
              << " "
              << std::format("{:25}", "Titulo")
              << " "
              << std::format("{:15}", "Esta completa?")
              << "\n"
              << "--------------------------------------------"
              << "\n";
    for (auto& task : tasks) {
      std::cout << std::format("{:8}", task.get_id())
                << " "
                << std::format("{:25}",
                     task.get_title().size() > 24 ? (task.get_title().substr(0, 21) + "...") : task.get_title())
                << " "
                << std::format("{:15}", task.get_completed() ? "si" : "no")
                << "\n";
    }
    std::cout << "\n\n";
  }

  void show_tasks()
  {
    std::cout << "Tareas\n"
              << "======\n";

    auto tasks = m_todo_service.get_tasks();
    if (tasks.empty()) {
      std::cout << "No hay tareas\n";
      return;
    }
    show_tasks_table(tasks);
  }

  void show_completed_tasks()
  {
    std::cout << "Tareas completadas\n"
              << "==================\n";

    auto tasks = m_todo_service.get_completed_tasks();
    if (tasks.empty()) {
      std::cout << "No hay tareas completadas\n";
      return;
    }
    show_tasks_table(tasks);
  }

  void show_not_completed_tasks()
  {
    std::cout << "Tareas no completadas\n"
              << "=====================\n";

    auto tasks = m_todo_service.get_not_completed_tasks();
    if (tasks.empty()) {
      std::cout << "No hay tareas sin completar\n";
      return;
    }
    show_tasks_table(tasks);
  }

  void process_menu_option(int option)
  {
    switch (option) {
    case 1: {
      show_tasks();
      break;
    }
    case 2: {
      show_completed_tasks();
      break;
    }
    case 3: {
      show_not_completed_tasks();
      break;
    }
    case 4: {
      create_task();
      break;
    }
    case 5: {
      search_task();
      break;
    }
    case 6: {
      complete_task();
      break;
    }
    case 7: {
      update_task_title();
      break;
    }
    case 8: {
      remove_task();
      break;
    }
    case 9: {
      remove_completed_tasks();
      break;
    }
    case 10: {
      throw NotImplementedMenuOptionError {};
      break;
    }
    default: {
      throw InvalidMenuOptionError {};
      break;
    }
    }
  }

  void show_menu()
  {
    while (true) {
      std::cout << "\n"
                << "Menu\n"
                << "====\n"
                << "1. Mostrar tareas\n"
                << "2. Mostrar tareas completadas\n"
                << "3. Mostrar tareas no completadas\n"
                << "4. Crear tarea\n"
                << "5. Buscar tarea\n"
                << "6. Completar una tarea\n"
                << "7. Actualizar titulo de una tarea\n"
                << "8. Borrar una tarea\n"
                << "9. Borrar tareas completadas\n"
                << "0. Salir\n\n";

      int option = utils::get_int(
        "Seleccione una opcion: ",
        "La opcion seleccionada no es valida. Intente de nuevo.\n");

      if (option == 0)
        break;

      std::cout << "\n";

      try {
        process_menu_option(option);
      } catch (const NotImplementedMenuOptionError& e) {
        std::cout << "La opcion seleccionada no esta implementada.\n";
      } catch (const InvalidMenuOptionError& e) {
        std::cout << "La opcion seleccionada no es valida.\n";
      }
    }
  }

public:
  TodoUI(TodoService& todo_service)
    : m_todo_service { todo_service }
  {
  }

  class NotImplementedMenuOptionError : public std::logic_error {
  public:
    NotImplementedMenuOptionError()
      : std::logic_error { "not implemented menu option" }
    {
    }
  };

  class InvalidMenuOptionError : public std::logic_error {
  public:
    InvalidMenuOptionError()
      : std::logic_error { "invalid menu option" }
    {
    }
  };

  void show()
  {
    show_menu();
  }
};
