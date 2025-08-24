# C++ Time Complexity Examples

This collection demonstrates common time complexities with small, runnable C++ programs.

Each program prints what it does, the input size, and the elapsed time. Use these to build intuition for how runtime scales as `n` changes.

## Contents
- O(1): Constant-time access — `src/constant_O1.cpp`
- O(log n): Binary search — `src/log_n_binary_search.cpp`
- O(n): Sum of elements — `src/n_sum.cpp`
- O(n log n): Merge sort (std::sort) — `src/nlogn_merge_sort.cpp`
- O(n^2): Bubble sort — `src/n2_bubble_sort.cpp`
- O(2^n): Naive recursive Fibonacci — `src/exp_2n_fibonacci.cpp`
- O(n!): Enumerating permutations — `src/factorial_permutations.cpp`

## Complexity ranking (most to least efficient)

| Rank | Time Complexity | Name            | Typical example                 | Growth intuition                                 |
|-----:|------------------|-----------------|---------------------------------|--------------------------------------------------|
|    1 | O(1)             | Constant        | Array access                    | Flat; doesn’t grow with n                        |
|    2 | O(log n)         | Logarithmic     | Binary search                   | Very slow growth                                 |
|    3 | O(n)             | Linear          | Summing array                   | Doubles when n doubles                           |
|    4 | O(n log n)       | Linearithmic    | Efficient sorts (std::sort)     | Slightly super-linear                            |
|    5 | O(n^2)           | Quadratic       | Bubble/selection/insertion sort | Grows quickly; small n only                      |
|    6 | O(2^n)           | Exponential     | Naive Fibonacci recursion       | Explodes; only tiny n feasible                   |
|    7 | O(n!)            | Factorial       | Enumerating permutations        | Even worse than exponential; minuscule n only    |

Notes:
- “Most efficient” refers to growth with respect to input size n, not constant factors.
- Real performance also depends on constants, memory/cache behavior, and implementation.

## Build
Requires g++ (C++17).

- Build all:
  make
- Clean:
  make clean

Binaries are placed in `bin/`:

- `bin/constant_O1`
- `bin/log_n_binary_search`
- `bin/n_sum`
- `bin/nlogn_merge_sort`
- `bin/n2_bubble_sort`
- `bin/exp_2n_fibonacci`
- `bin/factorial_permutations`

## Run
Each program accepts an optional `n` argument. Defaults try to be reasonable for a laptop.

Examples:

- Constant (independent of n):
  ./bin/constant_O1 1000000
- Logarithmic (vector of size n):
  ./bin/log_n_binary_search 1000000
- Linear:
  ./bin/n_sum 10000000
- N log N sort:
  ./bin/nlogn_merge_sort 2000000
- Quadratic (keep n small):
  ./bin/n2_bubble_sort 2000
- Exponential 2^n (keep n modest):
  ./bin/exp_2n_fibonacci 30
- Factorial n! (keep n small):
  ./bin/factorial_permutations 9

## Notes
- Timings vary with hardware, compiler flags, and randomness.
- For very fast operations (like O(1)), the program repeats the operation many times to get a measurable time. The repetitions are a constant factor; the complexity with respect to `n` remains O(1).
- For expensive algorithms (O(n^2), O(2^n), O(n!)), start with small `n` and increase gradually.
