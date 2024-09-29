#pragma warning(disable:4786)
#ifndef __SIMLIB__SIMULATION
#define __SIMLIB__SIMULATION

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <iomanip>

class Simulation {
	double left_temperature{ 0 };
	double right_temperature{ 0 };
	std::vector<int> num_nodes{10, 10, 10, 10, 10};
	std::vector<double> starting_temps;
	double frequency{ 25 };
	double time_step{ 0.0001 };
	double spacestep{ 0.0001 };
	std::vector<double> densities{ 7000, 7000, 7000, 7000, 7000 };
	std::vector<double> heat_jump_coeff{ 200, 200 };
	int magnetic_field{ 1 };
	double magnetization_time{ 0.01 };
	int num_steps{ 1 };
	double tolerance{ 0.1 };
	double stopping_condition{ 10 };

	std::vector<double> inner_transfer(const std::vector<double>&, const std::vector<double>&,
		const std::vector<double>&, int, int);

	std::vector<double> mcm_inner_transfer(const std::vector<double>&, const std::vector<double>&,
		const std::vector<double>&, int, int, int);

	std::vector<double> step(const std::vector<double>&);

public:
	void readData(const char* filename, std::vector<double>&);
};

#endif //__SIMLIB__SIMULATION