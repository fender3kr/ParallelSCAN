/*
 * Statistics.h
 *
 *  Created on: Oct 16, 2017
 *  Author: Seokyong Hong
 */

#ifndef SRC_UTIL_STATISTICS_H_
#define SRC_UTIL_STATISTICS_H_

#include <iostream>

using namespace std;

namespace phantom {

class Statistics {
private:
	double loadingTime;
	double processingTime;
	double storingTime;
	double totalExceptStoringTime;
	double totalTime;
public:
	Statistics();
	virtual ~Statistics();

	void setLoadingTime(double loadingTime);
	void setProcessingTime(double processingTime);
	void setStoringTime(double storingTime);
	void setTotalExceptStoringTime(double totalExceptStoringTime);
	void setTotalTime(double totalTime);

	double getLoadingTime(void) const;
	double getProcessingTime(void) const;
	double getStoringTime(void) const;
	double getTotalExceptStoringTime(void) const;
	double getTotalTime(void) const;

	void print(void) const;
};

} /* namespace phantom */

#endif /* SRC_UTIL_STATISTICS_H_ */
