# ParallelSCAN
Parallel Implementations of SCAN (Structural Community Detection Algorithm)

ParallelSCAN is parallel implementations of the SCAN algorithm:

http://www1.se.cuhk.edu.hk/~hcheng/seg5010/slides/p824-xu.pdf

This parallel algorithm is built upon matrix as a graph data model and linear albebraic operations.
As its base framework for distributed graph management and analysis, CombBLAS is used:

https://people.eecs.berkeley.edu/~aydin/CombBLAS/html/

The algorithm along with the framework leverages hybrid parallel programming (MPI and OpenMP). There are two implementations of the algorithm:

(1) Single-pass Parallel SCAN: it solely relies on the CombBLAS framework. In this approach, structural similarity computations are done with a matrix-matrix multiplication. 
(2) Two-pass Parallel SCAN: the matrix-matrix multiplication operation provided in the CombBLAS framework consumes a lot of memory space and it easily results in failure due to memory error. To avoid the operation, this two-pass algorithm was developed. Structural similarity computation is moved into the first step and computed values are materialized as edge edges. This allows to evaluate the algorithm with varying parameter settings. Instead of performing matrix-matrix multiplicatiion, this computes similarity values by intersecting matrix rows.
