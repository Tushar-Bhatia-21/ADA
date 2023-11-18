#include <stdio.h>

int binarySearch(int arr[], int left, int right, int key) {
    if (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == key) {
            return mid; // Element found at index mid
        } else if (arr[mid] > key) {
            return binarySearch(arr, left, mid - 1, key); // Search in the left subarray
        } else {
            return binarySearch(arr, mid + 1, right, key); // Search in the right subarray
        }
    }

    return -1; // Element not found
}

int main() {
    printf("\nTushar Bhatia\n");
    printf("A2305221202\n");
    int A[10], size, key, result;
    printf("Enter the size of array: ");
    scanf("%d", &size);

    for (int i = 0; i < size; i++) {
        printf("Enter value for A[%d]: ", i);
        scanf("%d", &A[i]);
    }

    printf("Enter element to search: ");
    scanf("%d", &key);

    result = binarySearch(A, 0, size - 1, key);

    if (result != -1) {
        printf("Element found at index %d\n", result);
    } else {
        printf("Element not found\n");
    }

    return 0;
}
