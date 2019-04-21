/*
 * GraphIOException.h
 *
 *  Created on: Oct 3, 2017
 *  Author: Seokyong Hong
 */

#ifndef IO_GRAPHIOEXCEPTION_H_
#define IO_GRAPHIOEXCEPTION_H_

#include <iostream>
#include <exception>

using namespace std;

namespace phantom {

class GraphIOException : public exception {
private:
	const char *message;
public:
	GraphIOException(string message);
	virtual ~GraphIOException();

	virtual const char *what(void) const throw ();
};

} /* namespace phantom */

#endif /* IO_GRAPHIOEXCEPTION_H_ */
