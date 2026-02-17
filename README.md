

## Exercise 1: Ring Communication
**Objective:** Implement a ring topology where data passes sequentially through all processes.

* **Logic:** Process 0 initializes a value ($100$), adds its rank, and sends it to Process 1. Each subsequent process adds its rank and forwards it. The last process sends the final sum back to Process 0.
* **Key Functions:** `MPI_Send`, `MPI_Recv`, Modulo operator for wrapping.


## Exercise 2: Parallel Array Sum
**Objective:** Compute the sum and average of an array of 100 elements in parallel.

* **Logic:** Process 0 creates an array (1-100) and distributes equal chunks to all processes. Each process calculates a local sum, and `MPI_Reduce` aggregates them into a global sum.
* **Key Functions:** `MPI_Scatter`, `MPI_Reduce` (with `MPI_SUM`).


## Exercise 3: Finding Maximum and Minimum
**Objective:** Identify global max/min values and the ranks of the processes that generated them.

* **Logic:** Each process generates 10 random numbers. Using custom structs, the program tracks both the value and the rank to identify the source of the extrema.
* **Key Functions:** `MPI_Reduce` (with `MPI_MAXLOC` and `MPI_MINLOC`).


## Exercise 4: Parallel Dot Product
**Objective:** Compute the dot product of two 8-element vectors in parallel.

* **Logic:** Two vectors are scattered across the available processes. Each process computes a partial product of its assigned segments, which are then summed at the root.
* **Expected Result:** $120$
* **Key Functions:** `MPI_Scatter`, `MPI_Reduce`.


**To compile any of the exercises (e.g., Exercise 1):**
```bash
mpicc ring_comm.c -o ring_comm
