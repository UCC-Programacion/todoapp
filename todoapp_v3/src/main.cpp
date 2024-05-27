#include "TextFileDatabase.h"
#include "TodoService.h"
#include <cassert>

int main()
{
  std::string db_path = "todos_db.txt";
  TextFileDatabase db { db_path };
  TodoService todo_service { db };
  return 0;
}
