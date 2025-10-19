#include <iostream>
#include <vector>
#include <limits>


#include <cctype>

using namespace std;

class Board {
private:
    vector<vector<char>> grid;
    int size;

public:
    Board(int n = 3) : size(n) {
        grid.resize(size, vector<char>(size, ' '));
    }

    void display() const {
        cout << "\n   ";
        for (int i = 0; i < size; i++) {
            cout << " " << i + 1 << "  ";
        }
        cout << "\n   ";
        for (int i = 0; i < size; i++) {
            cout << "---+";
        }
        cout << "\n";

        for (int i = 0; i < size; i++) {
            cout << " " << i + 1 << " ";
            for (int j = 0; j < size; j++) {
                cout << " " << grid[i][j] << " ";
                if (j < size - 1) cout << "|";
            }
            cout << "\n   ";
            for (int j = 0; j < size; j++) {
                cout << "---+";
            }
            cout << "\n";
        }
    }

    bool makeMove(int row, int col, char player) {
        if (row < 0 || row >= size || col < 0 || col >= size || grid[row][col] != ' ') {
            return false;
        }
        grid[row][col] = player;
        return true;
    }

    bool isFull() const {
        for (const auto& row : grid) {
            for (char cell : row) {
                if (cell == ' ') {
                    return false;
                }
            }
        }
        return true;
    }

    bool checkWin(char player) const {
        // Check rows and columns
        for (int i = 0; i < size; i++) {
            bool rowWin = true;
            bool colWin = true;
            for (int j = 0; j < size; j++) {
                if (grid[i][j] != player) rowWin = false;
                if (grid[j][i] != player) colWin = false;
            }
            if (rowWin || colWin) return true;
        }

        // Check diagonals
        bool diag1Win = true;
        bool diag2Win = true;
        for (int i = 0; i < size; i++) {
            if (grid[i][i] != player) diag1Win = false;
            if (grid[i][size - 1 - i] != player) diag2Win = false;
        }
        
        return diag1Win || diag2Win;
    }

    void reset() {
        for (auto& row : grid) {
            for (char& cell : row) {
                cell = ' ';
            }
        }
    }
};

class TicTacToe {
private:
    Board board;
    char currentPlayer;
    int playerXScore;
    int playerOScore;
    int draws;

public:
    TicTacToe() : currentPlayer('X'), playerXScore(0), playerOScore(0), draws(0) {}

    void play() {
        cout << "===============================\n";
        cout << "      TIC-TAC-TOE GAME\n";
        cout << "===============================\n\n";

        bool playAgain = true;
        while (playAgain) {
            board.reset();
            currentPlayer = 'X';
            bool gameEnded = false;

            while (!gameEnded) {
                displayScores();
                board.display();
                cout << "\nPlayer " << currentPlayer << "'s turn\n";

                int row, col;
                if (getPlayerMove(row, col)) {
                    if (board.checkWin(currentPlayer)) {
                        board.display();
                        cout << "\nPlayer " << currentPlayer << " wins!\n";
                        updateScore(currentPlayer);
                        gameEnded = true;
                    } else if (board.isFull()) {
                        board.display();
                        cout << "\nThe game is a draw!\n";
                        draws++;
                        gameEnded = true;
                    } else {
                        switchPlayer();
                    }
                } else {
                    cout << "Invalid move! Please try again.\n";
                }
            }

            playAgain = askToPlayAgain();
        }

        displayFinalScores();
    }

private:
    void displayScores() const {
        cout << "===============================\n";
        cout << "         SCORE BOARD\n";
        cout << "===============================\n";
        cout << "   Player X: " << playerXScore << " wins\n";
        cout << "   Player O: " << playerOScore << " wins\n";
        cout << "   Draws: " << draws << "\n";
        cout << "===============================\n\n";
    }

    void displayFinalScores() const {
        cout << "\n===============================\n";
        cout << "        FINAL SCORES\n";
        cout << "===============================\n";
        cout << "   Player X: " << playerXScore << " wins\n";
        cout << "   Player O: " << playerOScore << " wins\n";
        cout << "   Draws: " << draws << "\n";
        cout << "===============================\n";
        cout << "Thanks for playing!\n";
    }

    bool getPlayerMove(int& row, int& col) {
        while (true) {
            cout << "Enter row and column (1-3): ";
            cin >> row >> col;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input! Please enter numbers only.\n";
            } else {
                // Convert to 0-based indexing
                row--;
                col--;
                return board.makeMove(row, col, currentPlayer);
            }
        }
    }

    void switchPlayer() {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    void updateScore(char player) {
        if (player == 'X') {
            playerXScore++;
        } else {
            playerOScore++;
        }
    }

    bool askToPlayAgain() {
        char response;
        cout << "\nWould you like to play again? (y/n): ";
        cin >> response;
        response = tolower(response);
        
        // Clear input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        return response == 'y';
    }
};

int main() {
    TicTacToe game;
    game.play();
    return 0;
}