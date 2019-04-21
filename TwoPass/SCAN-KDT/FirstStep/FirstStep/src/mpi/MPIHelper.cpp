/*
 * MPIHelper.cpp
 *
 *  Created on: Oct 3, 2017
 *  Author: Seokyong Hong
 */

#include "MPIHelper.h"

namespace phantom {

MPIHelper::MPIHelper(int &argc, char **&argv, Parameter *parameter) {
	MPI::Init_thread(argc, argv, MPI::THREAD_MULTIPLE);
	processes = MPI::COMM_WORLD.Get_size();
	rank = MPI::COMM_WORLD.Get_rank();
	rows = parameter -> getNumberOfRows();
	columns = parameter -> getNumberOfColumns();

	if(rows * columns != processes) {
		MPI::Finalize();
		throw MPIConfException("Incorrect process numbers.");
	}

	worldComm = MPI::COMM_WORLD.Dup();

	int row = rank % rows;
	rowComm = worldComm.Split(row, rank);
	rowRank = rowComm.Get_rank();
	rankInRow = rank % rows;
}

MPIHelper::~MPIHelper() {
}

int MPIHelper::getProcesses(void) const {
	return processes;
}

int MPIHelper::getRank(void) const {
	return rank;
}

int MPIHelper::getRowRank(void) const {
	return rowRank;
}

int MPIHelper::getRankInRow(void) const {
	return rankInRow;
}

bool MPIHelper::isMaster(void) const {
	return rank == 0;
}

bool MPIHelper::isRowMaster(void) const {
	return rankInRow == 0;
}

void MPIHelper::reduceSharedNeighbors(uint64_t *counts, uint64_t *aggregatedCounts, int numberOfCounts) const {
	if(counts and aggregatedCounts and numberOfCounts > 0)
		rowComm.Allreduce(counts, aggregatedCounts, numberOfCounts, MPI::LONG, MPI::SUM);
}

double MPIHelper::getWallTime(void) const {
	return MPI::Wtime();
}

void MPIHelper::storeAsciiGraph(Parameter *parameter, uint64_t *sources, uint64_t *targets, uint64_t *counts, uint64_t edges) const {
	MTXFormatter formatter(parameter -> getNumberOfVertices(), parameter -> getNumberOfEdges());
	uint64_t edgesPerRow = (uint64_t)ceil((double)parameter -> getNumberOfEdges() / (double)parameter -> getNumberOfRows());
	uint64_t edgesPerProcess = (uint64_t)ceil((double)edges / (double)parameter -> getNumberOfColumns());

	MPI::File file = MPI::File::Open(MPI::COMM_WORLD, parameter -> getOutputPath().c_str(), MPI::MODE_CREATE | MPI::MODE_WRONLY, MPI::INFO_NULL);
	MPI::Offset displace = isMaster() ? (MPI::Offset)0 : (MPI::Offset)formatter.getHeaderLength() + (MPI::Offset)((rankInRow * edgesPerRow + rowRank * edgesPerProcess) * formatter.getLineWidth());
	file.Set_view(displace, MPI::BYTE, MPI::BYTE, "native", MPI::INFO_NULL);
	if(isMaster())
		file.Write(formatter.getHeader(), formatter.getHeaderLength(), MPI::BYTE);

	uint64_t startPosition = (uint64_t)rowRank * edgesPerProcess;
	uint64_t endPosition = (rowRank + 1UL < parameter -> getNumberOfColumns()) ? (uint64_t)(rowRank + 1UL) * edgesPerProcess : edgesPerRow;
	uint8_t *entries = formatter.getEntries(sources + startPosition, targets + startPosition, counts + startPosition, endPosition - startPosition);
	file.Write(entries, formatter.getEntryLength(), MPI::BYTE);
	file.Close();
}

void MPIHelper::storeBinaryGraph(Parameter *parameter, uint64_t *sources, uint64_t *targets, uint64_t *counts, uint64_t edges) const {
	BinaryFormatter formatter(parameter -> getNumberOfVertices(), parameter -> getNumberOfEdges());
	uint64_t edgesPerRow = (uint64_t)ceil((double)parameter -> getNumberOfEdges() / (double)parameter -> getNumberOfRows());
	uint64_t edgesPerProcess = (uint64_t)ceil((double)edges / (double)parameter -> getNumberOfColumns());

	MPI::File file = MPI::File::Open(MPI::COMM_WORLD, parameter -> getOutputPath().c_str(), MPI::MODE_CREATE | MPI::MODE_WRONLY, MPI::INFO_NULL);
	MPI::Offset displace = isMaster() ? (MPI::Offset)0 : (MPI::Offset)formatter.getHeaderLength() + (MPI::Offset)((rankInRow * edgesPerRow + rowRank * edgesPerProcess) * (MPI::Offset)formatter.getLineWidth());
	file.Set_view(displace, MPI::BYTE, MPI::BYTE, "native", MPI::INFO_NULL);
	if(isMaster())
		file.Write(formatter.getHeader(), formatter.getHeaderLength(), MPI::BYTE);

	uint64_t startPosition = (uint64_t)rowRank * edgesPerProcess;
	uint64_t endPosition = (rowRank + 1UL < parameter -> getNumberOfColumns()) ? (uint64_t)(rowRank + 1UL) * edgesPerProcess : edgesPerRow;
	uint8_t *entries = formatter.getEntries(sources + startPosition, targets + startPosition, counts + startPosition, endPosition - startPosition);
	file.Write(entries, formatter.getEntryLength(), MPI::BYTE);
	file.Close();
}

void MPIHelper::storeGraph(Parameter *parameter, uint64_t *sources, uint64_t *targets, uint64_t *counts, uint64_t edges, bool binary) const {
	if(binary)
		storeBinaryGraph(parameter, sources, targets, counts, edges);
	else
		storeAsciiGraph(parameter, sources, targets, counts, edges);
}

void MPIHelper::finalize(void) const {
	MPI::Finalize();
}

} /* namespace phantom */
