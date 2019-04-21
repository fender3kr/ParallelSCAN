/*
 * MPIConfException.h
 *
 *  Created on: Nov 3, 2017
 *  Author: Seokyong Hong
 */

#ifndef MPI_MPICONFEXCEPTION_H_
#define MPI_MPICONFEXCEPTION_H_

#include <iostream>
#include <exception>

using namespace std;

namespace phantom {

class MPIConfException : public exception {
private:
	const char *message;
public:
	MPIConfException(string message);
	virtual ~MPIConfException();

	virtual const char *what(void) const throw ();
};

} /* namespace phantom */

#endif /* MPI_MPICONFEXCEPTION_H_ */
