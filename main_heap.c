/*
 * main_heap.c
 * ------------
 * Part (a) driver: builds the three transaction lists, runs the
 * heap-based k-way merge, and prints every heap state plus the
 * final operation counts.
 *
 * Build:  make k_way_merge_heap
 * Run:    ./k_way_merge_heap
 */

#include <stdio.h>
#include "heap_merge.h"

int main(void) {
    int L1[] = {10, 30, 50, 70};
    int L2[] = {20, 40, 60, 80};
    int L3[] = {15, 35, 55, 75};

    int *lists[] = { L1, L2, L3 };
    int sizes[]  = { 4, 4, 4 };
    int k = 3;

    int total = sizes[0] + sizes[1] + sizes[2];
    int result[64];

    printf("=== K-WAY MERGE USING MIN HEAP ===\n\n");

    MinHeap h;
    int count = k_way_merge_heap(lists, sizes, k, result, &h, 1);

    printf("\nMerged output: [");
    for (int i = 0; i < count; i++)
        printf("%d%s", result[i], (i == count - 1) ? "" : ", ");
    printf("]\n");

    printf("\n--- Operation counts ---\n");
    printf("Total comparisons : %ld\n", h.comparisons);
    printf("Total pushes      : %ld\n", h.pushes);
    printf("Total pops        : %ld\n", h.pops);
    printf("Max heap size reached: %d (k = number of lists)\n", k);
    (void)total;

    return 0;
}
