#include <stdio.h>
#include <stdbool.h>
#include <math.h> 

#define MAX_N 25

int N;

bool isSafe(int grid[MAX_N][MAX_N], int row, int col, int num) {
    for (int x = 0; x < N; x++) {
        if (grid[row][x] == num || grid[x][col] == num) {
            return false;
        }
    }
    
    int boxSize = (int)sqrt(N);
    if (boxSize * boxSize != N) {
        printf("Invalid board size. N must be a perfect square.\n");
        return false;
    }

    int startRow = row - row % boxSize, startCol = col - col % boxSize;
    for (int i = 0; i < boxSize; i++) {
        for (int j = 0; j < boxSize; j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }
    
    return true;
}


bool solveSudoku(int grid[MAX_N][MAX_N]) {
    int row, col;
    bool emptyCell = false;
    
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                emptyCell = true;
                break;
            }
        }
        if (emptyCell) break;
    }
    
    if (!emptyCell) return true;
    
    for (int num = 1; num <= N; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;
            if (solveSudoku(grid)) return true;
            grid[row][col] = 0;
        }
    }
    
    return false;
}


void printGrid(int grid[MAX_N][MAX_N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", grid[i][j]);
        }
        printf("\n");
    }
}


int main() {
    printf("Enter the size of the board (must be a perfect square, e.g., 4, 9, 16): ");
    scanf("%d", &N);
    
    if ((int)sqrt(N) * (int)sqrt(N) != N) {
        printf("Invalid board size. N must be a perfect square.\n");
        return 1;
    }
    
    int grid[MAX_N][MAX_N];
    printf("Enter the Sudoku board (use 0 for empty cells):\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &grid[i][j]);
        }
    }
    
    if (solveSudoku(grid)) {
        printGrid(grid);
    } else {
        printf("No solution exists\n");
    }
    
    return 0;
}

