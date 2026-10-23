#include <iostream>
using namespace std;

const int N = 9;

void printGrid(int grid[N][N]) {
    cout << "\nSolved Sudoku:\n";

    for (int row = 0; row < N; row++) {
        if (row % 3 == 0 && row != 0)
            cout << "------+-------+------\n";

        for (int col = 0; col < N; col++) {
            if (col % 3 == 0 && col != 0)
                cout << "| ";

            cout << grid[row][col] << " ";
        }
        cout << '\n';
    }
}

bool isSafe(int grid[N][N], int row, int col, int num) {
    for (int i = 0; i < N; i++) {
        if (grid[row][i] == num ||
            grid[i][col] == num) {
            return false;
        }
    }

    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[startRow + i][startCol + j] == num)
                return false;
        }
    }

    return true;
}

bool solveSudoku(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                for (int num = 1; num <= 9; num++) {
                    if (isSafe(grid, row, col, num)) {
                        grid[row][col] = num;

                        if (solveSudoku(grid))
                            return true;

                        grid[row][col] = 0;
                    }
                }

                return false;
            }
        }
    }

    return true;
}

bool isValidGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            int num = grid[row][col];

            if (num < 0 || num > 9)
                return false;

            if (num != 0) {
                grid[row][col] = 0;
                bool safe = isSafe(grid, row, col, num);
                grid[row][col] = num;

                if (!safe)
                    return false;
            }
        }
    }

    return true;
}

int main() {
    int grid[N][N];

    cout << "Enter Sudoku grid (use 0 for empty cells):\n";

    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (!(cin >> grid[row][col])) {
                cout << "Invalid input.\n";
                return 0;
            }
        }
    }

    if (!isValidGrid(grid)) {
        cout << "Invalid Sudoku puzzle!\n";
        return 0;
    }

    if (solveSudoku(grid)) {
        printGrid(grid);
    } else {
        cout << "No solution exists for this Sudoku puzzle.\n";
    }

    return 0;
}