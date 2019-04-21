/*
 * Parameter.h
 *
 *  Created on: Oct 3, 2017
 *  Author: Seokyong Hong
 */

#ifndef UTIL_PARAMETER_H_
#define UTIL_PARAMETER_H_

#include <omp.h>
#include <iostream>

using namespace std;

namespace phantom {

class Parameter {
private:
	string inputPath;
	string outputPath;
	int32_t numberOfVertices;
	int32_t numberOfEdges;
	int32_t numberOfColumns;
	int32_t numberOfRows;
	int32_t numberOfThreads;

	Parameter(string inputPath, string outputPath, int32_t numberOfVertices, int32_t numberOfEdges, int32_t numberOfRows, int32_t numberOfColumns, int32_t numberOfThreads);

	static Parameter *parameter;
public:
	virtual ~Parameter();

	string getInputPath(void) const;
	string getOutputPath(void) const;
	int32_t getNumberOfVertices(void) const;
	int32_t getNumberOfEdges(void) const;
	int32_t getNumberOfColumns(void) const;
	int32_t getNumberOfRows(void) const;
	int32_t getNumberOfThreads(void) const;

	static Parameter *getParameter(int &argc, char **&argv);
	static void printUsage(void);
};

} /* namespace phantom */

#endif /* UTIL_PARAMETER_H_ */
