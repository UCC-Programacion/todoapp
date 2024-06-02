# TodoApp v3

- Bien al no mezclar logica con presentacion (no hay `cin`/`cout` en `Task`,
  `TodoService`, `InMemoryDatabase`, `TextFileDatabase`)
- La presentacion (`cin`/`cout`) se maneja en la clase `TodoUI`, que usa los
  casos de uso de `TodoService` (solo logica de negocio)
- Uso de polimorfismo para escribir/leer en memoria o en un archivo de texto,
  `InMemoryDatabase`/`TextFileDatabase` heredan de `Database`
- Uso de excepcion
  - en `TodoService`, `std::logic_error` y (opcional) excepcion custom
    `TaskNotFoundError`
  - en `Task`, `std::invalid_argument` para validar el valor de los atributos
- Uso de templates STL `std::map` `std:vector` para administrar map/lista de
  `Task`
- (opcional) Uso de algoritmos STL
  `std::erase_if`/`std::transform`/`std::back_inserter`
- Re-uso de `TodoService::get_tasks` en
  `get_completed_tasks`/`get_not_completed_tasks`
- Bien en separar funciones de utileria en su propio `.h` (`utils.h`,
  `utils_string.h`, `utils_io.h`)
  - (opcional) use de namespace `utils` para evitar colision de nombres
  - (opcional) mover funciones de `utils_string.h` al namespace `utils::string`
- 2 ejecutables
  - `main.cpp` como programa principal para usar `TodoService` con un menu
  - (opcional) `main_playground.cpp` como ejecutable para validar y probar
    funcionalidad `assert`
