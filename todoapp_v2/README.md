# TodoApp v2

Calificacion: 4

A mejorar:

- cin/cout (i/o) en clase TodoList, deberia tener solo logica
- Clase Item
  - destructor innecesario
  - str_tolower no deberia ser un metodo de Item (podria ser una funcion de utileria)
- `using namespace std;` en los `.h`
- faltan _include guards_ o `#pragma once` en los `.h`
- bug: en el menu, al ingresar una letra (o cualquier otro caracter que no sea una opcion valida) sale del programa
