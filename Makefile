CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -O2

.PHONY: all clean

all: k_way_merge_heap pairwise_merge compare_analysis

k_way_merge_heap: src/heap_merge.c src/main_heap.c src/heap_merge.h
	$(CC) $(CFLAGS) -o k_way_merge_heap src/heap_merge.c src/main_heap.c

pairwise_merge: src/pairwise_merge.c src/main_pairwise.c src/pairwise_merge.h
	$(CC) $(CFLAGS) -o pairwise_merge src/pairwise_merge.c src/main_pairwise.c

compare_analysis: src/heap_merge.c src/pairwise_merge.c src/main_compare.c src/heap_merge.h src/pairwise_merge.h
	$(CC) $(CFLAGS) -o compare_analysis src/heap_merge.c src/pairwise_merge.c src/main_compare.c

clean:
	rm -f k_way_merge_heap pairwise_merge compare_analysis
