#include "quicksort.h"

/**
Swapping elements of the array such that
all elements less than the pivot are to the left of it,
and all elements greater than the pivot are to the right.
The pivot is the most right element (element at index right).
Each comparison of array elements is recordred on the comparison counter.
@param arr the array to be partitioned
@param left the index to start the partition from
@param right the index to end the partition - the pivot
@param comparison_counter a pointer to the counter of array comparisons in the
algorithm
@return Pivot's index after the partition
*/
static int partition(int *arr, const int left, const int right, int *comparison_counter) {
    const int pivot = arr[right];
    int lower_than_pivot = left - 1;
    for (int i = left; i < right; i++) {
        if (arr[i] <= pivot) {
            lower_than_pivot++;
            swap(arr, lower_than_pivot, i);
        }
        (*comparison_counter)++;  // Each iteration of the loop contains one
                                  // comparison
    }
    swap(arr, lower_than_pivot + 1, right);
    return lower_than_pivot + 1;
}

/**
Find a pivot which doesn't give the worst case for quick sort.
The pivot chosen is not the maximum element nor the minimum in the array.
The algorithm takes the first 3 elements and returns the middle one, using a
decision tree. Comparisons of the array elements are counted using
comparison_counter.
@param arr the array to be sorted
@param left the index to start the sort from
@param right the index to sort until
@param comparison_counter a pointer to the counter of the comparison
@return the index of the good pivot (not minimal and not maximal element)
*/
static int find_good_pivot(int *arr, const int left, const int right, int *comparison_counter) {
    if (right - left < 3) {
        return left;  // Not relevant when sorting less than three elements.
    }

    const int first = left;
    const int second = left + 1;
    const int third = left + 2;

    // Decision tree repsesented with an if-else tree:
    (*comparison_counter)++;
    if (arr[first] < arr[second]) {
        (*comparison_counter)++;
        if (arr[first] < arr[third]) {
            (*comparison_counter)++;
            if (arr[second] < arr[third]) {
                return second;
            } else {
                return third;
            }
        } else {
            return first;
        }
    } else {
        (*comparison_counter)++;
        if (arr[first] < arr[third]) {
            return first;
        } else {
            (*comparison_counter)++;
            if (arr[second] < arr[third]) {
                return third;
            } else {
                return second;
            }
        }
    }
}

/**
Sort an array, using the quick-sort algorithm.
The algorithm pickes a pivot, then orginazes the array in such a way that
all elements less than the pivot are on the left and the rest are on the right
of the pivot. Then, the algorithms calls itself recursively on each half of the
array. In addition, the algorithm counts each comparison of array elements,
using @see comparison_counter
@param arr the array to sort
@param left the index to sort from
@param right the index to sort until
@param use_good_pivot whether to use a pivot which doesn't give the worst case
or not
@param comparison_counter a pointer to the counter of the comparisons, which is
incremented each comparison
*/
static void quicksort(int *arr, const int left, const int right, const bool use_good_pivot,
                      int *comparison_counter) {
    if (left < right) {
        if (use_good_pivot) {
            const int pivot = find_good_pivot(arr, left, right, comparison_counter);
            swap(arr, pivot,
                 right - 1);  // Swapping the good pivot with the current one
        }
        const int pivot_new_index =
            partition(arr, left, right,
                      comparison_counter);  // Getting pivot's new index after partition

        // Recursive calls
        quicksort(arr, left, pivot_new_index - 1, use_good_pivot, comparison_counter);
        quicksort(arr, pivot_new_index + 1, right, use_good_pivot, comparison_counter);
    }
}

/**
Given an array, count the number of comparisons it takes in order to sort it
using quick-sort.
@param arr array to sort
@param n number of elements in the array
@param use_good_pivot when true, chooses the pivot which is not max or min
*/
int count_comparisons(int *arr, const int n, const bool use_good_pivot) {
    int comparison_counter = 0;
    quicksort(arr, 0, n - 1, use_good_pivot, &comparison_counter);
    return comparison_counter;
}
