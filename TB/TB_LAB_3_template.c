#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int nQueens(int **board, int N, int col);
int isSafe(int **board, int N, int row, int col);
void printSolution(int **board, int N);

int main()
{
    int **board;
    int BSize;

    int i, j;

    printf("Enter the size of chessBoard:\n");
    scanf("%d", &BSize);

    board = (int **)malloc(BSize * sizeof(int *));
    for (i = 0; i < BSize; i++)
        board[i] = (int *)malloc(BSize * sizeof(int));

    for (i = 0; i < BSize; i++)
        for (j = 0; j < BSize; j++)
            board[i][j] = 0;

    clock_t begin, end;
    double time_spent;
    int result;

    begin = clock();
    result = nQueens(board, BSize, 0);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("%d (%lf second(s))", result, time_spent);

    return 0;
}

int nQueens(int **board, int BSize, int col)
{
    // Write your code here
    // Safe Place checking is provide below, you are free to use it.
    if (col >= BSize) {
        // printSolution(board, BSize);
        return 1;
    }

    int result = 0;
    for (int r = 0; r < BSize; ++r) {
        if (isSafe(board, BSize, r, col)) {
            board[r][col] = 1;
            result += nQueens(board, BSize, col+1);
            board[r][col] = 0;
        }
    }
    return result;
}

// Safe checking
int isSafe(int **board, int BSize, int row, int col)
{
    int i, j;

    // Horicatal check
    for (i = 0; i < col; i++)
        if (board[row][i])
            return 0;

    // Upper left diagonal check
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return 0;

    // Lower left diagonal check
    for (i = row, j = col; j >= 0 && i < BSize; i++, j--)
        if (board[i][j])
            return 0;

    return 1;
}

void printSolution(int **board, int BSize)
{
    int i, j;
    for (i = 0; i < BSize; i++)
    {
        for (j = 0; j < BSize; j++)
        {
            if (board[i][j] == 1)
                printf(" Q ");
            else
                printf(" + ");
        }
        printf("\n");
    }
    printf("\n");
}
