#include "utils.h"

#include <stdio.h>

/**
@param arr the array in which the elements are swapped
@param x index to be swapped with y
@param y index to be swapped with x
*/
void swap(int *arr, const int x, const int y) {
    const int temp = arr[x];
    arr[x] = arr[y];
    arr[y] = temp;
}

/**
@param n the number whose factorial will be calculated
@return the factorial of n
*/
uint64_t factorial(const int n) {
    if (n <= 1) return 1;

    uint64_t product = 1;
    for (int i = 1; i <= n; i++) {
        product *= i;
    }
    return product;
}

/**
prints array values in order with a comma seperator (,)
@param arr the array to be printed
@param n the length of the array
*/
void print_array(int *arr, const int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/**
@param source the array to be copied
@param destination the place the array will be copied to
@param n number of elements to copy
*/
void array_copy(const int *source, int *destination, const int n) {
    for (int i = 0; i < n; i++) destination[i] = source[i];
}

/**
same as @see array_copy but for uint64_t
*/
void array_copy_64(const uint64_t *source, uint64_t *destination, const int n) {
    for (int i = 0; i < n; i++) destination[i] = source[i];
}

/**
@param arr the array to be reversed
@param left the index to start the reverse from
@param right the index to end the reverse
*/
void reverse(int *arr, int left, int right) {
    while (right > left) {
        swap(arr, left, right);
        left++;
        right--;
    }
}

/**
fills an array with the values (1,2,3..n)
@param arr the array to be filled
@param n number of elements to fill
*/
void fill_array_1_to_n(int *arr, const int n) {
    for (int i = 0; i < n; i++) arr[i] = i + 1;
}

/**
fill an array with zeros
@param arr the array to be filled
@param n number of zeros to fill 
*/
void fill_array_zero(uint64_t *arr, const int n) {
    for (int i = 0; i < n; i++) arr[i] = 0;
}
