# K-Way Merge of Sorted Transaction Lists (C Version) — DSA Project

A small Data Structures & Algorithms project (in C) that merges
multiple already-sorted transaction lists using two different
techniques and compares them:

1. **K-way merge using a Min Heap** (`src/heap_merge.c` / `.h`)
2. **Simple sequential pairwise merging** (`src/pairwise_merge.c` / `.h`)

## Problem statement

A financial system receives three already sorted transaction lists:

```
L1 = 10, 30, 50, 70
L2 = 20, 40, 60, 80
L3 = 15, 35, 55, 75
```

- **(a)** Represent the three lists using suitable data structures and
  implement a k-way merge using a Min Heap. Show the important heap
  states during execution.
- **(b)** Implement a simple pairwise merging approach for the same
  lists. Execute both approaches and record the number of major
  operations.
- **(c)** Analyse and compare heap size, number of comparisons, time
  complexity, space requirements, and determine which approach is more
  suitable as the number of sorted files increases.

## Project structure

```
dsa-kway-merge-c/
├── README.md                  <- this file
├── Makefile                   <- builds all three executables
├── src/
│   ├── heap_merge.h / .c      <- part (a): custom Min Heap + k-way merge
│   ├── pairwise_merge.h / .c  <- part (b): sequential pairwise merge
│   ├── main_heap.c            <- driver: runs part (a) alone
│   ├── main_pairwise.c        <- driver: runs part (b) alone
│   └── main_compare.c         <- driver: runs both + comparison table
└── docs/
    └── ANALYSIS.md            <- part (c): full written analysis
```

## Data structures used

- **Each transaction list** is a plain sorted C array (`int[]`) — the
  natural fit since the lists arrive already sorted and are only ever
  scanned left to right.
- **The heap** is a custom **array-based binary Min Heap** (`MinHeap`
  struct in `heap_merge.h`), implemented from scratch (no library heap
  used) so the code can count comparisons/pushes/pops for the analysis
  in part (c). Each heap node (`HeapNode`) stores
  `(value, list_id, index)` — the value, which list it came from, and
  its position in that list — so that once it's popped we know exactly
  which element to push next.

## How to build and run

Requires only `gcc` (or any C11 compiler) and `make`. No external
libraries.

```bash
make            # builds all three executables
./k_way_merge_heap     # part (a) — prints every heap state
./pairwise_merge       # part (b) — prints every merge step
./compare_analysis     # runs both + prints the comparison table
make clean      # remove built binaries
```

## Sample output (heap states) — part (a)

```
push 10 (from L1)            heap = [(10, L1)]
push 20 (from L2)            heap = [(10, L1), (20, L2)]
push 15 (from L3)            heap = [(10, L1), (20, L2), (15, L3)]
initial heap built           heap = [(10, L1), (20, L2), (15, L3)]
pop  10 (from L1)            heap = [(15, L3), (20, L2)]
push 30 (from L1)            heap = [(15, L3), (20, L2), (30, L1)]
pop  15 (from L3)            heap = [(20, L2), (30, L1)]
push 35 (from L3)            heap = [(20, L2), (30, L1), (35, L3)]
pop  20 (from L2)            heap = [(30, L1), (35, L3)]
push 40 (from L2)            heap = [(30, L1), (35, L3), (40, L2)]
pop  30 (from L1)            heap = [(35, L3), (40, L2)]
push 50 (from L1)            heap = [(35, L3), (40, L2), (50, L1)]
pop  35 (from L3)            heap = [(40, L2), (50, L1)]
push 55 (from L3)            heap = [(40, L2), (50, L1), (55, L3)]
pop  40 (from L2)            heap = [(50, L1), (55, L3)]
push 60 (from L2)            heap = [(50, L1), (55, L3), (60, L2)]
pop  50 (from L1)            heap = [(55, L3), (60, L2)]
push 70 (from L1)            heap = [(55, L3), (60, L2), (70, L1)]
pop  55 (from L3)            heap = [(60, L2), (70, L1)]
push 75 (from L3)            heap = [(60, L2), (70, L1), (75, L3)]
pop  60 (from L2)            heap = [(70, L1), (75, L3)]
push 80 (from L2)            heap = [(70, L1), (75, L3), (80, L2)]
pop  70 (from L1)            heap = [(75, L3), (80, L2)]
pop  75 (from L3)            heap = [(80, L2)]
pop  80 (from L2)            heap = []
```

Final merged output (both approaches agree):

```
10, 15, 20, 30, 35, 40, 50, 55, 60, 70, 75, 80
```

## Recorded operation counts — part (b)

| Metric                            | Heap-based k-way merge | Pairwise sequential merge |
|------------------------------------|:----------------------:|:--------------------------:|
| Element comparisons                | 21                      | 18                          |
| Push / Pop (heap) or merge() calls | 12 pushes / 12 pops     | 2 merge() calls             |
| Max heap size                      | 3                       | — (not applicable)          |

(Full discussion in `docs/ANALYSIS.md`.)

## License

Feel free to use this for coursework / learning purposes.
