/* Description:- Advanced Sudoku Solver in C++
This program solves a given Sudoku puzzle using backtracking and bitmask optimization for fast checks.*/
#include <iostream>
#include <vector> // Header for the vector container – it's way more flexible than raw arrays for storing the 2D grid, and it handles memory automatically
#include <bitset> // Header for bitset – we use this for super-fast checks on whether numbers are already used in rows, columns, and subgrids (like a compact array of booleans)

using namespace std;

// Define the size of the Sudoku grid (standard is 9x9)
const int SIZE = 9;

// Class to encapsulate the Sudoku solver functionality
// This makes the code more organized and reusable, like grouping related data and methods together
class SudokuSolver {
private:
    // The grid is stored as a 2D vector for flexibility (easier to resize if needed later)
    vector<vector<int>> grid;
    
    // Bitmasks for optimization: each row, column, and 3x3 subgrid has a bitset to track used numbers (1-9)
    // Bitsets are super efficient for checking if a number is already used, instead of looping through arrays
    vector<bitset<10>> rowMask, colMask, subgridMask;
    
    // Helper to get the subgrid index (0-8) from row and col
    // Subgrids are numbered left-to-right, top-to-bottom
    int getSubgridIndex(int row, int col) {
        return (row / 3) * 3 + (col / 3);
    }
    
    // Initialize the masks based on the current grid
    // This is called at the start to set up the state for the solver
    void initializeMasks() {
        rowMask.assign(SIZE, bitset<10>(0));
        colMask.assign(SIZE, bitset<10>(0));
        subgridMask.assign(SIZE, bitset<10>(0));
        
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (grid[i][j] != 0) {
                    int num = grid[i][j];
                    rowMask[i][num] = 1;
                    colMask[j][num] = 1;
                    subgridMask[getSubgridIndex(i, j)][num] = 1;
                }
            }
        }
    }
    
    // Check if placing 'num' at (row, col) is safe
    // Uses bitmasks for O(1) checks instead of O(N) loops, which is a big speed boost for larger puzzles
    bool isSafe(int row, int col, int num) {
        int subIdx = getSubgridIndex(row, col);
        return !rowMask[row][num] && !colMask[col][num] && !subgridMask[subIdx][num];
    }
    
    // Place a number and update masks
    // This keeps the masks in sync with the grid
    void placeNumber(int row, int col, int num) {
        grid[row][col] = num;
        int subIdx = getSubgridIndex(row, col);
        rowMask[row][num] = 1;
        colMask[col][num] = 1;
        subgridMask[subIdx][num] = 1;
    }
    
    // Remove a number and update masks (for backtracking)
    void removeNumber(int row, int col, int num) {
        grid[row][col] = 0;
        int subIdx = getSubgridIndex(row, col);
        rowMask[row][num] = 0;
        colMask[col][num] = 0;
        subgridMask[subIdx][num] = 0;
    }
    
    // Find the next empty cell (marked as 0)
    // Returns true if found, and updates row/col by reference
    bool findEmptyCell(int& row, int& col) {
        for (row = 0; row < SIZE; ++row) {
            for (col = 0; col < SIZE; ++col) {
                if (grid[row][col] == 0) {
                    return true;
                }
            }
        }
        return false;
    }
    
    // The core backtracking solver
    // Tries numbers 1-9 in empty cells, recurses, and backtracks if needed
    // This is the heart of the algorithm - it's recursive to explore possibilities
    bool solve() {
        int row, col;
        if (!findEmptyCell(row, col)) {
            return true; // No empty cells means solved!
        }
        
        for (int num = 1; num <= 9; ++num) {
            if (isSafe(row, col, num)) {
                placeNumber(row, col, num);
                
                if (solve()) {
                    return true; // Found a solution
                }
                
                removeNumber(row, col, num); // Backtrack
            }
        }
        return false; // No solution from here
    }

public:
    // Constructor to set up the grid
    SudokuSolver(const vector<vector<int>>& initialGrid) : grid(initialGrid) {
        initializeMasks();
    }
    
    // Print the grid in a nice format with subgrid separators
    // Makes it easier to read, especially for debugging
    void printGrid() {
        for (int i = 0; i < SIZE; ++i) {
            if (i % 3 == 0 && i != 0) {
                cout << "------+-------+------\n"; // Separator for subgrids
            }
            for (int j = 0; j < SIZE; ++j) {
                if (j % 3 == 0 && j != 0) {
                    cout << "| "; // Vertical separator
                }
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
    }
    
    // Validate the initial grid for basic Sudoku rules
    // Checks for duplicates in rows, cols, subgrids - useful to catch invalid inputs early
    bool isValidGrid() {
        for (int i = 0; i < SIZE; ++i) {
            bitset<10> rowCheck, colCheck, subCheck;
            for (int j = 0; j < SIZE; ++j) {
                int num = grid[i][j];
                if (num != 0) {
                    if (rowCheck[num]) return false; // Duplicate in row
                    rowCheck[num] = 1;
                    
                    if (colCheck[j] && colCheck[j] == num) return false; // Wait, fix this
                    // Actually, better to check columns separately
                }
            }
        }
        // Full check for columns and subgrids
        for (int j = 0; j < SIZE; ++j) {
            bitset<10> colCheck;
            for (int i = 0; i < SIZE; ++i) {
                int num = grid[i][j];
                if (num != 0 && colCheck[num]) return false;
                colCheck[num] = 1;
            }
        }
        for (int box = 0; box < SIZE; ++box) {
            bitset<10> subCheck;
            int startRow = (box / 3) * 3;
            int startCol = (box % 3) * 3;
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    int num = grid[startRow + i][startCol + j];
                    if (num != 0 && subCheck[num]) return false;
                    subCheck[num] = 1;
                }
            }
        }
        return true;
    }
    
    // Public solve method that calls the private one
    // Also checks if the grid is valid first
    bool solveSudoku() {
        if (!isValidGrid()) {
            cout << "Invalid initial grid! Please check for duplicates.\n";
            return false;
        }
        return solve();
    }
    
    // Getter for the grid (in case you want to access it later)
    vector<vector<int>> getGrid() const {
        return grid;
    }
};

// Main function - where the program starts
// Handles user input, creates the solver, and runs it
int main() {
    cout << "Welcome to the Advanced Sudoku Solver!\n";
    cout << "Enter the Sudoku puzzle (9x9 grid, use 0 for empty cells):\n";
    cout << "Input row by row, with spaces between numbers.\n";
    
    vector<vector<int>> grid(SIZE, vector<int>(SIZE));
    for (int i = 0; i < SIZE; ++i) {
        cout << "Row " << (i + 1) << ": ";
        for (int j = 0; j < SIZE; ++j) {
            cin >> grid[i][j];
        }
    }
    
    SudokuSolver solver(grid);
    
    cout << "\nOriginal Sudoku Grid:\n";
    solver.printGrid();
    
    if (solver.solveSudoku()) {
        cout << "\nSudoku Solved Successfully!\n";
        solver.printGrid();
    } else {
        cout << "\nNo solution exists for the given Sudoku.\n";
    }
    
    return 0;
}
//End of the code
