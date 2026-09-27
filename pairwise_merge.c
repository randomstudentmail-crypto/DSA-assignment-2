/*
 * pairwise_merge.c
 * ------------------
 * Standard two-way merge, applied sequentially across k lists.
 */

#include <stdio.h>
#include <string.h>
#include "pairwise_merge.h"

int merge_two_sorted_arrays(const int a[], int na, const int b[], int nb,
                             int result[], MergeCounter *mc) {
    mc->merge_calls++;
    int i = 0, j = 0, m = 0;

    while (i < na && j < nb) {
        mc->comparisons++;
        if (a[i] <= b[j]) {
            result[m++] = a[i++];
        } else {
            result[m++] = b[j++];
        }
    }
    /* leftover elements: no comparisons needed, just copy */
    while (i < na) result[m++] = a[i++];
    while (j < nb) result[m++] = b[j++];

    return m;
}

int pairwise_merge_sequential(int *lists[], const int sizes[], int k,
                               int result[], MergeCounter *mc, int verbose) {
    mc->comparisons = 0;
    mc->merge_calls = 0;

    if (k <= 0) return 0;

    /* start with a copy of the first list in `result` */
    int result_count = sizes[0];
    memcpy(result, lists[0], sizes[0] * sizeof(int));

    if (verbose) {
        printf("Start        : L1 = [");
        for (int i = 0; i < result_count; i++)
            printf("%d%s", result[i], (i == result_count - 1) ? "" : ", ");
        printf("]\n");
    }

    int temp[1024]; /* scratch buffer, large enough for this exercise */

    for (int step = 1; step < k; step++) {
        int merged_count = merge_two_sorted_arrays(result, result_count,
                                                     lists[step], sizes[step],
                                                     temp, mc);
        memcpy(result, temp, merged_count * sizeof(int));
        result_count = merged_count;

        if (verbose) {
            printf("Merge step %-2d: merge(current_result, L%d) -> [", step, step + 1);
            for (int i = 0; i < result_count; i++)
                printf("%d%s", result[i], (i == result_count - 1) ? "" : ", ");
            printf("]\n");
        }
    }

    return result_count;
}
