/*
 * GraphReader.h
 *
 *  Created on: Oct 3, 2017
 *  Author: Seokyong Hong
 */

#ifndef IO_GRAPHREADER_H_
#define IO_GRAPHREADER_H_

#include <memory>
#include <fstream>
#include <iostream>
#include "GraphIOException.h"
#include "../mpi/MPIHelper.h"
#include "../util/Parameter.h"

using namespace std;

namespace phantom {

class GraphReader {
private:
	ifstream stream;
	uint64_t source;
	uint64_t target;
	bool isGood;

	void readHeader(void);
	void readNext(void);
public:
	GraphReader(string inputPath);
	virtual ~GraphReader();

	bool hasNext(void) const;
	void read(uint64_t &source, uint64_t &target);
};

} /* namespace phantom */

#endif /* IO_GRAPHREADER_H_ */
