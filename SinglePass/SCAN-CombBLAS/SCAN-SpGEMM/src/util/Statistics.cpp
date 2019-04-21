/*
 * Statistics.cpp
 *
 *  Created on: Oct 16, 2017
 *  Author: Seokyong Hong
 */

#include "Statistics.h"

namespace phantom {

Statistics::Statistics() {
}

Statistics::~Statistics() {
}

void Statistics::setLoadingTime(double loadingTime) {
	this -> loadingTime = loadingTime;
}

void Statistics::setProcessingTime(double processingTime) {
	this -> processingTime = processingTime;
}

void Statistics::setStoringTime(double storingTime) {
	this -> storingTime = storingTime;
}

void Statistics::setTotalExceptStoringTime(double totalExceptStoringTime) {
	this -> totalExceptStoringTime = totalExceptStoringTime;
}
void Statistics::setTotalTime(double totalTime) {
	this -> totalTime = totalTime;
}

double Statistics::getLoadingTime(void) const {
	return loadingTime;
}

double Statistics::getProcessingTime(void) const {
	return processingTime;
}

double Statistics::getStoringTime(void) const {
	return storingTime;
}

double Statistics::getTotalExceptStoringTime(void) const {
	return totalExceptStoringTime;
}

double Statistics::getTotalTime(void) const {
	return totalTime;
}

void Statistics::print(void) const {
	cout << "Data Loading: " << loadingTime << " seconds" << endl;
	cout << "Processing: " << processingTime << " seconds" << endl;
	cout << "Storing: " << storingTime << " seconds" << endl;
	cout << "Total except Storing Time: " << totalExceptStoringTime << " seconds" << endl;
	cout << "Total: " << totalTime << " seconds" << endl;
}

} /* namespace phantom */
