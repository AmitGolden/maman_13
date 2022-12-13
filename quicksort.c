#include "quicksort.h"

static int partition(int *arr, const int left, const int right,
                     int *comparison_counter) {
    const int pivot = arr[right];
    int lower_than_pivot = left - 1;
    for (int i = left; i < right; i++) {
        if (arr[i] <= pivot) {
            lower_than_pivot++;
            swap(arr, lower_than_pivot, i);
        }
        (*comparison_counter)++;
    }
    swap(arr, lower_than_pivot + 1, right);
    return lower_than_pivot + 1;
}

static int find_good_pivot(int *arr, const int left, const int right,
                           int *comparison_counter) {
    if (right - left < 3) {
        return left;
    }

    const int first = left;
    const int second = left + 1;
    const int third = left + 2;

    if (arr[first] < arr[second]) {
        (*comparison_counter)++;
        if (arr[first] < arr[third]) {
            (*comparison_counter)++;
            if (arr[second] < arr[third]) {
                (*comparison_counter)++;
                return second;
            } else {
                return third;
            }
        } else {
            return first;
        }
    } else {
        if (arr[first] < arr[third]) {
            (*comparison_counter)++;
            return first;
        } else {
            if (arr[second] < arr[third]) {
                (*comparison_counter)++;
                return third;
            } else {
                return second;
            }
        }
    }
}

static void quicksort(int *arr, const int left, const int right,
                      const bool use_good_pivot, int *comparison_counter) {
    if (left < right) {
        if (use_good_pivot) {
            const int pivot =
                find_good_pivot(arr, left, right, comparison_counter);
            swap(arr, pivot, right - 1);
        }
        const int pivot_new_index =
            partition(arr, left, right, comparison_counter);

        quicksort(arr, left, pivot_new_index - 1, use_good_pivot,
                  comparison_counter);
        quicksort(arr, pivot_new_index + 1, right, use_good_pivot,
                  comparison_counter);
    }
}

int count_comparisons(int *arr, const int n, const bool use_good_pivot) {
    int comparison_counter = 0;
    quicksort(arr, 0, n - 1, use_good_pivot, &comparison_counter);
    return comparison_counter;
}