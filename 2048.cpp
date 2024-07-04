#include <bits/stdc++.h>
using namespace std;

class Game2048 {
private:
    vector<vector<int>> board;
    int size;
    bool gameOver;

public:
    Game2048(int s) : size(s), gameOver(false) {
        board.resize(size, vector<int>(size, 0));
        srand(time(0));
        addNewTile();
        addNewTile();
    }

    void displayBoard() {
        for (const auto& row : board) {
            for (int tile : row) {
                if (tile == 0) {
                    cout << setw(4) << ".";
                } else {
                    cout << setw(4) << tile;
                }
            }
            cout << endl;
        }
        cout << endl;
    }

    void addNewTile() {
        vector<pair<int, int>> emptyTiles;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (board[i][j] == 0) {
                    emptyTiles.push_back({i, j});
                }
            }
        }
        if (!emptyTiles.empty()) {
            int randIndex = rand() % emptyTiles.size();
            board[emptyTiles[randIndex].first][emptyTiles[randIndex].second] = (rand() % 2 + 1) * 2;
        }
    }

    bool canMove() {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (board[i][j] == 0) return true;
                if (i < size - 1 && board[i][j] == board[i + 1][j]) return true;
                if (j < size - 1 && board[i][j] == board[i][j + 1]) return true;
            }
        }
        return false;
    }

    void moveLeft() {
        for (int i = 0; i < size; ++i) {
            vector<int> newRow(size, 0);
            int k = 0;
            for (int j = 0; j < size; ++j) {
                if (board[i][j] != 0) {
                    if (k > 0 && newRow[k - 1] == board[i][j]) {
                        newRow[k - 1] *= 2;
                        newRow[k] = 0;
                    } else {
                        newRow[k] = board[i][j];
                        ++k;
                    }
                }
            }
            board[i] = newRow;
        }
    }

    void moveRight() {
        for (int i = 0; i < size; ++i) {
            vector<int> newRow(size, 0);
            int k = size - 1;
            for (int j = size - 1; j >= 0; --j) {
                if (board[i][j] != 0) {
                    if (k < size - 1 && newRow[k + 1] == board[i][j]) {
                        newRow[k + 1] *= 2;
                        newRow[k] = 0;
                    } else {
                        newRow[k] = board[i][j];
                        --k;
                    }
                }
            }
            board[i] = newRow;
        }
    }

    void moveUp() {
        for (int j = 0; j < size; ++j) {
            vector<int> newCol(size, 0);
            int k = 0;
            for (int i = 0; i < size; ++i) {
                if (board[i][j] != 0) {
                    if (k > 0 && newCol[k - 1] == board[i][j]) {
                        newCol[k - 1] *= 2;
                        newCol[k] = 0;
                    } else {
                        newCol[k] = board[i][j];
                        ++k;
                    }
                }
            }
            for (int i = 0; i < size; ++i) {
                board[i][j] = newCol[i];
            }
        }
    }

    void moveDown() {
        for (int j = 0; j < size; ++j) {
            vector<int> newCol(size, 0);
            int k = size - 1;
            for (int i = size - 1; i >= 0; --i) {
                if (board[i][j] != 0) {
                    if (k < size - 1 && newCol[k + 1] == board[i][j]) {
                        newCol[k + 1] *= 2;
                        newCol[k] = 0;
                    } else {
                        newCol[k] = board[i][j];
                        --k;
                    }
                }
            }
            for (int i = 0; i < size; ++i) {
                board[i][j] = newCol[i];
            }
        }
    }

    void move(char direction) {
        switch (direction) {
            case 'a':
                moveLeft();
                break;
            case 'd':
                moveRight();
                break;
            case 'w':
                moveUp();
                break;
            case 's':
                moveDown();
                break;
            default:
                cout << "Invalid move! Use w/a/s/d keys." << endl;
                return;
        }
        addNewTile();
        if (!canMove()) {
            gameOver = true;
            cout << "Game Over!" << endl;
        }
    }

    bool isGameOver() {
        return gameOver;
    }
};

int main() {
    int boardSize = 4;
    Game2048 game(boardSize);

    char move;
    while (!game.isGameOver()) {
        game.displayBoard();
        cout << "Enter your move (w/a/s/d): ";
        cin >> move;
        game.move(move);
    }

    return 0;
}
