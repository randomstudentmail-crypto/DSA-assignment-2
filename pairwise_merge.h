/*
 * pairwise_merge.h
 * ------------------
 * Part (b): Simple pairwise merging approach.
 *
 * result = merge(L1, L2); result = merge(result, L3); ... sequentially,
 * mirroring the classic merge-sort "merge step" applied repeatedly.
 */

#ifndef PAIRWISE_MERGE_H
#define PAIRWISE_MERGE_H

typedef struct {
    long comparisons;
    long merge_calls;
} MergeCounter;

/*
 * Merges two sorted arrays a[0..na-1] and b[0..nb-1] into `result`
 * (which must be at least na+nb in size). Returns na+nb.
 */
int merge_two_sorted_arrays(const int a[], int na, const int b[], int nb,
                             int result[], MergeCounter *mc);

/*
 * Merges k sorted lists sequentially: result = merge(merge(merge(L1,L2),L3)...).
 * `result` must be large enough to hold the sum of all sizes.
 * If verbose != 0, prints the result of every merge step.
 * Returns the number of merged elements.
 */
int pairwise_merge_sequential(int *lists[], const int sizes[], int k,
                               int result[], MergeCounter *mc, int verbose);

#endif /* PAIRWISE_MERGE_H */
