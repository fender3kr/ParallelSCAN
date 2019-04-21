/*
 ============================================================================
 Name        : SCAN-MPI.c
 Author      : Seokyong Hong
 Version     :
 Copyright   : 
 Description : Parallel SCAN Community Detection in MPI
 ============================================================================
 */
#include <memory>
#include <iostream>
#include "mpi/MPIHelper.h"
#include "util/Parameter.h"
#include "mpi/MPIConfException.h"
#include "graph/GraphProcessor.h"

using namespace std;
using namespace phantom;

int main(int argc, char *argv[]) {
	Parameter *parameter = Parameter::getParameter(argc, argv);
	MPIHelper *helper;

	if(!parameter) {
		Parameter::printUsage();
		return 0;
	}

	try {
		helper = new MPIHelper(argc, argv, parameter);
	}
	catch(MPIConfException &e) {
		if(parameter)
			delete parameter;
		return 0;
	}

	double t0 = helper -> getWallTime();
	if(parameter) {
		GraphProcessor processor(helper, parameter);
		processor.process();
	}
	else {
		if(helper -> isMaster())
			Parameter::printUsage();
	}

	if(helper -> isMaster())
		cout << "Execution Time: " << (helper -> getWallTime() - t0) << " seconds" << endl;

	if(parameter)
		delete parameter;

	helper -> finalize();
	return 0;
}

