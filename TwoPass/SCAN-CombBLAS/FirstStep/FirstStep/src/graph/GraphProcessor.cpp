/*
 * GraphProcessor.cpp
 *
 *  Created on: Oct 3, 2017
 *  Author: Seokyong Hong
 */

#include "GraphProcessor.h"

namespace phantom {

GraphProcessor::GraphProcessor(MPIHelper *helper, Parameter *parameter) : helper(helper), parameter(parameter) {
	uint64_t vertices = (uint64_t)ceil((double)parameter -> getNumberOfVertices() / (double)parameter -> getNumberOfColumns());
	uint64_t gap = vertices * parameter -> getNumberOfColumns() - parameter -> getNumberOfVertices();
	//fromColumn = helper -> getRankInRow() * vertices + 1;
	//toColumn = (parameter -> getNumberOfColumns() - helper -> getRankInRow() != 1) ? (helper -> getRankInRow() + 1) * vertices : (helper -> getRankInRow() + 1) * vertices - gap;
	fromColumn = helper -> getRowRank() * vertices + 1;
	toColumn = (parameter -> getNumberOfColumns() - helper -> getRowRank() != 1) ? (helper -> getRowRank() + 1) * vertices : (helper -> getRowRank() + 1) * vertices - gap;
	bitsets = new vector<Roaring64Map>(parameter -> getNumberOfVertices(), Roaring64Map());

	uint64_t edges = (uint64_t)ceil((double)parameter -> getNumberOfEdges() / (double)parameter -> getNumberOfRows());
	gap = edges * parameter -> getNumberOfRows() - parameter -> getNumberOfEdges();
	//fromRow = helper -> getRowRank() * edges;
	//toRow = (parameter -> getNumberOfRows() - helper -> getRowRank() != 1) ? (helper -> getRowRank() + 1) * edges - 1: (helper -> getRowRank() + 1) * edges - gap - 1;
	fromRow = helper -> getRankInRow() * edges;
	toRow = (parameter -> getNumberOfRows() - helper -> getRankInRow() != 1) ? (helper -> getRankInRow() + 1) * edges - 1: (helper -> getRankInRow() + 1) * edges - gap - 1;
	this -> edges = toRow - fromRow + 1;

	sources = new uint64_t[this -> edges];
	targets = new uint64_t[this -> edges];
}

GraphProcessor::~GraphProcessor() {
	if(bitsets)
		delete bitsets;
	if(sources)
		delete []sources;
	if(targets)
		delete []targets;
}

void GraphProcessor::process(void) {
	GraphReader reader(parameter -> getInputPath());
	uint64_t source, target;
	uint64_t edges = 0UL;
	uint64_t position = 0UL;

	double t0 = helper -> getWallTime();

	try {
		while(reader.hasNext()) {
			reader.read(source, target);

			if(source >= fromColumn and source <= toColumn)
				(*bitsets)[target - 1].add(source - fromColumn);
			if(target >= fromColumn and target <= toColumn)
				(*bitsets)[source - 1].add(target - fromColumn);

			if(edges >= fromRow and edges <= toRow) {
				sources[position] = source;
				targets[position++] = target;
			}
			edges++;
		}
	}
	catch(GraphIOException &e) {
		cerr << e.what() << endl;
		return;
	}

	if(helper -> isMaster()) 
		cout << "\tLoading Time: " << (helper -> getWallTime() - t0) << endl;
	
	uint64_t *counts = new uint64_t[this -> edges];

	double t1 = helper -> getWallTime();
	#pragma omp parallel for schedule(static) private(position) num_threads(parameter -> getNumberOfThreads())
	for(position = 0UL;position < this -> edges;position++)
		counts[position] = ((*bitsets)[sources[position] - 1UL] & (*bitsets)[targets[position] - 1UL]).cardinality();
	if(helper -> isMaster())
		cout << "\tIntersection Time: " << (helper -> getWallTime() - t1) << endl;

	double t2 = helper -> getWallTime();
	uint64_t *aggregatedCounts = new uint64_t[this -> edges];
	helper -> reduceSharedNeighbors(counts, aggregatedCounts, this -> edges);
	if(helper -> isMaster())
		cout << "\tReduction Time: " << (helper -> getWallTime() - t2) << " seconds" << endl;

	double t3 = helper -> getWallTime();
	helper -> storeGraph(parameter, sources, targets, aggregatedCounts, this -> edges, true);
	if(helper -> isMaster())
		cout << "\tStoring Time: " << (helper -> getWallTime() - t3) << " seconds" << endl;

	if(aggregatedCounts)
		delete []aggregatedCounts;

	if(counts)
		delete []counts;

	if(helper -> isMaster())
		cout << "Graph Processing Time: " << (helper -> getWallTime() - t0) << " seconds" << endl;
}

} /* namespace phantom */
