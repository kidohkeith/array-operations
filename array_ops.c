/*
 * Array Operations in C: Create, Insert, and Delete
 * Dynamically allocates an array of any user-specified size, inserts a value
 * at a given index (0-based), and deletes a value at a given index or by value.
 */

#include <stdio.h>
#include <stdlib.h>

/* Print all elements currently in the array */
void print_array(const int *arr, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d%s", arr[i], (i < size - 1) ? ", " : "");
    }
    printf("] (size: %d)\n", size);
}

/* 1. Create an array of any size using dynamic memory allocation */
int *create_array(int size) {
    if (size <= 0) {
        fprintf(stderr, "Error: Array size must be greater than 0.\n");
        return NULL;
    }
    int *arr = (int *)malloc((size_t)size * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return NULL;
    }
    return arr;
}

/* 2. Insert a value into the array at a specific 0-based index */
int insert_value(int **arr, int *size, int index, int value) {
    if (index < 0 || index > *size) {
        fprintf(stderr, "Error: Insertion index %d is out of bounds (0 to %d).\n", index, *size);
        return -1;
    }

    int *resized = (int *)realloc(*arr, (size_t)(*size + 1) * sizeof(int));
    if (resized == NULL) {
        fprintf(stderr, "Error: Memory reallocation failed during insertion.\n");
        return -1;
    }
    *arr = resized;

    /* Shift elements to the right to make room at index */
    for (int i = *size; i > index; i--) {
        (*arr)[i] = (*arr)[i - 1];
    }

    (*arr)[index] = value;
    (*size)++;
    return 0;
}

/* 3. Delete a value from the array at a specific 0-based index */
int delete_at_index(int **arr, int *size, int index) {
    if (*size <= 0) {
        fprintf(stderr, "Error: Cannot delete from an empty array.\n");
        return -1;
    }
    if (index < 0 || index >= *size) {
        fprintf(stderr, "Error: Deletion index %d is out of bounds (0 to %d).\n", index, *size - 1);
        return -1;
    }

    /* Shift elements to the left to overwrite the deleted element */
    for (int i = index; i < *size - 1; i++) {
        (*arr)[i] = (*arr)[i + 1];
    }

    (*size)--;
    if (*size > 0) {
        int *resized = (int *)realloc(*arr, (size_t)(*size) * sizeof(int));
        if (resized != NULL) {
            *arr = resized;
        }
    } else {
        free(*arr);
        *arr = NULL;
    }
    return 0;
}

int main(void) {
    int size = 0;

    printf("--- C Dynamic Array Operations ---\n");
    printf("Enter the initial size of the array: ");
    if (scanf("%d", &size) != 1 || size <= 0) {
        fprintf(stderr, "Invalid size entered.\n");
        return 1;
    }

    /* Step 1: Create the array */
    int *arr = create_array(size);
    if (arr == NULL) {
        return 1;
    }

    printf("Enter %d integer elements:\n", size);
    for (int i = 0; i < size; i++) {
        printf("  Element [%d]: ", i);
        if (scanf("%d", &arr[i]) != 1) {
            fprintf(stderr, "Invalid input.\n");
            free(arr);
            return 1;
        }
    }

    printf("\nInitial array: ");
    print_array(arr, size);

    /* Step 2: Insert a value */
    int ins_val = 0, ins_idx = 0;
    printf("\nEnter the value to insert: ");
    scanf("%d", &ins_val);
    printf("Enter the index (0 to %d) to insert at: ", size);
    scanf("%d", &ins_idx);

    if (insert_value(&arr, &size, ins_idx, ins_val) == 0) {
        printf("Array after inserting %d at index %d: ", ins_val, ins_idx);
        print_array(arr, size);
    }

    /* Step 3: Delete a value */
    int del_idx = 0;
    printf("\nEnter the index (0 to %d) to delete from: ", size - 1);
    scanf("%d", &del_idx);

    if (del_idx >= 0 && del_idx < size) {
        int deleted_val = arr[del_idx];
        if (delete_at_index(&arr, &size, del_idx) == 0) {
            printf("Array after deleting %d from index %d: ", deleted_val, del_idx);
            print_array(arr, size);
        }
    } else {
        fprintf(stderr, "Error: Deletion index %d is out of bounds.\n", del_idx);
    }

    free(arr);
    return 0;
}