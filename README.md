# ParallelSCAN
<H3>Parallel Implementations of SCAN (Structural Community Detection Algorithm)</H3>

<H4>Description</H4>
ParallelSCAN is parallel implementations of <a href="http://www1.se.cuhk.edu.hk/~hcheng/seg5010/slides/p824-xu.pdf">the SCAN algorithm</a>. This parallel algorithm is built upon matrix as a graph data model and linear albebraic operations.
As its base framework for distributed graph management and analysis, <a href="https://people.eecs.berkeley.edu/~aydin/CombBLAS/html/">CombBLAS</a> is used. The algorithm along with the framework leverages hybrid parallel programming (MPI and OpenMP). There are two implementations of the algorithm:

(1) <B>Single-pass Parallel SCAN</B>: it solely relies on the CombBLAS framework. In this approach, structural similarity computations are done with a matrix-matrix multiplication. <BR>
(2) <B>Two-pass Parallel SCAN</B>: the matrix-matrix multiplication operation provided in the CombBLAS framework consumes a lot of memory space and it easily results in failure due to memory error. To avoid the operation, this two-pass algorithm was developed. Structural similarity computation is moved into the first step and computed values are materialized as edge edges. This allows to evaluate the algorithm with varying parameter settings. Instead of performing matrix-matrix multiplicatiion, this computes similarity values by intersecting matrix rows. The first part of this approach internally uses <a href="https://roaringbitmap.org/">roaring bitmap library</a> to represent graph partitions in memory.

A Python version of CombBLAS is also available and it is called <a href="kdt.sourceforge.net/">KDT (Knowledge Discovery Toolbox)</a>. This is a Python wrapper that allows data scientists to easily use the features of CombBLAS. The parallel SCAN algorithm was also implemented in Python over KDT.

<H4>Source Tree</H4>

<H4>Requirements</H4>
<ul>
  <li>MPI (Open MPI, Intel MPI, MPICH)</li>
  <li><a href="https://people.eecs.berkeley.edu/~aydin/CombBLAS/html/">CombBLAS 1.6.0</a></li>
  <li><a href="http://kdt.sourceforge.net/wiki/index.php/Download">KDT 0.3</a></li>
</ul>
