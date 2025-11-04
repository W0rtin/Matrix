# MatrixIO

Interactive console tool for creating and manipulating integer matrices in C++.

This project was written as part of my first year of studying Information Systems and Technologies (09.03.02) at Saint Petersburg Electrotechnical University "LETI".
The goal was to go beyond simple `cin`/`cout` and build something closer to a real console application:
- manual dynamic memory management (`new[]` / `delete[]`);
- custom low-level keyboard input without pressing Enter;
- safe integer input with ESC / Backspace handling;
- basic matrix operations (sum, difference, multiplication);
- simple text UI with a menu, running in a loop;
- separate sizes for two matrices and dimension checks before operations.

---

## Features

### 1. Dynamic matrix allocation

- Matrices are stored as `int**` (array of row pointers).
- Memory is allocated manually with `create_matrix(rows, cols)` and must be released with `free_matrix(matrix, rows)`.
- All elements are initialized to `0`.
- Both matrices have their **own** dimensions:

  - `m1` has size `rows1 x cols1`
  - `m2` has size `rows2 x cols2`

```cpp
int** m1 = create_matrix(rows1, cols1);
int** m2 = create_matrix(rows2, cols2);
/* ... use matrices ... */
free_matrix(m1, rows1);
free_matrix(m2, rows2);
```

This demonstrates understanding of raw pointers, manual ownership of heap memory, and working with 2D dynamic arrays.

---

### 2. Interactive input without `cin`

Instead of normal `std::cin >> value` (which requires pressing Enter), the program reads key presses directly from the terminal.

- `getch()` (in `matrix_io.hpp`) switches the terminal into non-canonical mode using `termios`, reads exactly one key, and restores the settings.
- `dig_esc(int& out)` (in `matrix_read.hpp`) builds on top of that and implements:
  - typing digits and optional leading `-`,
  - Backspace support,
  - finish number on Enter / Space,
  - cancel on `Esc`,
  - clamping to `int` range.

Then `fill(int** m, int rows, int cols)` uses this logic to fill every element of a matrix interactively:

```cpp
bool ok = fill(m1, rows1, cols1);
if (!ok) {
    // user pressed Esc to cancel input
}
```

So this is more like a tiny TUI than a basic lab that just calls `cin`.

---

### 3. Matrix operations

Three core operations are implemented:

- `sum_matrix(m1, rows1, cols1, m2, rows2, cols2)`  
  → returns a NEW matrix that is the element-wise sum `m1 + m2`, only if sizes match.

- `sub_matrix(m1, rows1, cols1, m2, rows2, cols2)`  
  → returns a NEW matrix that is the element-wise difference `m1 - m2`, only if sizes match.

- `multiplication_matrix(m1, rows1, cols1, m2, rows2, cols2)`  
  → returns a NEW matrix that is the matrix product `m1 * m2` with standard rule:
  `cols1 == rows2`, result size = `rows1 x cols2`.

Each function:

- checks input pointers and dimensions,
- allocates a fresh `int** result` using `create_matrix`,
- fills it,
- returns it to the caller.

The caller is responsible for freeing the result:

```cpp
int** s = sum_matrix(m1, rows1, cols1, m2, rows2, cols2);
if (s) {
    /* ... print s ... */
    free_matrix(s, rows1);
}
```

This shows explicit memory ownership conventions: “you allocate it, you free it” and safe dimension checks.

---

### 4. Text-based menu

The program (`main.cpp`) runs an interactive menu loop that does **not** require pressing Enter.
Everything is driven by immediate keypresses read with `getch()`.

Menu options (high level):

1. Set sizes of both matrices (independent `rows1/cols1` and `rows2/cols2`) and allocate `m1`, `m2`.
2. Fill matrix 1.
3. Fill matrix 2.
4. Print both matrices.
5. Matrix operations:
   - `m1 + m2` (only if sizes are equal)
   - `m1 - m2` (only if sizes are equal)
   - `m1 * m2` (only if `cols1 == rows2`)
Esc — exit.

