#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "analyzation.h"

int main(int argc, char *argv[]) {
    if (argc <= 2) {
        printf("Expected n and a!\n");
        return 1;
    }
    const int ARR_LENGTH = atoi(argv[1]);
    const float PERCENTAGE_TO_AVERAGE = (float)atoi(argv[2]) / 100.f;

    printf("Running ordinary quicksort:\n");
    const quicksort_analyzation ordinary =
        analyze_quicksort(ARR_LENGTH, PERCENTAGE_TO_AVERAGE, false);

    printf("\nRunning quicksort with good pivot finder:\n");
    const quicksort_analyzation with_good_pivot =
        analyze_quicksort(ARR_LENGTH, PERCENTAGE_TO_AVERAGE, true);

    printf("\n\n-----------------------\n\n");

    printf("N = %d, A = %.2f\n\n", ARR_LENGTH, PERCENTAGE_TO_AVERAGE);

    printf("Ordinary:\n");
    print_analyzation(ordinary);

    printf("\n");

    printf("With Good Pivot:\n");
    print_analyzation(with_good_pivot);

    printf("\n");

    return 0;
}