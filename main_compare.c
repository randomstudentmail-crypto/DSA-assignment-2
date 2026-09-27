/*
 * main_compare.c
 * ----------------
 * Runs BOTH approaches on the same input and prints a side-by-side
 * table of major operation counts and timing, for part (b)/(c).
 *
 * Build:  make compare_analysis
 * Run:    ./compare_analysis
 */

#include <stdio.h>
#include <time.h>
#include <string.h>
#include "heap_merge.h"
#include "pairwise_merge.h"

static void print_array(const int arr[], int n) {
    printf("[");
    for (int i = 0; i < n; i++)
        printf("%d%s", arr[i], (i == n - 1) ? "" : ", ");
    printf("]");
}

int main(void) {
    int L1[] = {10, 30, 50, 70};
    int L2[] = {20, 40, 60, 80};
    int L3[] = {15, 35, 55, 75};

    int *lists[] = { L1, L2, L3 };
    int sizes[]  = { 4, 4, 4 };
    int k = 3;

    printf("Input lists:\n");
    for (int i = 0; i < k; i++) {
        printf("  L%d = ", i + 1);
        print_array(lists[i], sizes[i]);
        printf("\n");
    }
    printf("\n");

    int heap_result[64], pair_result[64];

    printf("############################################################\n");
    printf("HEAP-BASED K-WAY MERGE\n");
    printf("############################################################\n");
    clock_t t0 = clock();
    MinHeap h;
    int heap_count = k_way_merge_heap(lists, sizes, k, heap_result, &h, 1);
    clock_t t1 = clock();
    double heap_time = (double)(t1 - t0) / CLOCKS_PER_SEC;

    printf("\n############################################################\n");
    printf("SIMPLE PAIRWISE MERGE\n");
    printf("############################################################\n");
    clock_t t2 = clock();
    MergeCounter mc;
    int pair_count = pairwise_merge_sequential(lists, sizes, k, pair_result, &mc, 1);
    clock_t t3 = clock();
    double pair_time = (double)(t3 - t2) / CLOCKS_PER_SEC;

    int match = (heap_count == pair_count) &&
                (memcmp(heap_result, pair_result, heap_count * sizeof(int)) == 0);

    printf("\n============================================================\n");
    printf("SUMMARY TABLE\n");
    printf("============================================================\n");
    printf("%-38s : %s\n", "Correct merged output matches?", match ? "Yes" : "No");
    printf("%-38s : %d\n", "Max heap size (heap approach)", k);
    printf("%-38s : %ld\n", "Comparisons (heap approach)", h.comparisons);
    printf("%-38s : %ld / %ld\n", "Pushes / Pops (heap approach)", h.pushes, h.pops);
    printf("%-38s : %ld\n", "Comparisons (pairwise approach)", mc.comparisons);
    printf("%-38s : %ld\n", "merge() calls (pairwise approach)", mc.merge_calls);
    printf("%-38s : %.8f\n", "Time - heap approach (s)", heap_time);
    printf("%-38s : %.8f\n", "Time - pairwise approach (s)", pair_time);

    printf("\nFinal merged result: ");
    print_array(heap_result, heap_count);
    printf("\n");

    return 0;
}