After each action, the app pauses (“Press any key…”) so the result stays on screen before returning to the menu.

The code also:

- checks that matrices exist and their sizes are valid before using them,
- prevents dereferencing `nullptr`,
- prevents operations on incompatible dimensions,
- frees all allocated memory on exit.

---

### 5. “Fool-proof” protection

The program includes several “defence against mistakes” mechanisms:

- Sizes must be strictly positive and below a configurable maximum (e.g. 1000×1000).
- If matrices already exist and the user tries to change sizes, the program asks for confirmation before freeing old data.
- If the user presses `Esc` during numeric input, the current operation is cancelled cleanly.
- All matrix operations validate dimensions and return `nullptr` instead of crashing when dimensions are incompatible.

---

## Project structure

```text
MatrixIO/
  CMakeLists.txt
  README.md
  header/
    matrix_io.hpp        // terminal helpers: getch(), clear_t()
    matrix_read.hpp      // safe integer input: dig_esc(), fill()
    matrix_action.hpp    // matrix memory, math and size management
  matrix_main/
    main.cpp             // menu loop and user interaction
```

### `matrix_io.hpp`

Low-level terminal utilities:

- `clear_t()` clears the terminal using an ANSI escape sequence.
- `getch()` reads a single keypress without waiting for Enter and without echoing it, using `termios` (macOS/Linux).

### `matrix_read.hpp`

Interactive input:

- `dig_esc(int& out)` reads an integer with Backspace and ESC handling, with clamping to `int`.
- `fill(int** m, int rows, int cols)` fills a matrix element-by-element using `dig_esc`.

### `matrix_action.hpp`

Matrix logic + memory management:

- `create_matrix(rows, cols)` / `free_matrix(matrix, rows)` — raw dynamic 2D arrays (`int**`).
- `sum_matrix(m1, rows1, cols1, m2, rows2, cols2)` — element-wise sum with dimension checks.
- `sub_matrix(m1, rows1, cols1, m2, rows2, cols2)` — element-wise difference with dimension checks.
- `multiplication_matrix(m1, rows1, cols1, m2, rows2, cols2)` — matrix product with standard rule `cols1 == rows2`.
- `set_matrices_size(m1, rows1, cols1, m2, rows2, cols2)` — interactive size setup for both matrices, with confirmation and safe reallocation.

---

## Build & Run

Requirements:

- CMake >= 3.16
- C++20-capable compiler (tested with clang++ on macOS)
- POSIX terminal (macOS / Linux) because of `termios`

From the project root (`MatrixIO/`):

```bash
cmake -S . -B build
cmake --build build
./build/matrix_app
```

This will:

- configure the project into `build/`
- compile `matrix_main/main.cpp`
- link into the `matrix_app` executable
- run it

---

## Why this project is relevant for a C/C++ internship

This project is not just “read matrix and print matrix”.
It demonstrates:

- **Manual dynamic memory management**  
  Allocating and freeing 2D arrays via `new[]` / `delete[]`, understanding who owns the memory and when it must be freed.

- **Low-level terminal control**  
  Using `termios` to implement a `getch()`-style input loop on macOS/Linux (read a key immediately, no Enter, no echo).

- **Robust interactive input**  
  Integer reader with live editing, ESC cancel, Backspace handling, and overflow protection.

- **Correct matrix algebra with dimension checks**  
  Separate dimensions for two matrices, correct rules for sum/difference/multiplication and informative error handling when sizes are incompatible.

- **Code organization into modules**  
  Clean separation:
  - terminal I/O layer (`matrix_io.hpp`),
  - user input parsing (`matrix_read.hpp`),
  - matrix math / memory and size management (`matrix_action.hpp`),
  - UI loop (`main.cpp`).

- **Safe shutdown and cleanup**  
  The program frees all allocated matrices before exiting and carefully handles reallocation when changing sizes.

This level of responsibility (memory management, terminal control, structured input, correct dimension handling) is close to what junior/trainee C/C++ engineers are expected to handle in real tasks.
