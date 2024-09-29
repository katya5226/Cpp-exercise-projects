#include "CSystem.h"


// Helper printing methods

void ControlVolume::printProperties() {
	std::cout << "******** CV properties *********" << std::endl;
	std::cout << "name: " << name << std::endl;
	std::cout << "parent: " << parent << std::endl;
	std::cout << "index: " << index << std::endl;
	std::cout << "numvar: " << numvar << std::endl;
	std::cout << "p: " << p << std::endl;
	std::cout << "h: " << h << std::endl;
	std::cout << "pOld: " << pOld << std::endl;
	std::cout << "hOld: " << hOld << std::endl;
	//std::cout << "vol: " << vol << std::endl;
	std::cout << "rho: " << rho << std::endl;
	std::cout << "derrhodp: " << derrhodp << std::endl;
	std::cout << "derrhodh: " << derrhodh << std::endl;
	/*std::cout << "deltaHflow: "; printVec(deltaHflow);*/
	std::cout << "massFlow: "; printVec(massFlow);
	std::cout << "********************************\n";
}

void printVec(const std::vector<double>& vec) {
	for (int i = 0; i < vec.size(); i++) {
		std::cout << std::setprecision(6) << vec[i] << "\t";
	}
	std::cout << "\n";
}

void printVecInt(const std::vector<int>& vec) {
	for (int i = 0; i < vec.size(); i++) {
		std::cout << vec[i] << "\t";
	}
	std::cout << "\n";
}

void printVecP(std::vector<double*>& vec) {
	for (int i = 0; i < vec.size(); i++) {
		std::cout << std::setprecision(6) << *vec[i] << "\t";
	}
	std::cout << "\n";
}

void printMatrix(const std::vector<std::vector<double>>& matrix) {

	std::cout << "\n********************************\n";

	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[i].size(); j++) {
			std::cout << std::setprecision(6) << matrix[i][j] << "\t";
		}
		std::cout << "\n";
	}

	std::cout << "********************************\n";
}

void printState(std::unique_ptr<Pipe>& pipe, std::ofstream& result) {
	for (auto cv : pipe->controlVolumes) {
		std::cout << "******** CV properties *********" << std::endl;
		std::cout << "index: " << cv->index << std::endl;
		std::cout << "p: " << std::setprecision(8) << cv->p << std::endl;
		std::cout << "h: " << std::setprecision(8) << cv->h << std::endl;
		std::cout << "rho: " << cv->rho << std::endl;
		std::cout << "x: " << cv->x << std::endl;
		std::cout << "phase: " << cv->phase << std::endl;
		std::cout << "derrhodp: " << cv->derrhodp << std::endl;
		std::cout << "derrhodh: " << cv->derrhodh << std::endl;
		/*std::cout << "deltaHflow: "; printVec(cv->deltaHflow);*/
		std::cout << "massFlow: "; printVec(cv->massFlow);
		std::cout << "********************************\n";
	}
	for (auto cv : pipe->controlVolumes) {
		result << "******** CV properties *********" << std::endl;
		result << "index: " << cv->index << std::endl;
		result << "p: " << cv->p << std::endl;
		result << "h: " << cv->h << std::endl;
		result << "rho: " << cv->rho << std::endl;
		result << "x: " << cv->x << std::endl;
		result << "phase: " << cv->phase << std::endl;
		result << "derrhodp: " << cv->derrhodp << std::endl;
		result << "derrhodh: " << cv->derrhodh << std::endl;
		/*result << "deltaHflow: " << cv->deltaHflow[0] << std::endl;*/
		result << "massFlow: " << cv->massFlow[1] << std::endl;
		result << "********************************\n";
	}
}

