# Bloom Filter, in C, with the receipts

A from-scratch Bloom filter in plain C — but the actual point of this project wasn't writing the filter, it was proving it. Alongside the implementation there's a full experimental suite that measures false-positive rates and benchmarks the filter against a hash table and a binary search tree across hundreds of thousands of insertions, to see whether the textbook math actually holds up in practice.

Spoiler: it does, closely enough that the recorded optimal-k curve nearly overlaps the theoretical one (see below).

## How it works

A Bloom filter trades certainty for space: it can tell you "definitely not in the set" for free, and "probably in the set" for almost nothing. Every insert sets `k` bits in a shared bit array; every lookup checks the same `k` positions and answers `no` if any of them is unset, `maybe` otherwise — false positives are possible, false negatives never are.

Rather than implementing `k` independent hash functions, `hash()` (`filter.c`) uses one rolling multiplicative hash reseeded with a random per-function "weight" for each of the `k` slots — simpler than maintaining a family of real hash functions, and empirically good enough that the false-positive curves below track theory almost exactly.

## Try it

```sh
make                 # builds bin/bloom_filter
./bin/bloom_filter    # interactive menu: create a filter, insert, query, run the stats suite
```

<div align="center">
  <img src="doc/command.png" alt="Menu Commands">
</div>

## Does the theory hold up?

### Filter size (m) vs. false positives
Fixing `k` and growing the bit array `m` should push false positives down. It does:

<div align="center">
  <img src="doc/m_variable_k_fixed.png" alt="False Positives with Fixed k">
</div>

### Hash function count (k) vs. false positives
Fixing `m` and cranking up `k` helps at first, then backfires — each extra hash function sets more bits per insert, so the array saturates faster and false positives climb back up:

<div align="center">
  <img src="doc/m_fixed_k_variable.png" alt="False Positives with Fixed m">
</div>

### The optimal k formula, checked against reality
Theory says the false-positive-minimizing `k` is `k ≈ (m/n)·ln(2)`. Plotting the empirically-measured best `k` against this formula:

<div align="center">
  <img src="doc/recorded_theoretical_k.png" alt="Theoretical vs Recorded Optimal k" width="400">
</div>

### Space and time, vs. a hash table and a BST
Benchmarked head-to-head with a custom chained hash table and BST up to 400,000 insertions: the Bloom filter's time stays close to the hash table's (both effectively O(k)/O(1)), while its memory footprint is a small fraction of either — no keys are ever stored, only bits.

<div align="center">
  <img src="doc/time_&_space.png" alt="Time and Space Comparison">
</div>

The full write-up (French) is in [`doc/rapport.pdf`](doc/rapport.pdf).

## Project layout

- `src/` / `include/` — the filter itself (`filter.c`), the underlying bit array, the comparison hash table and BST, the benchmarking harness, and the interactive menu.
- `data/` — word banks used to generate test keys.
- `stats/` — raw output from the false-positive experiments.
- `doc/` — the report and the charts above.
