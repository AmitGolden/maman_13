#include "analyzation.h"

#include <math.h>
#include <stdio.h>

#include "quicksort.h"
#include "utils.h"

void print_analyzation(const quicksort_analyzation analyzation) {
    printf("Total Average: %.2f\n", analyzation.total_average);
    printf("Worst Average: %.2f\n", analyzation.worst_average);
    printf("Best Average: %.2f\n", analyzation.best_average);
}

void print_percentage(const uint64_t total, const uint64_t current) {
    const float percentage = (float)current * 100 / (float)total;
    if (current % 1000000 == 0) {
        printf("\r%.1f%%", percentage);
        fflush(stdout);
    }
}

static void generate_next_permutation(int *arr, const int n) {
    int i = n - 2;
    while (i >= 0 && arr[i] > arr[i + 1]) {
        i--;
    }

    if (i == -1) return;

    int c = i + 1;
    for (int j = i + 2; j < n; j++) {
        if (arr[i] < arr[j] && arr[j] < arr[c]) {
            c = j;
        }
    }

    swap(arr, i, c);
    reverse(arr, i + 1, n - 1);
}

static float get_comparisons_average_of_a(const uint64_t *counters,
                                          const int num_counters,
                                          const uint64_t total_num_permutations,
                                          const float a,
                                          const bool best_cases) {
    uint64_t counters_copy[num_counters];
    array_copy_64(counters, counters_copy, num_counters);

    const uint64_t num_of_permutations_to_average =
        ceilf(total_num_permutations * a);
    int counter_index = best_cases ? 0 : (num_counters - 1);
    uint64_t sum = 0;
    for (uint64_t i = 0; i < num_of_permutations_to_average;) {
        if (counters_copy[counter_index] <= 0) {
            if (best_cases)
                counter_index++;
            else
                counter_index--;
            continue;
        }

        sum += counter_index;
        counters_copy[counter_index]--;
        i++;
    }
    return (float)sum / (float)num_of_permutations_to_average;
}

const quicksort_analyzation analyze_quicksort(const int n, const float a,
                                              const bool use_good_pivot) {
    const int max_comparisons = (n / 2 + 3) * (n - 1);
    uint64_t comparison_counters[max_comparisons];
    fill_array_zero(comparison_counters, max_comparisons);

    int permutation[n];
    fill_array_1_to_n(permutation, n);
    const uint64_t number_of_permutations = factorial(n);
    int permutation_copy[n];

    for (uint64_t i = 0; i < number_of_permutations; i++) {
        array_copy(permutation, permutation_copy, n);
        const int num_comp =
            count_comparisons(permutation_copy, n, use_good_pivot);
        comparison_counters[num_comp]++;
        generate_next_permutation(permutation, n);
        print_percentage(number_of_permutations, i);
    }

    printf("\nCalculating average...\n");

    const float best_average = get_comparisons_average_of_a(
        comparison_counters, max_comparisons, number_of_permutations, a, true);
    const float worst_average = get_comparisons_average_of_a(
        comparison_counters, max_comparisons, number_of_permutations, a, false);
    const float total_average = get_comparisons_average_of_a(
        comparison_counters, max_comparisons, number_of_permutations, 1, true);

    return (quicksort_analyzation){
        total_average,
        worst_average,
        best_average,
    };
}