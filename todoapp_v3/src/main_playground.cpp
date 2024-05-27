
#include "InMemoryDatabase.h"
#include "TextFileDatabase.h"
#include "TodoService.h"
#include "string_utils.h"
#include <cassert>
#include <cstddef>
#include <format>
#include <iostream>

void test_string_utils()
{
  using utils::join_strings;
  using utils::join_strings_v2;
  using utils::split_string;
  using utils::split_string_v2;

  assert(join_strings(split_string("a,b,c", ","), ",") == "a,b,c");
  assert(join_strings_v2(split_string_v2("a,b,c", ','), ',') == "a,b,c");

  std::cout << join_strings({ "a", "b", "c" }, ",") << "\n";
  std::cout << join_strings({ "a" }, ",") << "\n";
  std::cout << join_strings({}, ",") << "\n";
  std::cout << join_strings_v2({ "a", "b", "c" }, ',') << "\n";
  std::cout << join_strings_v2({ "a" }, ',') << "\n";
  std::cout << join_strings_v2({}, ',') << "\n";
}

void test_file_db()
{
  TextFileDatabase f { "test_file_db.txt" };
  f.write("");
  assert(f.read() == "");
  std::cout << "read: " << f.read() << "\n";
  f.write("bb");
  assert(f.read() == "bb\n");
  std::cout << "read: " << f.read() << "\n";
}

void test_format()
{
  using std::cout;
  using std::format;

  int a = 15;

  cout << format("a = {:10b}\n", a);
  cout << format("a = {:10x}\n", a);
}

void test_todo_service()
{
  using std::cin;
  using std::cout;

  InMemoryDatabase in_memory_db;

  TodoService todo_service { in_memory_db };

  {
    todo_service.create_task("Todo 1");
    todo_service.create_task("Todo 2");
    todo_service.create_task("Todo 3");

    assert(todo_service.get_tasks().size() == 3);
    assert(todo_service.get_completed_tasks().size() == 0);
    assert(todo_service.get_not_completed_tasks().size() == 3);

    cout << todo_service << "\n";
  }

  {
    Task t = todo_service.get_tasks().at(1);
    todo_service.complete_task(t.get_id());
    assert(todo_service.get_completed_tasks().size() == 1);
    assert(todo_service.get_not_completed_tasks().size() == 2);

    cout << todo_service << "\n";
  }

  {
    todo_service.remove_completed_tasks();
    assert(todo_service.get_tasks().size() == 2);
    assert(todo_service.get_completed_tasks().size() == 0);
    assert(todo_service.get_not_completed_tasks().size() == 2);
    cout << todo_service << "\n";

    todo_service.create_task("Todo 4");
    cout << todo_service << "\n";

    assert(todo_service.get_tasks().size() == 3);
    assert(todo_service.get_completed_tasks().size() == 0);
    assert(todo_service.get_not_completed_tasks().size() == 3);
    cout << todo_service << "\n";
  }

  {
    Task t = todo_service.get_tasks().at(2);
    todo_service.set_task_title(t.get_id(), "Todo 44");
    t = todo_service.get_task_by_id(t.get_id());
    assert(t.get_title() == "Todo 44");
  }
}

void test_todo_service_persistence()
{
  std::string db_path = "test_todo_service.txt";

  {
    TextFileDatabase db { db_path };
    db.write("");
  }

  {
    TextFileDatabase db { db_path };
    TodoService todo_service { db };
    assert(todo_service.get_tasks().empty());
    todo_service.create_task("Todo 1");
    assert(todo_service.get_tasks().size() == 1);
  }

  {
    TextFileDatabase db { db_path };
    TodoService todo_service { db };
    assert(todo_service.get_tasks().size() == 1);
  }
}

int main()
{
  test_string_utils();
  test_file_db();
  test_format();
  test_todo_service();
  test_todo_service_persistence();

  return 0;
}
