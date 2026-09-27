# Part (c): Analysis and Comparison

Input used for measurement (k = 3 sorted lists, n = 4 elements each,
N = 12 total elements):

```
L1 = 10, 30, 50, 70
L2 = 20, 40, 60, 80
L3 = 15, 35, 55, 75
```

Numbers below were produced by building and running `compare_analysis`
(`make && ./compare_analysis`).

## 1. Heap size

| Approach                | Heap / auxiliary size used                          |
|--------------------------|------------------------------------------------------|
| Heap-based k-way merge   | Never holds more than **k = 3** elements at once (one candidate per input list). Max heap size observed = **3**. |
| Pairwise sequential merge| No heap is used at all — space is `O(1)` extra apart from the arrays being merged. |

The heap size for the k-way approach stays fixed at **k**, the number
of input lists, regardless of how long each list is. This is the key
structural difference from the pairwise approach.

## 2. Number of comparisons

| Approach                 | Comparisons recorded |
|----------------------------|:--------------------:|
| Heap-based k-way merge     | **21**                |
| Pairwise sequential merge  | **18**                |

For this *tiny* example (only 3 lists of 4 elements = 12 items total),
the pairwise approach actually performs slightly *fewer* raw
comparisons, because the heap also spends comparisons maintaining its
internal structure (sift-up/sift-down) on top of the "who is
smallest" comparisons. This overhead is the classic trade-off: the
heap approach pays a constant-factor cost (`log k` per operation) even
when `k` is small — but that overhead is what makes it scale so much
better once `k` grows (see below).

## 3. Time complexity

Let **N** = total number of elements across all lists, and **k** =
number of sorted lists.

| Approach                | Time complexity | Why |
|---------------------------|:----------------:|-----|
| Heap-based k-way merge    | **O(N log k)**   | Each of the N elements is pushed and popped once; each push/pop costs `O(log k)` because the heap never holds more than `k` elements. |
| Pairwise sequential merge | **O(N × k)**     | There are `k − 1` merge steps. The *i*-th merge combines a running result of size `i × n` with the next list of size `n`, costing `O(i × n)`. Summed over all steps this is `O(N × k)` in the worst case (specifically `O(n·k²)` when all lists are the same size `n`). |

So although the pairwise approach can look cheaper on very small
inputs (as seen above with only 18 vs 21 comparisons), its cost grows
**quadratically in k**, while the heap approach grows only
**log-linearly in k**. As `k` increases, the heap approach wins by an
increasing margin.

## 4. Space requirements

| Approach                | Extra space (beyond the output array) |
|---------------------------|:----------------------------------------:|
| Heap-based k-way merge    | `O(k)` — the heap array holds at most one element per list. |
| Pairwise sequential merge | `O(1)` extra bookkeeping per merge step, but it repeatedly writes new intermediate result arrays; a naive implementation needs a scratch buffer up to `O(N)` by the last step, even though only one intermediate array is alive at a time. |

Both approaches need `O(N)` space for the final merged output; the
heap approach's real advantage is that its *auxiliary* bookkeeping
structure (the heap array) stays small (`O(k)`) no matter how large N
gets. In the C implementation this is visible directly: `MinHeap`
uses a fixed `MAX_LISTS`-sized array, while `pairwise_merge.c` uses a
`temp[]` scratch buffer sized for the full merged output.

## 5. Summary table

| Criterion            | Heap-based k-way merge | Pairwise sequential merge |
|-----------------------|:------------------------:|:---------------------------:|
| Heap / aux. size       | O(k)                    | O(1) per step (but repeated intermediate arrays) |
| Comparisons (this run) | 21                       | 18                            |
| Time complexity        | **O(N log k)**           | O(N·k)                       |
| Space (auxiliary)      | O(k)                     | up to O(N) scratch buffer    |
| Scales well as k grows?| **Yes**                  | No                            |

## 6. Which approach is more suitable as the number of sorted files (k) increases?

**The heap-based k-way merge is the better choice as k grows.**

- Its time complexity, `O(N log k)`, grows only logarithmically with
  the number of input lists, so doubling the number of transaction
  files barely increases the per-element cost.
- The pairwise approach's `O(N·k)` behaviour means that adding more
  files makes *every remaining element* more expensive to place,
  because each new list has to be merged against an
  ever-growing accumulated result. With many files this becomes
  noticeably slower.
- The heap's auxiliary memory footprint, `O(k)`, is tiny and grows
  slowly, whereas the pairwise approach keeps re-materializing larger
  and larger intermediate merged arrays.

**Conclusion:** for a small, fixed number of lists (like the k = 3
example here) the two approaches perform comparably, and the simple
pairwise merge is easier to reason about and implement. But for a real
financial system that may need to merge transactions from many
files/sources (large k — e.g. dozens or hundreds of branch/daily
transaction logs), the **Min-Heap-based k-way merge is clearly the
more suitable and scalable approach**, which is exactly why it's the
standard technique used in external sorting and multi-way merge
scenarios in practice.
