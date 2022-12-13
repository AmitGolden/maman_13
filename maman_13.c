#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "analyzation.h"

int main(int argc, char *argv[]) {
    // Getting the parameters to the program from the terminal:
    // First is the array length, and second is the best/worst percentage to average.
    if (argc <= 2) {
        printf("Expected n and a!\n");
        return 1; // Exit with error when not provided with enough arguments.
    }
    const int ARR_LENGTH = atoi(argv[1]);
    const float PERCENTAGE_TO_AVERAGE = (float)atoi(argv[2]) / 100.f;

    // Analyze for quicksort without good_pivot
    printf("Running ordinary quicksort:\n");
    const quicksort_analyzation ordinary =
        analyze_quicksort(ARR_LENGTH, PERCENTAGE_TO_AVERAGE, false);

    // Analyze for quicksort with good_pivot
    printf("\nRunning quicksort with good pivot finder:\n");
    const quicksort_analyzation with_good_pivot =
        analyze_quicksort(ARR_LENGTH, PERCENTAGE_TO_AVERAGE, true);

    printf("\n\n-----------------------\n\n");

    // Print parameters from the user.
    printf("N = %d, A = %.2f\n\n", ARR_LENGTH, PERCENTAGE_TO_AVERAGE);

    // Print analyzations:
    printf("Ordinary:\n");
    print_analyzation(ordinary);

    printf("\n");

    printf("With Good Pivot:\n");
    print_analyzation(with_good_pivot);

    printf("\n");

    return 0;
}
