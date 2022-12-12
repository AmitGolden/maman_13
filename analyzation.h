#ifndef ANALYZATION_H
#define ANALYZATION_H

#include <stdbool.h>

typedef struct quicksort_analyzation {
    const float total_average;
    const float worst_average;
    const float best_average;
} quicksort_analyzation;

const quicksort_analyzation analyze_quicksort(const int n, const float a,
                                              const bool use_good_pivot);
void print_analyzation(const quicksort_analyzation analyzation);

#endif  // ANALYZATION_H