#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "insertion_sort.c"
#include "merge_sort.c"
#include "heap_sort.c"
#include "quick_sort.c"
#include "counting_sort.c"
#include "radix_sort.c"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_BOLD          "\x1b[1m"
#define ANSI_COLOR_RESET   "\x1b[0m"

const int LEN = 1000;
const int ROUND = 10;

int comp_int(const void *x1, const void *x2);
void run_test(const char *sort_name, void (*sort_func)(int *, int), int input[], int answer[]);

//testing loop
int main() {
    int input[LEN];
    int answer[LEN];
    srand(time(NULL));

    for (int r = 0; r < ROUND; r++) {
        for (int i = 0; i < LEN; i++) {
            input[i] = rand() % 100;  //keep it within 0-99 for counting/radix
            answer[i] = input[i];
        }

        qsort(answer, LEN, sizeof(int), comp_int);  //correct answer

        printf("#############  Round %d  #############\n", r + 1);
        run_test("Insertion Sort", insertion_sort, input, answer);
        run_test("Merge Sort", merge_sort, input, answer);
        run_test("Heap Sort", heap_sort, input, answer);
        run_test("Quick Sort", quick_sort, input, answer);
        run_test("Counting Sort", counting_sort, input, answer);
        run_test("Radix Sort", radix_sort, input, answer);

        printf("\n\n");
    }

    printf("All tests done.\n");
    return 0;
}

//reusable test wrapper
void run_test(const char *sort_name, void (*sort_func)(int *, int), int input[], int answer[]) {
    int test[LEN];
    memcpy(test, input, sizeof(int) * LEN);
    sort_func(test, LEN);

    if (memcmp(test, answer, sizeof(int) * LEN) == 0) {
        printf(ANSI_BOLD ANSI_COLOR_GREEN "[PASS] %s" ANSI_COLOR_RESET "\n", sort_name);

    } else {
        printf(ANSI_BOLD ANSI_COLOR_RED "[FAIL] %s" ANSI_COLOR_RESET "\n", sort_name);
    }
}

int comp_int(const void *x1, const void *x2) {
    return (*(int *)x1) - (*(int *)x2);
}
