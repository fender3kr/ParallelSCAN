/*
 * GraphReader.cpp
 *
 *  Created on: Oct 3, 2017
 *  Author: Seokyong Hong
 */

#include "GraphReader.h"

namespace phantom {

GraphReader::GraphReader(string inputPath) {
	isGood = false;
	stream.open(inputPath.c_str());
	if(stream.fail())
		throw GraphIOException("Cannot open input file.");

	readHeader();
	readNext();
}

GraphReader::~GraphReader() {
	stream.close();
}

void GraphReader::readHeader(void) {
	if(stream.good()) {
		string line;
		for(int index = 0;index < 4;index++)
			getline(stream, line);
	}
}

void GraphReader::readNext(void) {
	try {
		stream >> source >> target;
	}
	catch(exception &e) {
		isGood = false;
		throw GraphIOException("Cannot read entries.");
	}

	isGood = stream.good();
}

bool GraphReader::hasNext(void) const {
	return isGood;
}

void GraphReader::read(uint64_t &source, uint64_t &target) {
	source = this -> source;
	target = this -> target;

	readNext();
}

} /* namespace phantom */
