# Algorithmic Efficiency Comparison Metrics

## Raw Execution Times

### Run 1
- Naive algorithm time: 0.861000 seconds
- Single-pass algorithm time: 0.000000 seconds

### Run 2
- Naive algorithm time: 0.931000 seconds
- Single-pass algorithm time: 0.000000 seconds

### Run 3
- Naive algorithm time: 0.881000 seconds
- Single-pass algorithm time: 0.000000 seconds

---

## Analysis and Averages

- **Naive Algorithm Average Time:** 0.891000 seconds
- **Single-pass Algorithm Average Time:** 0.000000 seconds (Below measurable threshold of clock())

### Relative Difference
The Naive implementation ($O(N^2)$) takes an average of 0.891 seconds, while the Single-pass implementation ($O(N)$) executes instantly (0.000000 seconds). 

This demonstrates a massive efficiency gap where the $O(N^2)$ approach requires significantly more CPU cycles, making it less sustainable and vastly more energy-intensive than the optimal $O(N)$ solution.
