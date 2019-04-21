/*
 * MTXFormatter.cpp
 *
 *  Created on: Oct 11, 2017
 *  Author: Seokyong Hong
 */

#include "MTXFormatter.h"

MTXFormatter::MTXFormatter(uint64_t numberOfVertices, uint64_t numberOfEdges) {
	this -> numberOfVertices = numberOfVertices;
	this -> numberOfEdges = numberOfEdges;
	ostringstream converter;
	converter << numberOfVertices;
	this -> entryWidth = converter.str().size();
	generateHeader();
}

MTXFormatter::~MTXFormatter() {
}

void MTXFormatter::generateHeader(void) {
	ostringstream hstream;
	hstream << HEADER;
	hstream << setw(entryWidth) << numberOfVertices << '\t';
	hstream << setw(entryWidth) << numberOfVertices << '\t';
	hstream << setw(entryWidth) << numberOfEdges << '\n';
	header = hstream.str();
}

uint8_t *MTXFormatter::getHeader(void) {
	return (uint8_t *)header.c_str();
}

uint32_t MTXFormatter::getHeaderLength(void) const {
	return header.length();
}

uint32_t MTXFormatter::getLineWidth(void) const {
	return (entryWidth + 1) * 3;
}

uint8_t *MTXFormatter::getEntries(uint64_t *sources, uint64_t *targets, uint64_t *counts, uint64_t length) {
	ostringstream estream;
	for(uint32_t position = 0;position < length;position++) {
		estream << setw(entryWidth) << *(sources + position) << '\t';
		estream << setw(entryWidth) << *(targets + position) << '\t';
		estream << setw(entryWidth) << *(counts + position) + 2 << '\n';
	}
	entries = estream.str();
	return (uint8_t *)entries.c_str();
}

uint64_t MTXFormatter::getEntryLength(void) const {
	return entries.length();
}