void printConstants(std::unique_ptr<System>& system, std::ofstream& result) {
	std::cout.precision(1);
	std::cout << std::fixed;

	std::cout << "******** SYSTEM CONSTANTS *********" << std::endl;
	std::cout << "CV length: " << std::scientific << system->pipe->cvL << std::endl;
	std::cout << "Number of CVs: " << std::scientific << system->pipe->numCV << std::endl;
	std::cout << "Pipe length: " << std::scientific << system->pipe->cvL * system->pipe->numCV << std::endl;
	std::cout << "CV cross section: " << std::scientific << system->pipe->cvA << std::endl;
	std::cout << "CV volume: " << std::scientific << system->pipe->cvV << std::endl;
	std::cout << "Time step: " << std::scientific << system->dt << std::endl;
	std::cout << "********************************\n";
	result << "******** SYSTEM CONSTANTS *********" << std::endl;
	result << "CV length: " << std::scientific << system->pipe->cvL << std::endl;
	result << "Number of CVs: " << std::scientific << system->pipe->numCV << std::endl;
	result << "Pipe length: " << std::scientific << system->pipe->cvL * system->pipe->numCV << std::endl;
	result << "CV cross section: " << std::scientific << system->pipe->cvA << std::endl;
	result << "CV volume: " << std::scientific << system->pipe->cvV << std::endl;
	result << "Time step: " << std::scientific << system->dt << std::endl;
	result << "********************************\n";
}

void printFlows(std::unique_ptr<Pipe>& pipe) {
	for (auto cv : pipe->controlVolumes) {
		std::cout;
		std::cout << "index: " << cv->index << "\tmf(0): " << std::setprecision(8) << cv->massFlow[0]
			<< "\tmf(1): " << std::setprecision(8) << cv->massFlow[1]
			<< "\th(0): " << std::setprecision(8) << cv->upstream[0]->h
			<< "\th(1): " << std::setprecision(8) << cv->upstream[1]->h << std::endl;
	}
}

void printPressures(std::unique_ptr<Pipe>& pipe) {
	for (auto cv : pipe->controlVolumes) {
		std::cout << "index: " << cv->index;
		std::cout << "\tp: " << std::setprecision(8) << cv->p
			<< "\th: " << std::setprecision(8) << cv->h << std::endl;
	}
}

void makeTransposeFile(int n, int m, std::string c) {

	std::vector<double> numbers;
	std::ifstream in("results/result_" + c + ".txt", std::ios::in);
	double number;
	while (in >> number) {
		numbers.push_back(number);
	}
	in.close();

	std::ofstream resultTranspose;
	resultTranspose.open("results/transpose_" + c + ".txt");

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (i == 0) {
				resultTranspose << "\"t = " +
					std::to_string(numbers[j * m])
					+ " s\"" << "\t";
			}
			else {
				resultTranspose << numbers[i + j * m] << "\t";
			}
		}
		resultTranspose << "\n";
	}

	resultTranspose.close();
}

void printResult(std::unique_ptr<System>& system, std::vector<std::unique_ptr<std::ofstream>>& results) {
	int rl = results.size();
	std::cout.precision(6);
	std::cout << std::fixed;
	//std::cout << std::fixed << system->time << "\t";
	for (int i = 1; i < rl; i++) {
		*results[i] << system->time << "\t";
	}
	//std::cout << std::scientific << system->pipe->cvStart->p << "\t";
	*results[1] << system->pipe->cvStart->p << "\t";
	*results[2] << system->pipe->cvStart->h << "\t";
	for (int i = 0; i < system->pipe->numCV; i++) {
		//std::cout << std::scientific << system->pipe->controlVolumes[i]->p << "\t";
		*results[1] << system->pipe->controlVolumes[i]->p << "\t";
		*results[2] << system->pipe->controlVolumes[i]->h << "\t";
		*results[3] << system->pipe->controlVolumes[i]->rho << "\t";
		*results[4] << system->pipe->controlVolumes[i]->x << "\t";
		*results[5] << system->pipe->controlVolumes[i]->massFlow[0] << "\t";
		*results[6] << system->pipe->controlVolumes[i]->massFlow[1] << "\t";
		*results[7] << system->pipe->controlVolumes[i]->velocity[0] << "\t";
		*results[8] << system->pipe->controlVolumes[i]->velocity[1] << "\t";
	}
	//std::cout << system->pipe->cvEnd->p << "\n";
	*results[1] << system->pipe->cvEnd->p << "\n";
	*results[2] << system->pipe->cvEnd->h << "\n";
	*results[3] << "\n";
	*results[4] << "\n";
	*results[5] << "\n";
	*results[6] << "\n";
	*results[7] << "\n";
	*results[8] << "\n";

}