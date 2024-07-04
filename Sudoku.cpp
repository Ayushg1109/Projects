#include <iostream>
#include <vector>
using namespace std;

const int N = 9;  // Size of Sudoku grid

class Sudoku {
private:
    vector<vector<int>> board;

public:
    Sudoku(vector<vector<int>>& initial) {
        board = initial;
    }

    // Function to print the Sudoku board
    void printBoard() {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                cout << board[i][j] << " ";
                if ((j + 1) % 3 == 0 && j != N - 1)
                    cout << "| ";
            }
            cout << endl;
            if ((i + 1) % 3 == 0 && i != N - 1)
                cout << "---------------------" << endl;
        }
    }

    // Function to check if a number can be placed in a cell
    bool canPlaceNumber(int row, int col, int num) {
        // Check row and column
        for (int i = 0; i < N; ++i) {
            if (board[row][i] == num || board[i][col] == num)
                return false;
        }
        // Check 3x3 sub-grid
        int startRow = row - row % 3;
        int startCol = col - col % 3;
        for (int i = startRow; i < startRow + 3; ++i) {
            for (int j = startCol; j < startCol + 3; ++j) {
                if (board[i][j] == num)
                    return false;
            }
        }
        return true;
    }

    // Function to solve Sudoku using backtracking
    bool solveSudoku() {
        int row, col;
        // Find an empty cell
        bool foundEmpty = false;
        for (row = 0; row < N; ++row) {
            for (col = 0; col < N; ++col) {
                if (board[row][col] == 0) {
                    foundEmpty = true;
                    break;
                }
            }
            if (foundEmpty)
                break;
        }
        // If no empty cell is found, Sudoku is solved
        if (!foundEmpty)
            return true;
        // Try placing numbers 1-9 in the empty cell
        for (int num = 1; num <= 9; ++num) {
            if (canPlaceNumber(row, col, num)) {
                board[row][col] = num;
                // Recursively try to solve Sudoku
                if (solveSudoku())
                    return true;
                // Backtrack
                board[row][col] = 0;
            }
        }
        return false;
    }
};

int main() {
    vector<vector<int>> initialBoard = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    Sudoku game(initialBoard);

    cout << "Sudoku Board:" << endl;
    game.printBoard();

    if (game.solveSudoku()) {
        cout << "\nSudoku Solved:" << endl;
        game.printBoard();
    } else {
        cout << "\nNo solution exists." << endl;
    }

    return 0;
}
