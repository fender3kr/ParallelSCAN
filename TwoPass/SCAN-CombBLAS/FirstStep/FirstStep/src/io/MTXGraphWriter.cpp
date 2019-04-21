/*
 * MTXGraphWriter.cpp
 *
 *  Created on: Oct 6, 2017
 *  Author: Seokyong Hong
 */

#include "MTXGraphWriter.h"

namespace phantom {

MTXGraphWriter::MTXGraphWriter(string outputPath) {
	stream.open(outputPath.c_str(), ios::out | ios::trunc);
}

MTXGraphWriter::~MTXGraphWriter() {
	if(stream.is_open())
		stream.flush();
		stream.close();
}

void MTXGraphWriter::writeHeader(const uint32_t vertices, const uint32_t edges) {
	if(stream.good()) {
		stream << "%%MatrixMarket matrix coordinate integer symmetric" << endl << "%" << endl;
		stream << vertices << "\t" << vertices << "\t" << edges << endl;
	}
	else
		throw GraphIOException("Cannot write header.");
}

void MTXGraphWriter::write(Parameter *parameter, uint32_t *sources, uint32_t *targets, uint32_t *counts) {
	if(!parameter || !sources || !targets || !counts)
		throw GraphIOException("Parameters are incorrect.");

	writeHeader(parameter -> getNumberOfVertices(), parameter -> getNumberOfEdges());
	for(int32_t position = 0;position < parameter -> getNumberOfEdges();position++) {
		stream << *(sources + position) << "\t" << *(targets + position) << "\t" << *(counts + position) << endl;
	}
}

} /* namespace phantom */
