#include <stdio.h>
#include <stdbool.h>

#define N 4

// Function to print the chessboard
void printBoard(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%c ", board[i][j] ? 'Q' : '.');
        }
        printf("\n");
    }
}

// Function to check if a queen can be placed at board[row][col]
bool isSafe(int board[N][N], int row, int col) {
    int i, j;

    // Check the left side of the current row
    for (i = 0; i < col; i++) {
        if (board[row][i]) {
            return false;
        }
    }

    // Check upper diagonal on the left side
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j]) {
            return false;
        }
    }

    // Check lower diagonal on the left side
    for (i = row, j = col; i < N && j >= 0; i++, j--) {
        if (board[i][j]) {
            return false;
        }
    }

    return true;
}

// Solve N-Queens problem using backtracking
bool solveNQueens(int board[N][N], int col) {
    if (col >= N) {
        return true; // All queens are placed successfully
    }

    for (int i = 0; i < N; i++) {
        if (isSafe(board, i, col)) {
            board[i][col] = 1; // Place the queen

            if (solveNQueens(board, col + 1)) {
                return true; // If placing the queen leads to a solution, return true
            }

            board[i][col] = 0; // If placing the queen doesn't lead to a solution, backtrack
        }
    }

    return false; // If no position is found to place a queen in this column
}

int main() {
    int board[N][N] = {{0}}; // Initialize the chessboard
    printf("Tushar Bhatia\n");
    printf("A2305221202\n");
    if (solveNQueens(board, 0)) {
        printf("Solution found:\n");
        printBoard(board);
    } else {
        printf("No solution exists for N = %d\n", N);
    }

    return 0;
}
