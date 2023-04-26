#include <stdio.h>
#include <stdbool.h>

// Function prototypes
void drawBoard(char board[3][3]);
int checkWin(char board[3][3], bool markWinningLine);
void playerMove(char board[3][3]);
void aiMove(char board[3][3]);
int minimax(char board[3][3], int depth, bool isMaximizingPlayer);

int main() {
    char board[3][3] = { {' ', ' ', ' '},
                         {' ', ' ', ' '},
                         {' ', ' ', ' '} };
    int turn = 0;

    printf("Welcome to Tic Tac Toe!\n");
    drawBoard(board);

    while (checkWin(board, false) == 0 && turn < 9) {
        playerMove(board);
        turn++;
        if (checkWin(board, false) != 0 || turn == 9) break; // If player wins or board is full, break the loop
        aiMove(board);
        turn++;
    }

    int result = checkWin(board, true);
    drawBoard(board);
    if (result == 1)
        printf("Congratulations, you won!\n");
    else if (result == -1)
        printf("AI won, better luck next time!\n");
    else
        printf("It's a draw!\n");

    return 0;
}

// Function to draw the board
void drawBoard(char board[3][3]) {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        printf(" %c | %c | %c \n", board[i][0], board[i][1], board[i][2]);
        if (i < 2) printf("---|---|---\n");
    }
    printf("\n");
}

// Function to check for a win and mark the winning row/column/diagonal
int checkWin(char board[3][3], bool markWinningLine) {
    // Check rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            if (board[i][0] == 'X') {
                if (markWinningLine) {
                    board[i][0] = board[i][1] = board[i][2] = '*';
                }
                return 1;
            }
            if (board[i][0] == 'O') {
                if (markWinningLine) {
                    board[i][0] = board[i][1] = board[i][2] = '*';
                }
                return -1;
            }
        }
    }

    // Check columns
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            if (board[0][i] == 'X') {
                if (markWinningLine) {
                    board[0][i] = board[1][i] = board[2][i] = '*';
                }
                return 1;
            }
            if (board[0][i] == 'O') {
                if (                markWinningLine) {
                    board[0][i] = board[1][i] = board[2][i] = '*';
                }
                return -1;
            }
        }
    }

    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[1][1] == 'X') {
            if (markWinningLine) {
                board[0][0] = board[1][1] = board[2][2] = '*';
            }
            return 1;
        }
        if (board[1][1] == 'O') {
            if (markWinningLine) {
                board[0][0] = board[1][1] = board[2][2] = '*';
            }
            return -1;
        }
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[1][1] == 'X') {
            if (markWinningLine) {
                board[0][2] = board[1][1] = board[2][0] = '*';
            }
            return 1;
        }
        if (board[1][1] == 'O') {
            if (markWinningLine) {
                board[0][2] = board[1][1] = board[2][0] = '*';
            }
            return -1;
        }
    }

    return 0;
}

// Function to handle player's move
void playerMove(char board[3][3]) {
    int x, y;
    while (1) {
        printf("Enter your move (row and column, separated by space): ");
        scanf("%d %d", &x, &y);

        // Check if the input is valid and the chosen cell is empty
        if (x >= 1 && x <= 3 && y >= 1 && y <= 3 && board[x - 1][y - 1] == ' ') {
            board[x - 1][y - 1] = 'X';
            break;
        } else {
            printf("Invalid move. Try again.\n");
        }
    }
    drawBoard(board);
}

// Function to handle AI's move
void aiMove(char board[3][3]) {
    int bestScore = -1000;
    int bestMove[2] = {-1, -1};

    // Iterate through all possible moves and select the best one
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                int moveScore = minimax(board, 0, false);
                board[i][j] = ' ';
                if (moveScore > bestScore) {
                    bestScore = moveScore;
                    bestMove[0] = i;
                    bestMove[1] = j;
                }
            }
        }
    }

    board[bestMove[0]][bestMove[1]] = 'O';
    printf("AI made a move:\n");
    drawBoard(board);
}

// Minimax function to find the optimal move
int minimax(char board[3][3], int depth, bool isMaximizingPlayer) {
    int result = checkWin(board, false);

    // Base case: return the score if the game is over or the maximum depth is reached
    if (result != 0)
        return result * (10 - depth); // Favor faster wins
    if (depth == 9)
        return 0;

    if (isMaximizingPlayer) {
        int bestScore = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O';
                    int score = minimax(board, depth + 1, false);
                    board[i][j] = ' ';
                    bestScore = (score > bestScore) ? score : bestScore;
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X';
                    int score = minimax(board, depth + 1, true);
                    board[i][j] = ' ';
                    bestScore = (score < bestScore) ? score : bestScore;
                }
            }
        }
        return bestScore;
    }
}


