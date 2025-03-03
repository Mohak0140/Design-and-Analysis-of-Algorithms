#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_N 15
#define MAX_SOLUTIONS 5

int unique_solutions[MAX_N][MAX_N]; 
int unique_solution_count = 0;
int total_solutions = 0;
int N;

bool is_safe(int board[], int row, int col) {
    for (int i = 0; i < row; i++) {
        if (board[i] == col || abs(board[i] - col) == abs(i - row))
            return false;
    }
    return true;
}

void rotate_board(int board[], int rotated[]) {
    int temp[MAX_N];
    for (int i = 0; i < N; i++) {
        temp[board[i]] = N - 1 - i;
    }
    memcpy(rotated, temp, N * sizeof(int));
}

void reflect_board(int board[], int reflected[]) {
    for (int i = 0; i < N; i++) {
        reflected[i] = N - 1 - board[i];
    }
}

bool is_duplicate(int board[]) {
    int temp[MAX_N];
    memcpy(temp, board, N * sizeof(int));
    for (int i = 0; i < 4; i++) {
        int rotated[MAX_N];
        rotate_board(temp, rotated);
        memcpy(temp, rotated, N * sizeof(int));
        for (int j = 0; j < unique_solution_count; j++) {
            if (memcmp(rotated, unique_solutions[j], N * sizeof(int)) == 0)
                return true;
        }
        int reflected[MAX_N];
        reflect_board(rotated, reflected);
        for (int j = 0; j < unique_solution_count; j++) {
            if (memcmp(reflected, unique_solutions[j], N * sizeof(int)) == 0)
                return true;
        }
    }
    return false;
}

void save_solution(int board[]) {
    total_solutions++;
    if (!is_duplicate(board) && unique_solution_count < MAX_N) {
        memcpy(unique_solutions[unique_solution_count], board, N * sizeof(int));
        unique_solution_count++;
    }
}

void solve_n_queens(int board[], int row) {
    if (row == N) {
        save_solution(board);
        return;
    }
    for (int col = 0; col < N; col++) {
        if (is_safe(board, row, col)) {
            board[row] = col;
            solve_n_queens(board, row + 1);
        }
    }
}

void print_solutions() {
    printf("Total Solutions: %d\n", total_solutions);
    printf("Total Unique Solutions: %d\n", unique_solution_count);
    int to_print = unique_solution_count < MAX_SOLUTIONS ? unique_solution_count : MAX_SOLUTIONS;
    if(unique_solution_count<5){
    	for (int i = 0; i < to_print; i++) {
        printf("Solution %d:\n", i + 1);
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                printf("%c ", unique_solutions[i][j] == k ? 'Q' : '.');
            }
            printf("\n");
        }
        printf("\n");
    	}
	}
    
}

int main() {
    printf("Enter N (Max %d): ", MAX_N);
    scanf("%d", &N);
    if (N < 1 || N > MAX_N) {
        printf("Invalid N.\n");
        return 1;
    }
    int board[MAX_N] = {0};
    solve_n_queens(board, 0);
    print_solutions();
    return 0;
}

