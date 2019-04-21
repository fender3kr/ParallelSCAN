/*
 * BinaryFormatter.h
 *
 *  Created on: Oct 13, 2017
 *  Author: Seokyong Hong
 */

#ifndef MTX_BINARYFORMATTER_H_
#define MTX_BINARYFORMATTER_H_

#include <cstdint>
#include <cstring>
#include <iostream>

using namespace std;

namespace phantom {

class BinaryFormatter {
private:
	const string HEADER = "HKDT";
	const uint64_t VERSION = 1;
	const uint64_t OBJECT_SIZE = sizeof(uint64_t) * 3;
	const uint64_t FORMAT = 0;
	const uint32_t headerBytes = 4 + sizeof(uint64_t) * 6;

	uint8_t *entries;
	uint8_t *header;
	uint64_t numberOfVertices;
	uint64_t numberOfEdges;
	uint64_t entryBytes;

	void generateHeader(void);
public:
	BinaryFormatter(uint64_t numberOfVertices, uint64_t numberOfEdges);
	virtual ~BinaryFormatter();

	uint8_t *getHeader(void);
	uint32_t getHeaderLength(void) const;
	uint32_t getLineWidth(void) const;
	uint8_t *getEntries(uint64_t *sources, uint64_t *targets, uint64_t *counts, uint64_t length);
	uint64_t getEntryLength(void) const;
};

} /* namespace phantom */

#endif /* MTX_BINARYFORMATTER_H_ */
