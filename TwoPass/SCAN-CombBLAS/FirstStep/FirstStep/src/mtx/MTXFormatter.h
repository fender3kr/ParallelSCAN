/*
 * MTXFormatter.h
 *
 *  Created on: Oct 11, 2017
 *  Author: Seokyong Hong
 */

#ifndef IO_MTXFORMATTER_H_
#define IO_MTXFORMATTER_H_

#include <iomanip>
#include <cstdint>
#include <cstring>
#include <sstream>
#include <iostream>

using namespace std;

class MTXFormatter {
private:
	const string HEADER = "%%MatrixMarket matrix coordinate integer symmetric\n%\n";

	string entries;
	string header;
	uint64_t entryWidth;
	uint64_t numberOfVertices;
	uint64_t numberOfEdges;

	void generateHeader(void);
public:
	MTXFormatter(uint64_t numberOfVertices, uint64_t numberOfEdges);
	virtual ~MTXFormatter();

	uint8_t *getHeader(void);
	uint32_t getHeaderLength(void) const;
	uint32_t getLineWidth(void) const;
	uint8_t *getEntries(uint64_t *sources, uint64_t *targets, uint64_t *counts, uint64_t length);
	uint64_t getEntryLength(void) const;
};

#endif /* IO_MTXFORMATTER_H_ */
