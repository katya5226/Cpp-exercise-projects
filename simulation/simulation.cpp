#include "simulation.h"

std::vector<double> Simulation::inner_transfer(const std::vector<double>& X,
	const std::vector<double>& coeff, const std::vector<double>& spec_heat, int index, int i) {
	const double& a = X[i] / 1000;
	const double& b = X[i] / 1000;
	const double& c = 0.2;
	const double& z = 0.5 * X[i];
	std::vector<double> res{ a, b, c, z };
	return res;
}

std::vector<double> Simulation::mcm_inner_transfer(const std::vector<double>& X,
	const std::vector<double>& coeff, const std::vector<double>& spec_heat, int index, int i, int field) {
	std::vector<double> res;
	if (field) {
		res.push_back(X[i] / 1000);
		res.push_back(X[i] / 1000);
		res.push_back(0.2);
		res.push_back(0.5*X[i]);
	}
	else {
		res.push_back(X[i] / 1000);
		res.push_back(X[i] / 1000);
		res.push_back(0.2);
		res.push_back(0.5 * X[i]);
	}
	return res;
}

 void Simulation::readData(const char* filename, std::vector<double>& data) {

	std::ifstream ifile(filename, std::ios::in);

	if (!ifile.is_open()) {
		std::cerr << "There was a problem opening the input file!\n";
		exit(1);
	}

	double num = 0.0000000;
	while (ifile >> num) {
		data.push_back(num);
	}

	for (int i = 0; i < data.size(); ++i) {
		std::cout << std::setprecision(15) << data[i] << std::endl;
	}

	ifile.close();
}