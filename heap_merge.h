/*
 * heap_merge.h
 * -------------
 * Part (a): Min Heap based k-way merge.
 *
 * Each transaction list is represented as a plain sorted int array
 * (already sorted, as given by the problem). Each heap node stores
 * (value, list_id, index) so that once a value is popped we know
 * exactly which list/position to pull the next candidate from.
 */

#ifndef HEAP_MERGE_H
#define HEAP_MERGE_H

#define MAX_LISTS 10   /* max number of input lists the heap can hold at once */

typedef struct {
    int value;
    int list_id;   /* 0-indexed: which list (L1, L2, ...) this came from */
    int index;     /* position of this value inside that list */
} HeapNode;

typedef struct {
    HeapNode nodes[MAX_LISTS];
    int size;
    long comparisons;  /* comparisons made while sifting up/down */
    long pushes;
    long pops;
} MinHeap;

void heap_init(MinHeap *h);
int  heap_is_empty(const MinHeap *h);
void heap_push(MinHeap *h, HeapNode node);
HeapNode heap_pop(MinHeap *h);
void heap_print(const MinHeap *h, const char *event);

/*
 * Merges `k` sorted lists (lists[0..k-1], each of length sizes[0..k-1])
 * into `result` using a min heap. `result` must be large enough to
 * hold the sum of all sizes. Returns the number of merged elements.
 * If verbose != 0, prints every push/pop heap state to stdout.
 */
int k_way_merge_heap(int *lists[], const int sizes[], int k,
                      int result[], MinHeap *h, int verbose);

#endif /* HEAP_MERGE_H */
