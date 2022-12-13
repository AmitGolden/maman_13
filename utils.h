#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

void swap(int *arr, const int x, const int y);
uint64_t factorial(const int n);
void print_array(int *arr, const int n);
void array_copy(const int *source, int *destination, const int n);
void array_copy_64(const uint64_t *source, uint64_t *destination, const int n);
void reverse(int *arr, int left, int right);
void fill_array_1_to_n(int *arr, const int n);
void fill_array_zero(uint64_t *arr, const int n);

#endif  // UTILS_H