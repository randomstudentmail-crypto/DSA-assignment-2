/*
 * heap_merge.c
 * -------------
 * Array-based binary Min Heap (built from scratch, not a library),
 * with operation counters, plus the k-way merge routine that uses it.
 */

#include <stdio.h>
#include "heap_merge.h"

void heap_init(MinHeap *h) {
    h->size = 0;
    h->comparisons = 0;
    h->pushes = 0;
    h->pops = 0;
}

int heap_is_empty(const MinHeap *h) {
    return h->size == 0;
}

static void swap_nodes(HeapNode *a, HeapNode *b) {
    HeapNode tmp = *a;
    *a = *b;
    *b = tmp;
}

static void sift_up(MinHeap *h, int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        h->comparisons++;
        if (h->nodes[idx].value < h->nodes[parent].value) {
            swap_nodes(&h->nodes[idx], &h->nodes[parent]);
            idx = parent;
        } else {
            break;
        }
    }
}

static void sift_down(MinHeap *h, int idx) {
    while (1) {
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;
        int smallest = idx;

        if (left < h->size) {
            h->comparisons++;
            if (h->nodes[left].value < h->nodes[smallest].value) {
                smallest = left;
            }
        }
        if (right < h->size) {
            h->comparisons++;
            if (h->nodes[right].value < h->nodes[smallest].value) {
                smallest = right;
            }
        }
        if (smallest != idx) {
            swap_nodes(&h->nodes[idx], &h->nodes[smallest]);
            idx = smallest;
        } else {
            break;
        }
    }
}

void heap_push(MinHeap *h, HeapNode node) {
    h->nodes[h->size] = node;
    h->size++;
    h->pushes++;
    sift_up(h, h->size - 1);
}

HeapNode heap_pop(MinHeap *h) {
    HeapNode top = h->nodes[0];
    h->pops++;
    h->size--;
    h->nodes[0] = h->nodes[h->size];
    if (h->size > 0) {
        sift_down(h, 0);
    }
    return top;
}

void heap_print(const MinHeap *h, const char *event) {
    printf("%-28s heap = [", event);
    for (int i = 0; i < h->size; i++) {
        printf("(%d, L%d)%s", h->nodes[i].value, h->nodes[i].list_id + 1,
               (i == h->size - 1) ? "" : ", ");
    }
    printf("]\n");
}

int k_way_merge_heap(int *lists[], const int sizes[], int k,
                      int result[], MinHeap *h, int verbose) {
    heap_init(h);
    int result_count = 0;

    /* Step 1: push the first element of every list */
    for (int i = 0; i < k; i++) {
        if (sizes[i] > 0) {
            HeapNode node = { lists[i][0], i, 0 };
            heap_push(h, node);
            if (verbose) {
                char event[64];
                snprintf(event, sizeof(event), "push %d (from L%d)", node.value, i + 1);
                heap_print(h, event);
            }
        }
    }
    if (verbose) heap_print(h, "initial heap built");

    /* Step 2: repeatedly pop the min, push the next element from the same list */
    while (!heap_is_empty(h)) {
        HeapNode top = heap_pop(h);
        result[result_count++] = top.value;
        if (verbose) {
            char event[64];
            snprintf(event, sizeof(event), "pop  %d (from L%d)", top.value, top.list_id + 1);
            heap_print(h, event);
        }

        int next_index = top.index + 1;
        if (next_index < sizes[top.list_id]) {
            int next_val = lists[top.list_id][next_index];
            HeapNode node = { next_val, top.list_id, next_index };
            heap_push(h, node);
            if (verbose) {
                char event[64];
                snprintf(event, sizeof(event), "push %d (from L%d)", next_val, top.list_id + 1);
                heap_print(h, event);
            }
        }
    }

    return result_count;
}
