#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int BUFFER = 1000;

int longestSub(char *s);
int *strtoints(char *s);
int *prefixSum(int sz, int *arr);
int sumRange(int sz, int *arr, int *pre, int left, int right);

int main()
{
    char input[BUFFER];
    scanf("%s", input);
    
    printf("%d", longestSub(input));
    return 0;
}

int longestSub(char *s)
{
    int len = strlen(s);
    if (len < 2) {
        return 0;
    }
    int *arr = strtoints(s);
    int *pre = prefixSum(len, arr);
    
    int max = 0;
    for (int mid = 1; mid < len; ++mid) {
        int left = mid - 1, 
            right = mid + 1;
        while (left >= 0 && right <= len) {
            if (sumRange(len, arr, pre, left, mid) == sumRange(len, arr, pre, mid, right) 
                && right-left > max)
            {
                max = right - left;
            }
            --left;
            ++right;
        }
    }
    return max;
}

int *strtoints(char *s)
{
    int len = strlen(s);
    int *result = malloc(len * sizeof(int));
    for (int i = 0; i < len; ++i) {
        result[i] = s[i] - '0';
    }
    return result;
}

int *prefixSum(int sz, int *arr)
{
    if (sz == 0 || arr == NULL) {
        return NULL;
    }
    int *result = malloc(sz * sizeof(int));
    result[0] = arr[0];
    for (int i = 1; i < sz; ++i) {
        result[i] = result[i-1] + arr[i];
    }
    return result;
}

// sum[left, right)
int sumRange(int sz, int *arr, int *pre, int left, int right)
{
    if (right < left || left < 0 || right < 0 || left > sz || right > sz) {
        return -1;
    }
    if (left == right) {
        return 0;
    }
    if (left == 0) {
        return pre[right-1];
    }
    return pre[right-1] - pre[left-1];
}