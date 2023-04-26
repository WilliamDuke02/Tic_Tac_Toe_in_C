#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function prototypes
void drawBoard(char board[3][3]);
int checkWin(char board[3][3]);
void playerMove(char board[3][3]);
void aiMove(char board[3][3]);

int main() {
    char board[3][3] = { {' ', ' ', ' '},
                         {' ', ' ', ' '},
                         {' ', ' ', ' '} };
    int turn = 0;

    srand(time(NULL)); // Initialize random seed for AI move

    printf("Welcome to Tic Tac Toe!\n");
    drawBoard(board);

    while (checkWin(board) == 0 && turn < 9) {
        playerMove(board);
        turn++;
        if (checkWin(board) != 0 || turn == 9) break; // If player wins or board is full, break the loop
        aiMove(board);
        turn++;
    }

    int result = checkWin(board);
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

// Function to check for a win
int checkWin(char board[3][3]) {
    // Check rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            if (board[i][0] == 'X') return 1;
            if (board[i][0] == 'O') return -1;
        }
    }

    // Check columns
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            if (board[0][i] == 'X') return 1;
            if (board[0][i] == 'O') return -1;
        }
    }

    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] || 
        board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[1][1] == 'X') return 1;
        if (board[1][1] == 'O') return -1;
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
    int x, y;
    while (1) {
        x = rand() % 3;
        y = rand() % 3;

        // Check if the chosen cell is empty
        if (board[x][y] == ' ') {
            board[x][y] = 'O';
            break;
        }
    }
    printf("AI made a move:\n");
    drawBoard(board);
}
