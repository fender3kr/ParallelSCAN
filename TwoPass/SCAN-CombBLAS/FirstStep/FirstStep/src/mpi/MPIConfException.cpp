/*
 * MPIConfException.cpp
 *
 *  Created on: Nov 3, 2017
 *  Author: Seokyong Hong
 */

#include "MPIConfException.h"

namespace phantom {

MPIConfException::MPIConfException(string message) : message(message.c_str()) {
}

MPIConfException::~MPIConfException() {
}

const char *MPIConfException::what(void) const throw () {
	return message;
}

} /* namespace phantom */
