/*
 * MPIHelper.h
 *
 *  Created on: Oct 16, 2017
 *  Author: Seokyong Hong
 */

#ifndef SRC_MPI_MPIHELPER_H_
#define SRC_MPI_MPIHELPER_H_

#include <mpi.h>
#include <iostream>

using namespace std;

namespace phantom {

class MPIHelper {
private:
	int processes;
	int rank;
public:
	MPIHelper(int &argc, char **&argv);
	virtual ~MPIHelper();

	int getProcesses(void) const;
	int getRank(void) const;
	bool isMaster(void) const;
	int getMaster(void) const;
	double getWallTime(void) const;
};

} /* namespace phantom */

#endif /* SRC_MPI_MPIHELPER_H_ */
