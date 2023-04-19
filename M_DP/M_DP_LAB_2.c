#include <stdio.h>
#include <stdlib.h>

// memory
int *r;

int cr_bottom_up_dp_print(int *p, int n)
{
    // write your code here
    int **partitions = malloc(n * sizeof(int *));
    for (int i = 0; i < n; ++i) {
        partitions[i] = malloc(n * sizeof(int));
        for (int j = 0; j < n; ++j) {
            partitions[i][j] = -1;
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (i < 2) {
            r[i] = p[i];
            partitions[i-1][0] = 1;
        } else {
            int temp_max = p[i];
            partitions[i-1][0] = i;
            for (int j = 1; j < i; ++j) {
                if (p[j] + r[i - j] > temp_max) {
                    temp_max = p[j] + r[i - j];
                    partitions[i-1][0] = j;
                    for (int k = 0; k < n - 1 && partitions[i - j - 1][k] != -1; ++k) {
                        partitions[i - 1][k + 1] = partitions[i - j - 1][k];
                    }
                }
            }
            r[i] = temp_max;
        }
    }
    for (int i = 0; i < n && partitions[n - 1][i] != -1; ++i) {
        printf("%d ", partitions[n - 1][i]);
    }
    printf("\n");
    return r[n];
}

void main()
{
    int n; // length of  rod
    int function;
    int i;
    int *p; // price list

    int price_list[10] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24};  // declare one more value to cover the index 0;

    // n = sizeof(price_list) / sizeof(int) - 1;
    n = 8;
    p = price_list;

    // allocate the memory array
    r = malloc(sizeof(int) * (n + 1));

    // set all memory elements to -1
    for (i = 0; i <= n; i++)
        r[i] = -1;

    printf("The maximun value is: %d \n", cr_bottom_up_dp_print(p, n));
}