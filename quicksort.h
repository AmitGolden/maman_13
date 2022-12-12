#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <stdbool.h>

#include "utils.h"

int count_comparisons(int *arr, const int n, const bool use_good_pivot);

#endif  // QUICKSORT_H