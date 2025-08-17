#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>

class Game2048 {
private:
    std::vector<std::vector<int>> board;
    int size;
    bool gameOver;
    bool gameWon;
    int score;

    void addNewTile() {
        std::vector<std::pair<int, int>> emptyTiles;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (board[i][j] == 0) {
                    emptyTiles.push_back({i, j});
                }
            }
        }
        if (!emptyTiles.empty()) {
            int randIndex = std::rand() % emptyTiles.size();
            board[emptyTiles[randIndex].first][emptyTiles[randIndex].second] = (std::rand() % 2 + 1) * 2;
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

    void checkWin() {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (board[i][j] == 2048) {
                    gameWon = true;
                    return;
                }
            }
        }
    }

    void moveLeft() {
        for (int i = 0; i < size; ++i) {
            std::vector<int> newRow;
            for (int j = 0; j < size; ++j) {
                if (board[i][j] != 0) {
                    if (!newRow.empty() && newRow.back() == board[i][j]) {
                        newRow.back() *= 2;
                        score += newRow.back();
                        newRow.push_back(0);
                    } else {
                        newRow.push_back(board[i][j]);
                    }
                }
            }
            while (newRow.size() < size) {
                newRow.push_back(0);
            }
            board[i] = newRow;
        }
    }

    void moveRight() {
        for (int i = 0; i < size; ++i) {
            std::vector<int> newRow;
            for (int j = size - 1; j >= 0; --j) {
                if (board[i][j] != 0) {
                    if (!newRow.empty() && newRow.back() == board[i][j]) {
                        newRow.back() *= 2;
                        score += newRow.back();
                        newRow.push_back(0);
                    } else {
                        newRow.push_back(board[i][j]);
                    }
                }
            }
            std::reverse(newRow.begin(), newRow.end());
            while (newRow.size() < size) {
                newRow.insert(newRow.begin(), 0);
            }
            board[i] = newRow;
        }
    }

    void moveUp() {
        for (int j = 0; j < size; ++j) {
            std::vector<int> newCol;
            for (int i = 0; i < size; ++i) {
                if (board[i][j] != 0) {
                    if (!newCol.empty() && newCol.back() == board[i][j]) {
                        newCol.back() *= 2;
                        score += newCol.back();
                        newCol.push_back(0);
                    } else {
                        newCol.push_back(board[i][j]);
                    }
                }
            }
            while (newCol.size() < size) {
                newCol.push_back(0);
            }
            for (int i = 0; i < size; ++i) {
                board[i][j] = newCol[i];
            }
        }
    }

    void moveDown() {
        for (int j = 0; j < size; ++j) {
            std::vector<int> newCol;
            for (int i = size - 1; i >= 0; --i) {
                if (board[i][j] != 0) {
                    if (!newCol.empty() && newCol.back() == board[i][j]) {
                        newCol.back() *= 2;
                        score += newCol.back();
                        newCol.push_back(0);
                    } else {
                        newCol.push_back(board[i][j]);
                    }
                }
            }
            std::reverse(newCol.begin(), newCol.end());
            while (newCol.size() < size) {
                newCol.insert(newCol.begin(), 0);
            }
            for (int i = 0; i < size; ++i) {
                board[i][j] = newCol[i];
            }
        }
    }

public:
    Game2048(int s) : size(s), gameOver(false), gameWon(false), score(0) {
        board.resize(size, std::vector<int>(size, 0));
        std::srand(std::time(0));
        addNewTile();
        addNewTile();
    }

    void displayBoard() {
        std::cout << "Score: " << score << std::endl;
        for (const auto& row : board) {
            for (int tile : row) {
                if (tile == 0) {
                    std::cout << std::setw(4) << ".";
                } else {
                    std::cout << std::setw(4) << tile;
                }
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    void move(char direction) {
        std::vector<std::vector<int>> prevBoard = board;
        
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
                std::cout << "Invalid move! Use w/a/s/d keys." << std::endl;
                return;
        }

        if (prevBoard != board) {
            addNewTile();
        }

        checkWin();
        if (gameWon) {
            std::cout << "Congratulations! You won the game!" << std::endl;
            gameOver = true;
        } else if (!canMove()) {
            gameOver = true;
            std::cout << "Game Over!" << std::endl;
        }
    }

    bool isGameOver() {
        return gameOver;
    }
};

int main() {
    int boardSize = 4;
    char playAgain;

    do {
        Game2048 game(boardSize);
        char moveInput;
        while (!game.isGameOver()) {
            game.displayBoard();
            std::cout << "Enter your move (w/a/s/d): ";
            std::cin >> moveInput;
            game.move(moveInput);
        }
        game.displayBoard();
        std::cout << "Do you want to play again? (y/n): ";
        std::cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y');

    std::cout << "Thanks for playing!" << std::endl;

    return 0;
}
