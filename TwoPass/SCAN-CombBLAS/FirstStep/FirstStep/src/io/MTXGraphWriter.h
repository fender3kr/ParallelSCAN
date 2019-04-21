/*
 * MTXGraphWriter.h
 *
 *  Created on: Oct 6, 2017
 *  Author: Seokyong Hong
 */

#ifndef IO_MTXGRAPHWRITER_H_
#define IO_MTXGRAPHWRITER_H_

#include <fstream>
#include <iostream>
#include "GraphIOException.h"
#include "../util/Parameter.h"

using namespace std;

namespace phantom {

class MTXGraphWriter {
private:
	ofstream stream;

	void writeHeader(const uint32_t vertices, const uint32_t edges);
public:
	MTXGraphWriter(string outputPath);
	virtual ~MTXGraphWriter();

	void write(Parameter *parameter, uint32_t *sources, uint32_t *targets, uint32_t *counts);
};

} /* namespace phantom */

#endif /* IO_MTXGRAPHWRITER_H_ */
