/*
 * SCAN.cpp
 *
 *  Created on: Oct 16, 2017
 *  Author: Seokyong Hong
 */

#include "SCAN.h"

namespace phantom {

SCAN::SCAN(MPIHelper *helper) : helper(helper) {
	world.reset(new CommGrid(MPI::COMM_WORLD, 0, 0));
}

SCAN::~SCAN() {
}

void SCAN::detect(Parameter *parameter) {
	double t0 = helper -> getWallTime();
	Dist<double>::MPI_DCCols SMat(graph)(world);

	// Load and symmetricize graph.
	double l0 = helper -> getWallTime();
	SMat(graph).ReadDistribute(parameter -> getInputPath(), helper -> getMaster(), false, true);
	if(helper -> isMaster())
		statistics.setLoadingTime(helper -> getWallTime() - l0);

	double p0 = helper -> getWallTime();
	symmetricize(SMat(graph));

	Dist<double>::MPI_DCCols SMat(distance)(world);
	SMat(distance) = SMat(graph);
	SMat(graph).Apply(one<double, double>());

	// Compute degrees of vertices.
	Dist<uint32_t>::MPI_DenseVec DVec(degrees)(world);
	DVec(degrees) = SMat(graph).Reduce(Column, plus<double>(), 0.0);

	// Compute epsilon distances.
	Dist<double>::MPI_DCCols SMat(temp)(world);
	SMat(temp) = (Dist<double>::MPI_DCCols)SMat(graph);
	SMat(temp).DimApply(Row, DVec(degrees), plus<double>());
	SMat(temp).DimApply(Column, DVec(degrees), add_multiple_sqaure_root<double>());
	SMat(distance) = EWiseApply<double, Dist<double>::DCCols>(SMat(distance), SMat(temp), divide_by_second<double, double, double>(), always_true<double>(), false, true, 0.0, 0.0, true, false);
	SMat(distance).Prune(less_than_epsilon<double>(parameter -> getEpsilon()), true);

	// Find cores.
	Dist<uint64_t>::MPI_DenseVec DVec(cores) = SMat(distance).Reduce(Row, count_non_zeros<double, uint64_t>(), 0.0);
	DVec(cores).Apply(set_core<uint64_t>(parameter -> getMu()));
	if(helper -> isMaster())
		cout << "Cores: " << DVec(cores).Count(is_greater_than_zero<uint64_t>()) << endl;

	// Generate input graph for connected components.
	SMat(temp) = SMat(distance);
	SMat(temp).Apply(one<double, double>());
	SMat(temp).DimApply(Row, DVec(cores), multiplies<double>());
	SMat(temp).DimApply(Column, DVec(cores), multiplies<double>());
	SMat(temp).Prune(is_zero<double>(), true);
	//SMat(temp) = EWiseApply<double, Dist<double>::DCCols>(SMat(temp), SMat(temp), set_one_4<double, double, uint8_t>(), always_true<double>(), false, false, 0.0, 0.0, true, false);

	// Perform connected components operation.
	if(helper -> isMaster())
		cout << "Core edges: " << SMat(temp).getnnz() << endl;
	SMat(temp).AddLoops(1, false);
	Dist<int64_t>::MPI_DenseVec DVec(components)(world);
	DVec(components).iota(SMat(temp).getnrow(), 0);
	Dist<uint64_t>::MPI_SparseVec SVec(frontier)(components);
	while(SVec(frontier).getnnz() > 0) {
		SpMV<select_max_sr>(SMat(temp), SVec(frontier), SVec(frontier), false);
		SVec(frontier) = EWiseApply<uint64_t, uint64_t>(SVec(frontier), DVec(components), select_first<uint64_t>(), not_equal_to<uint64_t>(), false, 0UL);
		DVec(components).Set(SVec(frontier));
	}
	SMat(temp).FreeMemory();

	// Find all solitary vertices.
	Dist<uint64_t>::MPI_SparseVec SVec(frequencies)(world);
	Dist<uint64_t>::MPI_DenseVec DVec(ranges)(world);
	Dist<uint64_t>::MPI_DenseVec DVec(ones)(world, SMat(graph).getnrow(), 1UL);

	DVec(ranges).iota(SMat(graph).getnrow(), 0UL);
	Dist<uint64_t>::MPI_DCCols SMat(tempD)(SMat(graph).getnrow(), SMat(graph).getnrow(), DVec(components), DVec(ranges), DVec(ones), false);
	SVec(frequencies) = SMat(tempD).Reduce(Row, sum<uint64_t, uint64_t>(), 0UL);
	SVec(frequencies) = EWiseApply<uint64_t, uint64_t>(SVec(frequencies), DVec(cores), select_first<uint64_t>(), is_second_not_equal_to_one<uint64_t>(), false, 0UL);
	SMat(tempD).FreeMemory();

	Dist<uint64_t>::MPI_SparseVec SVec(solitaries)(world);
	SVec(solitaries) = EWiseApply<uint64_t, uint64_t>(SVec(frequencies), DVec(cores), set_one_2<uint64_t, uint8_t>(), is_solitary<uint64_t>(), false, 0UL);

	// Mark all solitary nodes as outliers.
	DVec(components).EWiseApply((Dist<int64_t>::MPI_SparseVec)SVec(solitaries), set_minus_one<int64_t, int64_t>(), false, 0L);

	// Find borders.
	SMat(distance).Apply(one<double, double>());
	SMat(distance).DimApply(Column, DVec(cores), multiplies<double>());
	SMat(distance).DimApply(Column, DVec(components), multiplies<double>());
	SMat(distance).Prune(is_zero<double>(), true);
	Dist<int64_t>::MPI_SparseVec SVec(borders)(world);
	SVec(borders) = SMat(distance).Reduce(Row, select_max<double>(), -1L);

	// Mark as borders.
	DVec(components).EWiseApply(SVec(borders), select_second<int64_t>(), is_second_greater_than_zero<int64_t>(), false, -1L);

	// Find hubs.
	SVec(solitaries) = EWiseApply<uint64_t, uint64_t>(SVec(solitaries), SVec(borders), set_one_4<uint64_t, int64_t, uint64_t>(), is_second_less_than_zero<uint64_t, int64_t>(), false, false, 0UL, -1L, true, false);
	Dist<uint8_t>::MPI_DenseVec DVec(ds)(world);
	DVec(ds) = solitaries;
	SMat(graph).DimApply(Row, DVec(ds), set_solitary<double, uint8_t>());
	SMat(graph).Prune(is_lt_or_eq_zero<double>(), true);
	SMat(graph).DimApply(Column, DVec(components), set_label<double, int64_t>());
	SMat(graph) = SMat(graph).Prune(is_less_than_zero<double>(), false);

	Dist<int64_t>::MPI_DenseVec DVec(neighborhood)(world);
	DVec(neighborhood) = SMat(graph).Reduce(Row, check_cluster<double>(), -2.0);
	DVec(components).EWiseApply(DVec(neighborhood), mark_as_hub<int64_t, int64_t>(), is_hub<int64_t, int64_t>(), false);
	if(helper -> isMaster())
		statistics.setProcessingTime(helper -> getWallTime() - p0);

	double s0 = helper -> getWallTime();
	ofstream output(parameter -> getOutputPath());
	components.SaveGathered(output, helper -> getMaster());
	output.close();
	if(helper -> isMaster())
		statistics.setStoringTime(helper -> getWallTime() - s0);

	if(helper -> isMaster()) {
		set<int64_t> communities;
		uint64_t outliers = 0UL;
		uint64_t hubs = 0UL;

		for(uint64_t index = 0UL;index < components.TotalLength();index++) {
			int64_t element = DVec(components).GetElement(index);
			if(element == -1L)
				outliers++;
			else if(element == -3L)
				hubs++;
			else
				communities.insert(element);
		}
		cout << "#Communities: " << communities.size() << endl;
		cout << "#Hubs: " << hubs << endl;
		cout << "#Outliers: " << outliers << endl;
	}

	if(helper -> isMaster())
		statistics.setTotalTime(helper -> getWallTime() - t0);
}

Statistics SCAN::getStatistics(void) const {
	return statistics;
}

} /* namespace phantom */
