#include "item.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

class TodoList {
public:
  TodoList();
  TodoList(const char*);
  ~TodoList();

  void read();
  void display();
  void create();
  void save();
  void add();
  void clear();
  void check();

  int get_count();

private:
  const char* filename;
  vector<Item> list;
};