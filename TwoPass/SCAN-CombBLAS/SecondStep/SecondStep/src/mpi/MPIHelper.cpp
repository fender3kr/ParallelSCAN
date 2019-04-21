/*
 * MPIHelper.cpp
 *
 *  Created on: Oct 16, 2017
 *  Author: Seokyong Hong
 */

#include "MPIHelper.h"

namespace phantom {

MPIHelper::MPIHelper(int &argc, char **&argv) {
	MPI::Init(argc, argv);
	processes = MPI::COMM_WORLD.Get_size();
	rank = MPI::COMM_WORLD.Get_rank();
}

MPIHelper::~MPIHelper() {
	MPI::Finalize();
}

int MPIHelper::getProcesses(void) const {
	return processes;
}

int MPIHelper::getRank(void) const {
	return rank;
}

bool MPIHelper::isMaster(void) const {
	return rank == 0;
}

int MPIHelper::getMaster(void) const {
	return 0;
}

double MPIHelper::getWallTime(void) const {
	return MPI::Wtime();
}

} /* namespace phantom */
