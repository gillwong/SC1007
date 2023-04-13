#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void dualSearch(int A[], int size, int K, int dualIndex[]);
void dualSortedSearch(int A[], int size, int K, int dualIndex[]);
int partition (int A[], int low, int high);
void quickSort(int A[], int low, int high);

int main()
{
	char fileName[100];
	FILE *file;

	printf("Enter input file name (.txt): ");
	scanf("%s", fileName);
	
	if ((file = fopen(fileName, "r")) == NULL) {
		printf("Error opening file!");
		return 1;
	}
	
	int target, *arr,
		size, result[2] = { -1, -1 };

	fscanf(file, "%d", &target);
	printf("Target: %d\n", target);
	fscanf(file, "%d", &size);
	printf("Array size: %d\n\n", size);

	arr = malloc(sizeof(long) * size);
	for (size_t i = 0; i != size; ++i) {
		fscanf(file, "%d", &arr[i]);
	}

	clock_t begin, end;
	double time_spent;

	begin = clock();
	dualSearch(arr, size, target, result);
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	printf("Result of dualSearch(): [%d, %d]\n", result[0], result[1]);
	printf("dualSearch() took %lf second(s)\n\n", time_spent);

	result[0] = -1;
	result[1] = -1;

	begin = clock();
	quickSort(arr, 0, size-1);
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	printf("quickSort() took %lf second(s)\n\n", time_spent);

	begin = clock();
	dualSortedSearch(arr, size, target, result);
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	printf("Result of dualSortedSearch: [%d, %d]\n", result[0], result[1]);
	printf("dualSortedSearch() took %lf second(s)\n\n", size, time_spent);
	return 0;
}

void dualSearch(int A[], int size, int K, int dualIndex[])
{
	int i, j;
   	for (i = 0; i != size; ++i) {
		for (j = i; j != size; ++j) {
			if (A[i] + A[j] == K) {
				dualIndex[0] = i;
				dualIndex[1] = j;
				return;
			}
		}
	}
}

void dualSortedSearch(int A[], int size, int K, int dualIndex[])
{
	int left = 0, right = size - 1;
   	while (left <= right) {
		long sum = A[left] + A[right];
		if (sum < K) {
			++left;
		} else if (sum > K) {
			--right;
		} else {
			dualIndex[0] = left;
			dualIndex[1] = right;
			return;
		}
	}
}

int partition (int A[], int low, int high)
{
    int pivot = A[high];
    int i = (low - 1);

    int temp;
    for (int j = low; j <= high- 1; j++)
    {
        if (A[j] < pivot)
        {
            i++;

            temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    }

    temp = A[i+1];
    A[i+1]= A[high];
    A[high] = temp;
    return (i + 1);
}

void quickSort(int A[], int low, int high)
{
    if (low < high)
    {
        int pivot = partition(A, low, high);

        quickSort(A, low, pivot - 1);
        quickSort(A, pivot + 1, high);
    }
}