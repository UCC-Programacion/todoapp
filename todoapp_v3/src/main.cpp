#include "TextFileDatabase.h"
#include "TodoService.h"
#include "TodoUI.h"

int main()
{
  std::string db_path = "todos_db.txt";
  TextFileDatabase db { db_path };
  TodoService todo_service { db };
  TodoUI ui { todo_service };
  ui.show();

  return 0;
}
