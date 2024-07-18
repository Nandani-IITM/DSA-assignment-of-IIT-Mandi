#include <stdio.h>

void insertionSort(int arr[], int n, int *comparisons, int *swaps) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        (*comparisons)++;
        while (j >= 0 && arr[j] > key) {
            (*swaps)++;
            arr[j + 1] = arr[j];
            j = j - 1;
            (*comparisons)++;
        }
        arr[j + 1] = key;
    }
}

void printArray(int arr[], int n) {
    int i;
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    int arr[] = {30, 10, 1, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    int comparisons = 0;
    int swaps = 0;

    printf("Original array: \n");
    printArray(arr, n);

    insertionSort(arr, n, &comparisons, &swaps);

    printf("\nSorted array: \n");
    printArray(arr, n);

    printf("\nNumber of comparisons: %d\n", comparisons);
    printf("Number of swaps: %d\n", swaps);

    return 0;
}

