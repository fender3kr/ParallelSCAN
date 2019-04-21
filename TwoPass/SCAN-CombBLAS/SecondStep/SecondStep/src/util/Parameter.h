/*
 * Parameter.h
 *
 *  Created on: Oct 16, 2017
 *  Author: Seokyong Hong
 */

#ifndef SRC_UTIL_PARAMETER_H_
#define SRC_UTIL_PARAMETER_H_

#include <cstdint>
#include <iostream>

using namespace std;

namespace phantom {

class Parameter {
private:
	string inputPath;
	string outputPath;
	uint32_t mu;
	double epsilon;

	Parameter(string inputPath, string outputPath, uint32_t mu, double epsilon);

	static Parameter *parameter;
public:
	virtual ~Parameter();

	string getInputPath(void) const;
	string getOutputPath(void) const;
	uint32_t getMu(void) const;
	double getEpsilon(void) const;

	static Parameter *getParameter(int &argc, char **&argv);
	static void printUsage(void);
};

} /* namespace phantom */

#endif /* SRC_UTIL_PARAMETER_H_ */
