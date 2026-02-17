**Q1: Molecular Dynamics Simulation**
Computation of N-body Lennard-Jones forces and total potential energy. This implementation addresses race conditions in force accumulation using atomic operations and optimizes load balancing for particle interactions.

**Q2: Smith-Waterman Alignment**
A parallel local DNA sequence alignment algorithm. It utilizes a wavefront (anti-diagonal) approach to overcome dynamic programming dependencies, allowing for concurrent scoring matrix calculations.

**Q3: 2D Heat Diffusion**
Simulation of thermal distribution across a metal plate using the finite difference method. It implements spatial loop parallelization, double-buffering to prevent race conditions, and reduction for heat accumulation.
