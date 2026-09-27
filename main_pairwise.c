/*
 * main_pairwise.c
 * -----------------
 * Part (b) driver: runs the simple sequential pairwise merge on the
 * same three lists and prints every merge step plus operation counts.
 *
 * Build:  make pairwise_merge
 * Run:    ./pairwise_merge
 */

#include <stdio.h>
#include "pairwise_merge.h"

int main(void) {
    int L1[] = {10, 30, 50, 70};
    int L2[] = {20, 40, 60, 80};
    int L3[] = {15, 35, 55, 75};

    int *lists[] = { L1, L2, L3 };
    int sizes[]  = { 4, 4, 4 };
    int k = 3;

    int result[64];

    printf("=== SIMPLE PAIRWISE MERGING ===\n\n");

    MergeCounter mc;
    int count = pairwise_merge_sequential(lists, sizes, k, result, &mc, 1);

    printf("\nMerged output: [");
    for (int i = 0; i < count; i++)
        printf("%d%s", result[i], (i == count - 1) ? "" : ", ");
    printf("]\n");

    printf("\n--- Operation counts ---\n");
    printf("Total comparisons  : %ld\n", mc.comparisons);
    printf("Total merge() calls: %ld\n", mc.merge_calls);

    return 0;
}
