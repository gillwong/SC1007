#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cyclicalMin1(size_t sz, int *arr);
int cyclicalMin2(size_t sz, int *arr);

int main()
{
    char filename[100];
    FILE *input;

    printf("Enter input file name (.txt): ");
    scanf("%s", filename);

    if ((input = fopen(filename, "r")) == NULL) {
        printf("Error opening file!");
        return 1;
    }

    size_t size;
    fscanf(input, "%llu", &size);

    int *cyclically_sorted = malloc(size * sizeof(int));
    for (size_t i = 0; i < size; ++i) {
        fscanf(input, "%d", cyclically_sorted + i);
    }
    
    clock_t begin, end;
    double time_spent;
    int result;

    begin = clock();
    result = cyclicalMin1(size, cyclically_sorted);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("cyclicalMin1: %d (%lf second(s))\n", result, time_spent);

    begin = clock();
    result = cyclicalMin2(size, cyclically_sorted);
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("cyclicalMin2: %d (%lf second(s))\n", result, time_spent);

    fclose(input);
    return 0;
}

int cyclicalMin1(size_t sz, int *arr)
{
    int min = arr[0];
    for (size_t i = 1; i < sz; ++i) {
        if (arr[i-1] > arr[i]) {
            min = arr[i];
            break;
        }
    }
    return min;
}

int cyclicalMin2(size_t sz, int *arr)
{
    if (arr[0] < arr[sz-1])
        return arr[0];
    
    size_t l = 1, r = sz;
    while (arr[l-1] < arr[l]) {
        size_t d = r-l;
        if (arr[l] > arr[r-1]) {
            l += d/2;
        } else {
            r = l;
            l -= d/2;
        }
    }
    return arr[l];
}