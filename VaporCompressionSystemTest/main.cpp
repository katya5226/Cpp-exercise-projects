#include "Csystem.h"
#include <chrono>
#include <thread>




int main() {

	std::string myPath = "C:/Users/katja/source/repos/VaporCompressionSystemTest/VaporCompressionSystem/";

	std::vector<std::string> resultnames = { "", "p", "h", "rho", "x", "mfIn", "mfOut", "vIn", "vOut"};
	int rl = resultnames.size();
	std::vector<std::unique_ptr<std::ofstream>> results;

	std::vector<std::string> plotnames = { "pressure", "density", "quality", "velocity" };
	int pl = plotnames.size();
	std::vector<std::unique_ptr<std::ofstream>> plots;

	for (int i = 0; i < rl; i++) {
		results.push_back(std::make_unique<std::ofstream>());
		results[i]->open(myPath + "results/result_" + resultnames[i] + ".txt");
	}

	for (int i = 0; i < pl; i++) {
		plots.push_back(std::make_unique<std::ofstream>());
		plots[i]->open(myPath + "results/" + plotnames[i] + ".txt");
	}

	// *********************** initialization ***************************

	//____________________________________________

	double dtime = 1.0e-6;

	double length = 1;
	int numCVs = 150;

	double cvL = static_cast<double>(length / numCVs);
	double diam = 7e-3;
	double cvA = PI * pow(diam, 2) / 4;
	double cvV = cvL * cvA;

	double deltaHflow = 0.0;
	double pLeft = 775000;
	double pRight = 300000;
	double hLeft = 250000;
	double hRight = 250000;
	double massFlow = 0.1926;
	double p = 500000;
	double h = 250000;

	double alphaTilde = 0.028;

	double totalSimulationTime = 1.0e-5;
	double printInterval = 1.0e-5;

	int solver = 0;

	//___________________________________________

	*results[0] << "pLeft: " << pLeft << "\npRight: " << pRight
		<< "\nhLeft: " << hLeft << "\nhRight: " << hRight
		<< "\nalphaTilde: " << alphaTilde << "\nsolver: " << solver << "\n\n";

	// system creation and initialization
	std::unique_ptr<System> mySystem = std::make_unique<System>(numCVs);
	mySystem->initialize(dtime, cvL, cvA, deltaHflow, hLeft, hRight, massFlow, p, h, pLeft, pRight, alphaTilde);
	printConstants(mySystem, *results[0]);
	printResult(mySystem, results);


	// ********************* end of initialization *************************


	// ************************* simulation *****************************

	int nSteps = static_cast<int>(totalSimulationTime / mySystem->dt); // total number of time steps
	int m = static_cast<int>(printInterval / mySystem->dt); // print state every m steps
	int numRows = static_cast<int>(nSteps / m) + 1;

	auto start = std::chrono::high_resolution_clock::now();
	for (int step = 1; step <= nSteps; step++) {

		mySystem->guessProperties();
		mySystem->calculateFlows2();

		if (!solver) mnewt(MAXITER, mySystem, TOLX, TOLF);
		else solveExplicit2(mySystem);

		mySystem->time = step * mySystem->dt;

		mySystem->pipe->replaceOldNew();

		if (step % m == 0) {
			printResult(mySystem, results);
		}

	}
	// ************************ end of simulation ***************************

	auto finished = std::chrono::high_resolution_clock::now();
	*results[0] << "\n\nFinished\n\n";
	//printState(mySystem->pipe, *results[0]);
	std::cout << "Simulation elapsed time: " << std::chrono::duration_cast<std::chrono::seconds>(finished - start).count() << " seconds" << std::endl;
	*results[0] << "\n\nSimulation elapsed time: " << std::chrono::duration_cast<std::chrono::seconds>(finished - start).count() << " seconds" << std::endl;

	for (int i = 0; i < rl; i++) {
		results[i]->close();
	}

	for (int i = 0; i < numCVs; i++) {
		*plots[0] << (length / numCVs) * (i + 0.5) << "\t" << mySystem->pipe->controlVolumes[i]->p << "\n";
		*plots[1] << (length / numCVs) * (i + 0.5) << "\t" << mySystem->pipe->controlVolumes[i]->rho << "\n";
		*plots[2] << (length / numCVs) * (i + 0.5) << "\t" << mySystem->pipe->controlVolumes[i]->x << "\n";
		*plots[3] << (length / numCVs) * (i + 0.5) << "\t" << mySystem->pipe->controlVolumes[i]->velocity[0] << "\n";
	}
	*plots[3] << (length / numCVs) * (numCVs + 0.5) << "\t" << mySystem->pipe->cvEnd->velocity[0] << "\n";

	for (int i = 0; i < pl; i++) {
		plots[i]->close();
	}

	//makeTransposeFile(numRows, numCVs + 3, "p");
	//makeTransposeFile(numRows, numCVs + 3, "h");
	//makeTransposeFile(numRows, numCVs + 1, "rho");
	//makeTransposeFile(numRows, numCVs + 1, "x");

	return 0;
}