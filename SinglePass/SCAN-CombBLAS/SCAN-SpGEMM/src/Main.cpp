/*
 * Main.cpp
 *
 *  Created on: Oct 16, 2017
 *  Author: Seokyong Hong
 */
#include <iostream>
#include "mpi/MPIHelper.h"
#include "util/Parameter.h"
#include "operation/SCAN.h"
#include "util/Statistics.h"

using namespace std;
using namespace phantom;

int main(int argc, char *argv[]) {
	auto parameter = Parameter::getParameter(argc, argv);
	MPIHelper *helper = new MPIHelper(argc, argv);
	SCAN *operation = new SCAN(helper);

	if(parameter) {
		operation -> detect(parameter);
		Statistics statistics = operation -> getStatistics();
		if(helper -> isMaster())
			statistics.print();
	}
	else {
		if(helper -> isMaster())
			Parameter::printUsage();
	}

	delete operation;
	delete helper;
	return 0;
}



