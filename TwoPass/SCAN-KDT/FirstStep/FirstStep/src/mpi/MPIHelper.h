/*
 * MPIHelper.h
 *
 *  Created on: Oct 3, 2017
 *      Author: phantom
 */

#ifndef MPI_MPIHELPER_H_
#define MPI_MPIHELPER_H_

#include <mpi.h>
#include <math.h>
#include <cstdint>
#include <iostream>
#include "MPIConfException.h"
#include "../util/Parameter.h"
#include "../mtx/MTXFormatter.h"
#include "../mtx/BinaryFormatter.h"

using namespace std;

namespace phantom {

class MPIHelper {
private:
	int processes;
	int rank;
	int rowRank;
	int rankInRow;
	int rows;
	int columns;

	MPI::Intracomm worldComm;
	MPI::Intracomm rowComm;

	void storeAsciiGraph(Parameter *parameter, uint64_t *sources, uint64_t *targets, uint64_t *counts, uint64_t edges) const;
	void storeBinaryGraph(Parameter *parameter, uint64_t *sources, uint64_t *targets, uint64_t *counts, uint64_t edges) const;
public:
	MPIHelper(int &argc, char **&argv, Parameter *parameter);
	virtual ~MPIHelper();

	int getProcesses(void) const;
	int getRank(void) const;
	int getRowRank(void) const;
	int getRankInRow(void) const;
	bool isMaster(void) const;
	bool isRowMaster(void) const;
	void reduceSharedNeighbors(uint64_t *counts, uint64_t *aggregatedCounts, int numberOfCounts) const;
	double getWallTime(void) const;
	void storeGraph(Parameter *parameter, uint64_t *sources, uint64_t *targets, uint64_t *counts, uint64_t edges, bool binary) const;
	void finalize(void) const;
};

} /* namespace phantom */

#endif /* MPI_MPIHELPER_H_ */
