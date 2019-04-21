/*
 * BinaryFormatter.cpp
 *
 *  Created on: Oct 13, 2017
 *  Author: Seokyong Hong
 */

#include "BinaryFormatter.h"

namespace phantom {

BinaryFormatter::BinaryFormatter(uint64_t numberOfVertices, uint64_t numberOfEdges) {
	this -> numberOfVertices = numberOfVertices;
	this -> numberOfEdges = numberOfEdges;
	header = new uint8_t[headerBytes];
	entries = NULL;
	entryBytes = 0;
	generateHeader();
}

BinaryFormatter::~BinaryFormatter() {
	if(header)
		delete []header;
	if(entries)
		delete []entries;
}

void BinaryFormatter::generateHeader(void) {
	int offset = 0;
	memcpy(header + offset, HEADER.c_str(), HEADER.length());
	offset += HEADER.length();
	memcpy(header + offset, &VERSION, sizeof(VERSION));
	offset += sizeof(VERSION);
	memcpy(header + offset, &OBJECT_SIZE, sizeof(OBJECT_SIZE));
	offset += sizeof(OBJECT_SIZE);
	memcpy(header + offset, &FORMAT, sizeof(FORMAT));
	offset += sizeof(FORMAT);
	memcpy(header + offset, &numberOfVertices, sizeof(numberOfVertices));
	offset += sizeof(uint64_t);
	memcpy(header + offset, &numberOfVertices, sizeof(numberOfVertices));
	offset += sizeof(numberOfVertices);
	memcpy(header + offset, &numberOfEdges, sizeof(numberOfEdges));
}

uint8_t *BinaryFormatter::getHeader(void) {
	return header;
}

uint32_t BinaryFormatter::getHeaderLength(void) const {
	return headerBytes;
}

uint32_t BinaryFormatter::getLineWidth(void) const {
	return sizeof(uint64_t) * 2 + sizeof(double);
}

uint8_t *BinaryFormatter::getEntries(uint64_t *sources, uint64_t *targets, uint64_t *counts, uint64_t length) {
	if(entries)
		delete []entries;

	entryBytes = getLineWidth() * length;
	entries = new uint8_t[entryBytes];
	for(uint64_t position = 0UL;position < length;position++) {
		*(((uint64_t *)entries) + position * 3) = *(sources + position) - 1;
		*(((uint64_t *)entries) + position * 3 + 1) = *(targets + position) - 1;
		*(((double *)entries) + position * 3 + 2) = (double)(*(counts + position) + 2.0);
	}
	return entries;
}

uint64_t BinaryFormatter::getEntryLength(void) const {
	return entryBytes;
}

} /* namespace phantom */
