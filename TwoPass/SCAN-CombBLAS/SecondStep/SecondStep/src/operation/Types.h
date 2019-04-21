/*
 * Types.h
 *
 *  Created on: Oct 16, 2017
 *  Author: Seokyong Hong
 */

#ifndef SRC_OPERATION_TYPES_H_
#define SRC_OPERATION_TYPES_H_

#include "CombBLAS.h"

#define DMat(M)	M
#define SMat(M)	M
#define DVec(V)	V
#define SVec(V)	V

template <class T>
class Dist {
public:
	typedef SpDCCols<uint64_t, T> DCCols;
	typedef SpParMat<uint64_t, T, DCCols> MPI_DCCols;
	typedef FullyDistVec<uint64_t, T> MPI_DenseVec;
	typedef DenseParMat<uint64_t, T> MPI_DenseMat;
	typedef FullyDistSpVec<uint64_t, T> MPI_SparseVec;
};

#endif /* SRC_OPERATION_TYPES_H_ */
