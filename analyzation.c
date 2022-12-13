#include "analyzation.h"

#include <math.h>
#include <stdio.h>

#include "quicksort.h"
#include "utils.h"

/**
Print an analyzation to the screen.
Printing the total average, worst average, and best average in seperate lines.
@param analyzation the analyzation to print
*/
void print_analyzation(const quicksort_analyzation analyzation) {
    printf("Total Average: %.2f\n", analyzation.total_average);
    printf("Worst Average: %.2f\n", analyzation.worst_average);
    printf("Best Average: %.2f\n", analyzation.best_average);
}

/**
Print the percentage of the running progress of the program.
@param current index of the current permutation
@param total the number of the total permutations
*/
void print_percentage(const uint64_t total, const uint64_t current) {
    const float percentage = (float)current * 100 / (float)total;
    if (current % 1000000 == 0) { // In order to not clog the terminal - print percentage every million permutations
        printf("\r%.1f%%", percentage);
        fflush(stdout);
    }
}

/**
Genetates the next permutation to analyze, given the previous permutation.
@param arr the previous permutation
@param n the number of elements in each permutation
*/
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

/**
Get the number of comparisons average across 'a' percentage of the best/worst permutations.
When analyzing the algorithm for multiple permutations, the program is keeping
an array of counters, indicating how many times has occured a permutation which took
a certain number of comparisons to sort, depending on the index.
i.e. the number of times it took quicksort 'k' comparisons to sort the array is kept in the k-th index in the counters array.
@param counters the array, which stores the number of times it took quicksort to sort permutations with the number of comparisons equaling the index
@param num_counters the length of the counters array
@param total_num_permutations the number of total permutations the algorithm analyzed
@param a the percentage of cases to average, in range of between 0 to 1
@param best_cases whether to take average of the best worst a cases. 'true' is best; 'false' is worst.
@return the avarage of the number of comparisons for best/worst 'a' permutations for quick-sort.
*/
static float get_comparisons_average_of_a(const uint64_t *counters,
                                          const int num_counters,
                                          const uint64_t total_num_permutations,
                                          const float a,
                                          const bool best_cases) {
    // Copying the counters array, in order to not modify the original.
    uint64_t counters_copy[num_counters];
    array_copy_64(counters, counters_copy, num_counters);

    const uint64_t num_of_permutations_to_average =
        ceilf(total_num_permutations * a); // Calculate the number of permutations the average includes, depending on 'a'.
    int counter_index = best_cases ? 0 : (num_counters - 1); // The index of the counter in the counters array that is currently checked.
    uint64_t sum = 0;
    for (uint64_t i = 0; i < num_of_permutations_to_average;) { // Note: Not incrementing each iteration.
        // Check if there are cases which had counter_index number of comparisons.
        // If not, then change counter_index (based on best_cases) to the next index.
        if (counters_copy[counter_index] <= 0) { 
            if (best_cases)
                counter_index++;
            else
                counter_index--;
            continue; // Continue in loop, without incrementing 'i' and adding anything to the sum.
        }

        sum += counter_index; // Summing cases
        counters_copy[counter_index]--; // Decrementing the number of cases for counter_index
        i++; // Counting how many permutations have we summed so far
    }
    return (float)sum / (float)num_of_permutations_to_average; // Return sum divided by number of cases
}

/**
Analyze the quick-sort for all permutations in size n, and take average of the best and worst 'a' permutations.
@param n size of permutations to analyze
@param a the percentage of the average to analyze for the best/worst cases (between 0 and 1).
@param use_good_pivot whether to use the good_pivot algorithm when sorting the array
@return the analyzation of the algorithm, containing the average for the best and worst cases, and a total average.
*/
const quicksort_analyzation analyze_quicksort(const int n, const float a,
                                              const bool use_good_pivot) {
    const int max_comparisons = (n * (n + 7)) / 2; // The maximum number of comparisons a permutation could have is n(n+7)/2.
    uint64_t comparison_counters[max_comparisons];
    fill_array_zero(comparison_counters, max_comparisons); // Creating comparison counters arrays and initializing to zero.

    int permutation[n];
    fill_array_1_to_n(permutation, n); // First permutation is (1,2,3...n)
    const uint64_t number_of_permutations = factorial(n); // n! is the number of possible permutations for arrays with size n.
    int permutation_copy[n];

    for (uint64_t i = 0; i < number_of_permutations; i++) {
        // Copying the permutation to another array and sorting it in place with quick-sort.
        array_copy(permutation, permutation_copy, n);
        // Get the number of comparisons it took to sort the array.
        const int num_comp =
            count_comparisons(permutation_copy, n, use_good_pivot);
        comparison_counters[num_comp]++; // Saving the permutation's result (number of comparisons)
        generate_next_permutation(permutation, n); // Generating the next permutation to sort, based on the current one.
        print_percentage(number_of_permutations, i); // Printing the progress to the screen.
    }

    printf("\nCalculating average...\n");

    // Constructing the analyzation
    const float best_average = get_comparisons_average_of_a(
        comparison_counters, max_comparisons, number_of_permutations, a, true);
    const float worst_average = get_comparisons_average_of_a(
        comparison_counters, max_comparisons, number_of_permutations, a, false);
    // The total average is calculated via the same method with a=1
    const float total_average = get_comparisons_average_of_a(
        comparison_counters, max_comparisons, number_of_permutations, 1, true);

    return (quicksort_analyzation){
        total_average,
        worst_average,
        best_average,
    };
}
