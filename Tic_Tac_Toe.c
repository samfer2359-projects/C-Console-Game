#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// 3x3 Tic Tac Toe board
char board[3][3] = { {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '} };

// Function prototypes
void displayBoard();
bool checkPosition(int row, int col);
int insertPlayer(int currentPlayer, char symbol);
int insertComputer(int currentPlayer, char symbol);
bool checkWinner();
bool isBoardFull();
void twoPlayerGame();
void singlePlayerGame();

int main() {
    int choice;
    do {
        printf("\n      WELCOME TO TIC TAC TOE      \n");
        printf("1. Play with Computer\n");
        printf("2. Play with Another Player\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                singlePlayerGame();
                break;
            case 2:
                twoPlayerGame();
                break;
            case 3:
                printf("\nExiting...\n");
                break;
            default:
                printf("\nInvalid input! Try again.\n");
        }

        // Reset the board for a new game
        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
                board[i][j] = ' ';

    } while(choice != 3);

    return 0;
}

// Display the current board
void displayBoard() {
    printf("   1   2   3\n");
    for(int i = 0; i < 3; i++) {
        printf("  +---+---+---+\n");
        printf("%d |", i + 1);
        for(int j = 0; j < 3; j++)
            printf(" %c |", board[i][j]);
        printf("\n");
    }
    printf("  +---+---+---+\n");
}

// Check if a position is valid and empty
bool checkPosition(int row, int col) {
    return !(row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ');
}

// Insert a move for a human player
int insertPlayer(int currentPlayer, char symbol) {
    int row, col;
    while(true) {
        printf("\nPlayer %d, enter your move (row and column): ", currentPlayer);
        scanf("%d %d", &row, &col);
        row--; col--;  // Adjust for 0-based indexing
        if(checkPosition(row, col)) break;
        printf("Invalid position! Try again.\n");
    }
    board[row][col] = symbol;
    displayBoard();
    return (currentPlayer == 1) ? 2 : 1;  // Switch player
}

// Insert a move for the computer
int insertComputer(int currentPlayer, char symbol) {
    int row, col;
    srand(time(NULL));
    do {
        row = rand() % 3;
        col = rand() % 3;
    } while(!checkPosition(row, col));

    printf("\nComputer chooses: Row %d, Column %d\n", row + 1, col + 1);
    board[row][col] = symbol;
    displayBoard();
    return (currentPlayer == 1) ? 2 : 1;  // Switch player
}

// Check if any player has won
bool checkWinner() {
    // Rows and columns
    for(int i = 0; i < 3; i++) {
        if(board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return true;
        if(board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return true;
    }
    // Diagonals
    if(board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return true;
    if(board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return true;

    return false;
}

// Check if the board is full
bool isBoardFull() {
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(board[i][j] == ' ')
                return false;
    return true;
}

// Two-player game mode
void twoPlayerGame() {
    int currentPlayer = 1;
    char symbol;
    char player1[20] = "Player 1";
    char player2[20] = "Player 2";

    printf("\nEnter symbol for Player 1 (X or O): ");
    scanf(" %c", &symbol);
    char symbol1 = (symbol == 'X' || symbol == 'x') ? 'X' : 'O';
    char symbol2 = (symbol1 == 'X') ? 'O' : 'X';

    displayBoard();

    while(!checkWinner() && !isBoardFull()) {
        if(currentPlayer == 1)
            currentPlayer = insertPlayer(currentPlayer, symbol1);
        else
            currentPlayer = insertPlayer(currentPlayer, symbol2);
    }

    if(checkWinner()) {
        printf("\nWinner is %s!\n", (currentPlayer == 1) ? player2 : player1);
    } else {
        printf("\nIt's a tie!\n");
    }
}

// Single-player (vs computer) mode
void singlePlayerGame() {
    int currentPlayer = 1;
    char playerSymbol, computerSymbol;
    char playerName[20] = "Player";

    printf("\nChoose your symbol (X or O): ");
    scanf(" %c", &playerSymbol);
    if(playerSymbol == 'X' || playerSymbol == 'x') {
        playerSymbol = 'X';
        computerSymbol = 'O';
    } else {
        playerSymbol = 'O';
        computerSymbol = 'X';
    }

    displayBoard();

    while(!checkWinner() && !isBoardFull()) {
        if(currentPlayer == 1)
            currentPlayer = insertPlayer(currentPlayer, playerSymbol);
        else
            currentPlayer = insertComputer(currentPlayer, computerSymbol);
    }

    if(checkWinner()) {
        printf("\nWinner is %s!\n", (currentPlayer == 1) ? "Computer" : playerName);
    } else {
        printf("\nIt's a tie!\n");
    }
}
