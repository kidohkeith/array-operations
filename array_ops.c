#include <stdio.h>
#include <stdlib.h>

void display(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Pass capacity by reference to update it when reallocating
int* insertElement(int *arr, int *size, int *capacity, int element, int index) {
    if (index < 0 || index > *size) {
        printf("Error: Invalid index.\n");
        return arr;
    }

    // Expand capacity by doubling it if the array is full
    if (*size >= *capacity) {
        *capacity *= 2;
        arr = (int*)realloc(arr, *capacity * sizeof(int));
        if (arr == NULL) {
            printf("Memory allocation failed!\n");
            exit(1);
        }
    }

    // Shift elements right to make space
    for (int i = *size - 1; i >= index; i--) {
        arr[i + 1] = arr[i];
    }

    arr[index] = element;
    (*size)++;
    return arr;
}

int* deleteElement(int *arr, int *size, int *capacity, int index) {
    if (*size <= 0) {
        printf("Error: Array is empty.\n");
        return arr;
    }
    if (index < 0 || index >= *size) {
        printf("Error: Invalid index.\n");
        return arr;
    }

    // Shift elements left to overwrite the deleted element
    for (int i = index; i < *size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    (*size)--;

    // Memory optimization: Shrink capacity if it's vastly underutilized
    if (*size > 0 && *size == *capacity / 4) {
        *capacity /= 2;
        arr = (int*)realloc(arr, *capacity * sizeof(int));
        if (arr == NULL) {
            printf("Memory reallocation failed!\n");
            exit(1);
        }
    }

    return arr;
}

int main() {
    int capacity = 5;
    int size = 5;
    
    // 1. Allocate initial memory using malloc
    int *arr = (int*)malloc(capacity * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Populate the array
    for(int i = 0; i < size; i++) {
        arr[i] = (i + 1) * 10;
    }

    printf("Original array: ");
    display(arr, size);

    // 2. Insert element (triggers realloc to expand since size == capacity)
    arr = insertElement(arr, &size, &capacity, 25, 2);
    printf("After inserting 25 at index 2: ");
    display(arr, size);

    // 3. Delete element
    arr = deleteElement(arr, &size, &capacity, 3);
    printf("After deleting element at index 3: ");
    display(arr, size);

    // 4. Always free dynamically allocated memory to prevent leaks
    free(arr);
    arr = NULL;

    return 0;
}