/*
 * Parameter.cpp
 *
 *  Created on: Oct 3, 2017
 *  Author: Seokyong Hong
 */

#include "Parameter.h"

namespace phantom {

Parameter *Parameter::parameter = NULL;

Parameter::Parameter(string inputPath, string outputPath, int32_t numberOfVertices, int32_t numberOfEdges, int32_t numberOfRows, int32_t numberOfColumns, int32_t numberOfThreads) : inputPath(inputPath), outputPath(outputPath), numberOfVertices(numberOfVertices), numberOfEdges(numberOfEdges), numberOfRows(numberOfRows), numberOfColumns(numberOfColumns), numberOfThreads(numberOfThreads) {
}

Parameter::~Parameter() {
}

string Parameter::getInputPath(void) const {
	return inputPath;
}

string Parameter::getOutputPath(void) const {
	return outputPath;
}

int32_t Parameter::getNumberOfVertices(void) const {
	return numberOfVertices;
}

int32_t Parameter::getNumberOfEdges(void) const {
	return numberOfEdges;
}

int32_t Parameter::getNumberOfRows(void) const {
	return numberOfRows;
}

int32_t Parameter::getNumberOfColumns(void) const {
	return numberOfColumns;
}

int32_t Parameter::getNumberOfThreads(void) const {
	return numberOfThreads;
}

Parameter *Parameter::getParameter(int &argc, char **&argv) {
	if(argc != 8)
		return NULL;

	string inputPath = argv[1];
	string outputPath = argv[2];
	int32_t numberOfVertices = atoi(argv[3]);
	int32_t numberOfEdges = atoi(argv[4]);
	int32_t numberOfRows = atoi(argv[5]);
	int32_t numberOfColumns = atoi(argv[6]);
	int32_t numberOfThreads = atoi(argv[7]);

	if(numberOfVertices < 1 || numberOfEdges < 1 || numberOfRows < 1 || numberOfColumns < 1)
		return NULL;

	if(numberOfThreads < 0)
		numberOfThreads = 1;

	//if(numberOfThreads > omp_get_max_threads())
	//	numberOfThreads = omp_get_max_threads();

	if(!parameter)
		parameter = new Parameter(inputPath, outputPath, numberOfVertices, numberOfEdges, numberOfRows, numberOfColumns, numberOfThreads);

	return parameter;
}

void Parameter::printUsage(void) {
	cout << "mpirun -np <#processes: must be #rowProcesses X #colProcesses> <input path> <output path> <size: #vertices> <size: #edges> <#rowProcesses> <#colProcesses> <#threads>" << endl;
}

} /* namespace phantom */
