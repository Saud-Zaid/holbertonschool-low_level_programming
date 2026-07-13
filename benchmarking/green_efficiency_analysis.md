# Green Tech Efficiency & Benchmarking Analysis

## Measurement Methodology
To establish a rigorous baseline and evaluate algorithmic impact on performance, measurements were conducted under controlled conditions on a single target machine environment. Execution timing was captured using the standard C library `<time.h>` and the `clock()` function. This approach measures the CPU time consumed by the program, eliminating external wall-clock noise. 

The boundaries for the multi-phase instrumentation were defined by capturing the `clock_t` ticks immediately prior to a function call and immediately following its termination. The elapsed time was then computed by dividing the delta of ticks by `CLOCKS_PER_SEC` to produce a high-precision floating-point value in seconds (`%.6f`). For the global baseline (`TOTAL`), the clock was initialized at the entry point of the `main` function and captured right before output delivery, ensuring all sub-phases were contained inside the global boundary uniformly.

## Observed Performance Differences
The empirical data collected from the controlled experiments revealed substantial gaps between the implementations. In the baseline loop test, running $100,000,000$ iterations demonstrated low but noticeable timing variability across three consecutive runs ($0.106000$s, $0.123000$s, and $0.136000$s). This slight fluctuation highlights background operating system scheduling and resource allocation overhead.

The most dramatic performance delta appeared in the algorithmic comparison lab over an array of $50,000$ integers. The Naive nested-loop implementation ($O(N^2)$) required an average execution time of $0.891000$ seconds. Conversely, the optimal Single-pass linear implementation ($O(N)$) executed instantaneously, recording $0.000000$ seconds across all iterations because its execution window fell below the measurable threshold of the standard system clock. This means the quadratic approach is orders of magnitude slower, wasting substantial compute time on identical datasets.

## Relation Between Runtime and Energy Consumption
Software runtime serves as a direct engineering proxy for hardware energy consumption. When a program executes an inefficient algorithm like `count_even_naive`, the CPU cores must remain in a high-power active state ($C_0$ state) for a longer duration. In this experiment, the $O(N^2)$ algorithm forced the processor to compute instructions for almost a full second ($0.891000$s), drawing steady electric current to drive the logic gates.

In contrast, the $O(N)$ single-pass execution allows the CPU to complete the task instantly and immediately transition back into low-power states or handle other concurrent threads. At data center scale, multiplying this 0.89-second delay by millions of daily transactions scales up electricity usage linearly, escalating the infrastructure's carbon footprint. Thus, reducing runtime through algorithmic design directly minimizes cumulative energy draw.

## Limitations of the Experiment
While the results clearly distinguish efficient code from inefficient code, the experimental setup presents clear limitations:
1. **Clock Resolution:** The `clock()` function lacks sub-microsecond precision on certain platforms, causing the optimal single-pass algorithm to register as $0.000000$ seconds, preventing a literal, exact mathematical ratio calculation.
2. **Proxy Metric:** The experiment relies entirely on runtime as a proxy for power. It does not measure actual physical energy consumption in Watts, nor does it track real-time CPU core thermal dynamics or memory subsystem power draw.

## Practical Engineering Takeaway
The fundamental takeaway for a software engineer is that green computing starts at the architectural and algorithmic level, not through superficial patches. Writing optimal code ($O(N)$ over $O(N^2)$) is a powerful, proactive sustainability practice. Developers must integrate benchmarking loops early in development to discover latent computational bottlenecks before deploying code at scale.
