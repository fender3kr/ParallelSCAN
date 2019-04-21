/*
 * Parameter.cpp
 *
 *  Created on: Oct 16, 2017
 *  Author: Seokyong Hong
 */

#include "Parameter.h"

namespace phantom {

Parameter *Parameter::parameter = NULL;

Parameter::Parameter(string inputPath, string outputPath, uint32_t mu, double epsilon) : inputPath(inputPath), outputPath(outputPath), mu(mu), epsilon(epsilon) {
}

Parameter::~Parameter() {
}

string Parameter::getInputPath(void) const {
	return inputPath;
}

string Parameter::getOutputPath(void) const {
	return outputPath;
}

uint32_t Parameter::getMu(void) const {
	return mu;
}

double Parameter::getEpsilon(void) const {
	return epsilon;
}

Parameter *Parameter::getParameter(int &argc, char **&argv) {
	if(argc != 5)
		return NULL;

	string inputPath = argv[1];
	string outputPath = argv[2];
	uint32_t mu = stoul(argv[3]);
	double epsilon = stod(argv[4]);

	if(epsilon <= 0.0)
		return NULL;

	if(!parameter)
		parameter = new Parameter(inputPath, outputPath, mu, epsilon);

	return parameter;
}

void Parameter::printUsage(void) {
	cout << "mpirun -np <#processes> <executable> <input path> <output path> <mu> <epsilon>" << endl;
}

} /* namespace phantom */
