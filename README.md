
## Assignment Tasks

### 1. DAXPY Loop Optimization
Implementation of the **Double-precision $A \cdot X + Y$** operation on vectors of size $2^{16}$.
* **Objective:** Compare execution time and speedup starting from a 2-thread baseline.
* **Analysis:** identification of the optimal thread count and the performance degradation point caused by synchronization overhead and hardware limitations.

### 2. Parallel Matrix Multiplication
Parallel implementation of $1000 \times 1000$ matrix multiplication using two distinct partitioning strategies:
* **1D Threading:** Work is partitioned by assigning entire rows to a single thread.
* **2D Threading:** Work is partitioned across nested loops to allow for finer-grained parallelization across the product array.

* **Objective:** Evaluation of cache locality and partitioning efficiency between 1D and 2D schemes.

### 3. Numerical Estimation of $\pi$
Approximating the value of $\pi$ using the rectangle rule to solve the integral:
$$\pi = \int_{0}^{1} \frac{4.0}{1+x^2} \,dx$$
* **Objective:** Implementation of thread cooperation where multiple threads calculate partial sums to arrive at a single global value.
* **Focus:** Understanding data races and the importance of reduction operations in parallel computing.

