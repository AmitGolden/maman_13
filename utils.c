#include "utils.h"

#include <stdio.h>

void swap(int *arr, const int x, const int y) {
    const int temp = arr[x];
    arr[x] = arr[y];
    arr[y] = temp;
}

int factorial(const int n) {
    if (n <= 1) return 1;

    int product = 1;
    for (int i = 1; i <= n; i++) {
        product *= i;
    }
    return product;
}

void print_array(int *arr, const int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void array_copy(const int *source, int *destination, const int n) {
    for (int i = 0; i < n; i++) destination[i] = source[i];
}
void array_copy_64(const uint64_t *source, uint64_t *destination, const int n) {
    for (int i = 0; i < n; i++) destination[i] = source[i];
}

void reverse(int *arr, int left, int right) {
    while (right > left) {
        swap(arr, left, right);
        left++;
        right--;
    }
}

void fill_array_1_to_n(int *arr, const int n) {
    for (int i = 0; i < n; i++) arr[i] = i + 1;
}

void fill_array_zero(uint64_t *arr, const int n) {
    for (int i = 0; i < n; i++) arr[i] = 0;
}