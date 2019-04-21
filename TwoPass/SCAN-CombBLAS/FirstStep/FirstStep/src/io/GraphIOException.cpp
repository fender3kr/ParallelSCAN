/*
 * GraphIOException.cpp
 *
 *  Created on: Oct 3, 2017
 *  Author: Seokyong Hong
 */

#include "GraphIOException.h"

namespace phantom {

GraphIOException::GraphIOException(string message) : message(message.c_str()) {
}

GraphIOException::~GraphIOException() {
}

const char *GraphIOException::what(void) const throw () {
	return message;
}

} /* namespace phantom */
