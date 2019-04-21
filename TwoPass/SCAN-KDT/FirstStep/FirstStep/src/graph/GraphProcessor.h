/*
 * GraphProcessor.h
 *
 *  Created on: Oct 3, 2017
 *  Author: Seokyong Hong
 */

#ifndef GRAPH_GRAPHPROCESSOR_H_
#define GRAPH_GRAPHPROCESSOR_H_

#include <omp.h>
#include <math.h>
#include <vector>
#include "../mpi/MPIHelper.h"
#include "../roar/roaring.hh"
#include "../io/GraphReader.h"
#include "../io/MTXGraphWriter.h"
#include "../io/GraphIOException.h"

using namespace std;

namespace phantom {

class GraphProcessor {
private:
	MPIHelper *helper;
	Parameter *parameter;
	vector<Roaring64Map> *bitsets;
	uint64_t *sources;
	uint64_t *targets;
	uint64_t fromColumn;
	uint64_t toColumn;
	uint64_t fromRow;
	uint64_t toRow;
	uint64_t edges;
public:
	GraphProcessor(MPIHelper *helper, Parameter *parameter);
	virtual ~GraphProcessor();

	void process(void);
};

} /* namespace phantom */

#endif /* GRAPH_GRAPHPROCESSOR_H_ */
