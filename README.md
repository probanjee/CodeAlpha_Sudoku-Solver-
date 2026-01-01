# CodeAlpha_Sudoku-Solver-
Advanced Sudoku Solver implemented in C++ using optimized backtracking with bitmasking for fast constraint checking. Features grid validation, clean object-oriented design, and efficient solving of standard 9×9 Sudoku puzzles.
# Advanced Sudoku Solver in C++

An efficient and well-structured **Sudoku Solver** written in **C++**, using **backtracking combined with bitmask optimization** for fast constraint checking.  
Designed with clean **object-oriented principles**, this solver validates the input grid and efficiently solves standard **9×9 Sudoku puzzles**.

---

##  Features

-  Solves standard **9×9 Sudoku puzzles**
-  **Optimized backtracking** using bitsets (O(1) validity checks)
-  Separate tracking of **rows, columns, and 3×3 subgrids**
-  **Initial grid validation** to detect invalid puzzles early
-  Clean **OOP-based design** using a dedicated `SudokuSolver` class
-  Nicely formatted grid output with subgrid separators
-  Easily extensible and reusable codebase

---

##  Technologies Used

- **Language:** C++
- **STL Containers:** `vector`
- **Optimization:** `bitset` for fast constraint checks
- **Algorithm:** Recursive Backtracking

---

##  Algorithm Overview

1. **Bitmask Initialization**
   - Uses three bitsets per row, column, and subgrid to track used numbers.

2. **Constraint Checking**
   - Validity of a number placement is checked in **constant time** using bitsets.

3. **Backtracking**
   - Recursively fills empty cells.
   - If a conflict occurs, it backtracks and tries the next possible number.

4. **Validation**
   - Ensures the initial puzzle follows Sudoku rules before solving.

---

##  Input Format

- Enter a **9×9 grid**
- Use **0** to represent empty cells
- Input is taken row-wise

**Example:**
5 3 0 0 7 0 0 0 0
6 0 0 1 9 5 0 0 0
0 9 8 0 0 0 0 6 0
8 0 0 0 6 0 0 0 3
4 0 0 8 0 3 0 0 1
7 0 0 0 2 0 0 0 6
0 6 0 0 0 0 2 8 0
0 0 0 4 1 9 0 0 5
0 0 0 0 8 0 0 7 9

---

## Output

- Displays:
  - Original Sudoku Grid
  - Solved Sudoku Grid (if solvable)
- Prints an error message if the grid is invalid or unsolvable

---

## How to Compile and Run

```bash
g++ sudoku_solver.cpp -o sudoku_solver
./sudoku_solver
