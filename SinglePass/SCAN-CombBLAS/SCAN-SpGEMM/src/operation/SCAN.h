/*
 * SCAN.h
 *
 *  Created on: Oct 16, 2017
 *  Author: Seokyong Hong
 */

#ifndef SRC_OPERATION_SCAN_H_
#define SRC_OPERATION_SCAN_H_

#include <fstream>
#include <iostream>
#include "Types.h"
#include "Functions.h"
#include "../mpi/MPIHelper.h"
#include "../util/Parameter.h"
#include "../util/Statistics.h"

using namespace std;
using namespace phantom;

namespace phantom {

class SCAN {
private:
	MPIHelper *helper;
	shared_ptr<CommGrid> world;
	Statistics statistics;
public:
	SCAN(MPIHelper *helper);
	virtual ~SCAN();

	void detect(Parameter *parameter);
	Statistics getStatistics(void) const;
};

} /* namespace phantom */

#endif /* SRC_OPERATION_SCAN_H_ */
