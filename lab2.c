#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Partition function
int partition(int arr[], int lb, int ub) {
    int pivot = arr[ub]; // Pivot element
    int i = (lb - 1);    // Index of smaller element

    for (int j = lb; j < ub; j++) {
        if (arr[j] <= pivot) {
            i++;
            // Swap arr[i] and arr[j]
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    // Swapping arr[i + 1] and arr[ub]
    int temp = arr[i + 1];
    arr[i + 1] = arr[ub];
    arr[ub] = temp;

    return (i + 1);
}

// Quick Sort function
void quickSort(int arr[], int lb, int ub) {
    if (lb < ub) {
        int m = partition(arr, lb, ub);

        quickSort(arr, lb, m - 1); // Elements before m
        quickSort(arr, m + 1, ub);  // Elements after m
    }
}

// Random array generation
void RandomArr(int arr[], int size) {
    for (int i = 0; i < size; i++)
        arr[i] = rand() % 1000; // Random numbers between 0 and 999
}

int main() {
    int n;

    srand(time(NULL)); // Seed for random number generation

    printf("Enter the number of elements: ");
    scanf("%d", &n);

    // Memory allocation
    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Input random values into the array
    RandomArr(arr, n);

    // Timer starts
    clock_t start_time = clock();

    // Call to quickSort
    quickSort(arr, 0, n - 1);

    // Timer ends
    clock_t end_time = clock();

    // Calculate and print execution time
    double time_taken = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Execution time: %f seconds\n", time_taken);

    // Free memory
    free(arr);

    return 0;
}