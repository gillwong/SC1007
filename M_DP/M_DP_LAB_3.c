#include <stdio.h>
#include <stdlib.h>

int min(int sz, int *arr) {
    if (sz == 0 || arr == NULL) {
        return INT_MAX;
    }
    int min = arr[0];
    for (int i = 1; i < sz; ++i) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

int waysToScoreMemo(int *memo, int n, int sz, int *score, int min_score)
{
    if (n < min_score) {
        return 0;
    }
    if (memo[n - 1] != 0) {
        return memo[n - 1];
    }

    int result = 0;
    for (int i = 0; i < sz; ++i) {
        if (n - score[i] > 0) {
            result += waysToScoreMemo(memo, n - score[i], sz, score, min_score);
        } else if (n - score[i] == 0) {
            ++result;
        }
    }
    memo[n - 1] = result;
    return result;
}

int waysToScoreDP(int *memo, int n, int sz, int *score, int min_score)
{
    for (int i = 0; i < sz; ++i) {
        memo[score[i] - 1] = 1;
    }
    for (int i = min_score + 1; i <= n; ++i) {
        int result = 0;
        for (int j = 0; j < sz && i - score[j] >= 0; ++j) {
            if (i - score[j] == 0) {
                ++result;
            } else {
                result += memo[i - score[j] - 1];
            }
        }
        memo[i - 1] = result;
    }
    return memo[n - 1];
}

int waysToScore(int n, int *score)
{
    // write your code here
    int sz = 3;
    int min_score = min(sz, score);
    int *memo = malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        memo[i] = 0;
    }
    return waysToScoreDP(memo, n, sz, score, min_score);
    return waysToScoreMemo(memo, n, sz, score, min_score);
}

void main()
{
    int n;

    int score[3] = {3, 5, 10};

    printf("Enter the value of N: ");
    scanf("%d", &n);

    printf("The number of ways to reach to a score of %d is: %d \n", n, waysToScore(n, score));
}
