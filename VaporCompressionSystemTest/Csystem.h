#ifndef CSYSTEM_H
#define CSYSTEM_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <iterator>
#include <memory>
#include <exception>
#include "CSconstants.h"
//#include "include/CoolProplib.h"
//#include "include/CoolProp.h"
//#include "include/AbstractState.h"
//#include "include/crossplatform_shared_ptr.h"
#include "interpolation.h"


// ***************** simulation classes & methods *********************

class ControlVolume {
public:
	ControlVolume(std::string, int, int);

	std::string name = "control volume";
	std::string parent;
	int index{ 0 };
	int numFaces{ 2 };
	int numvar{ 3 };
	//double vol = C_VOLUME;

	// ---------- properties ------------------
	double p{ 0.0 }; // Pa
	double h{ 0.0 }; // J/kg

	double pOld{ 0.0 };
	double hOld{ 0.0 };

	double dp{ 0.0 };
	double dh{ 0.0 };
	double du{ 0.0 };

	double rho{ 0.0 }; // kg/m^3
	double derrhodp{ 0.0 }; // kg/Pa m^3
	double derrhodh{ 0.0 }; // kg^2/Jm^3
	double secderrhodp{ 0.0 };
	double secderrhodh{ 0.0 };
	double secderrhodhdp{ 0.0 };
	double K{ 0.0 };
	double he{ 0.0 };
	double hw{ 0.0 };
	double Wuh_i{ 0.0 };
	double Zuh_i{ 0.0 };

	double x{ 0.0 }; // mol/mol
	int phase{ 0 }; // phase of the fluid inside the cv

	double rhoLiquid{ 0.0 }; // liquid density kg/m^3
	double rhoVapor{ 0.0 }; // vapor density kg/m^3
	double hLiquid{ 0.0 }; // liquid enthalpy J/kg
	double hVapor{ 0.0 }; // vapor enthalpy J/kg

	// four faces: left, right, up, down - the next vectors are of length 4
	std::vector<double> deltaHflow; // Watt
	std::vector<double> massFlow; // kg/s
	std::vector<double> velocity; // kg/s
	std::vector<double> velocityOld; // kg/s
	std::vector<std::shared_ptr<ControlVolume>> neighbours; // neighbour control volumes at the four faces
	std::vector<int> directions; // directions of flow on the four faces (-1 means out, 1 means in)
	std::vector<std::shared_ptr<ControlVolume>> upstream; // upstream control volumes at the four faces

	// helper variables for Jacobian
	int flowCase{ 0 };
	double mj{ 0.0 };
	double mfdiff{ 0.0 };
	double a{ 0.0 };
	double Fp{ 0.0 };
	double Fh{ 0.0 };
	double Fu{ 0.0 };
	double dz{ 0.0 };

	// -----------------------------------------

	void printProperties();
};


class Pipe {
public:
	Pipe(std::string, int, int);

	std::string name = "pipe";
	std::string parent;
	int index{ 0 };
	int numCV{ 0 };
	int numvar{ 3 };  // this can be constructor input if necessary
	std::vector<std::shared_ptr<ControlVolume>> controlVolumes;

	double* time = nullptr;
	double dt{ 0.0 };

	double cvL{ 0.0 };
	double cvA{ 0.0 };
	double cvV{ 0.0 };

	std::vector<double*> stateVec;
	std::vector<double*> stateVecOld;
	std::vector<double> rhs;
	std::vector<std::vector<double>> jacobi;

	std::shared_ptr<ControlVolume> cvStart;
	std::shared_ptr<ControlVolume> cvEnd;
	double massFlowIn{ 0.0 }; // boundary condition
	double alpha{ 0.0 };

	void constructStateVecs(); // Method to construct old and new state vectors
	void calcJacobi(); // Method to calculateJacobi matrix of system to solve
	void calcRHS(); // Method to calculate right hand sides of system to solve
	void replaceOldNew(); // Method for replacing the old state vector with a new one

};

class Separator {
public:
	Separator(std::string, std::shared_ptr<ControlVolume>&, std::shared_ptr<ControlVolume>&);

	std::string name = "separator";
	std::string parent;
	int index{ 0 };
	int numCV{ 1 };
	int numvar{ 2 };  // this can be constructor input if necessary
	std::shared_ptr<ControlVolume> cvSep;
	std::shared_ptr<ControlVolume> cvIn;
	std::shared_ptr<ControlVolume> cvOut;

	double* time = nullptr;
	double dt{ 0.0 };

	double cvL{ 0.0 };
	double cvA{ 0.0 };
	double cvV{ 0.0 };


	std::vector<double*> stateVec;
	std::vector<double*> stateVecOld;
	std::vector<double> rhs;
	std::vector<std::vector<double>> jacobi;

	double hIn{ 0.0 }; // boundary condition
	double hOut{ 0.0 }; // boundary condition
	double massFlowIn{ 0.0 }; // boundary condition
	double pIn{ 0.0 }; // boundary condition
	double pOut{ 0.0 }; // boundary condition

	double lNom{ 0.0 };
	double f1{ 0.0 };
	double f2{ 0.0 };
	double xOut{ 0.01 };

	void f(double&, double, double, double&);
	void calculatehOut();

	void constructStateVecs(); // Method to construct old and new state vectors
	void calculateRHS(); // Method to calculate right hand sides of system to solve
	void calculateJacobi(); // Method to calculate Jacobi matrix of system to solve
	void replaceOldNew(); // Method for replacing the old state vector with a new one

};

class Valve {
public:
	Valve(std::string, std::shared_ptr<ControlVolume>&, std::shared_ptr<ControlVolume>&);

	std::string name = "valve";
	std::string parent;
	int index{ 0 };
	int numCV{ 0 };
	int numvar{ 2 };  // this can be constructor input if necessary
	std::shared_ptr<ControlVolume> cvSep;
	std::shared_ptr<ControlVolume> cvIn;
	std::shared_ptr<ControlVolume> cvOut;

	double* time = nullptr;
	double dt{ 0.0 };

	double nomA{ 0.0001 };
	double knu{ 1.0 };

	double hIn{ 0.0 }; // boundary condition
	double hOut{ 0.0 }; // boundary condition
	double massFlowIn{ 0.0 }; // boundary condition
	double pIn{ 0.0 }; // boundary condition
	double pOut{ 0.0 }; // boundary condition

	void calculatemf();

};


class System {
public:
	System(int);

	std::string name = "system";
	int numComponents{ 1 };
	std::unique_ptr<Pipe> pipe;

	std::string fluid = "R134A";
	/*std::shared_ptr<CoolProp::AbstractState> Fluid;*/

	std::unique_ptr<std::vector<double>> pressures = std::make_unique<std::vector<double>>();
	std::unique_ptr<std::vector<double>> enthalpies = std::make_unique<std::vector<double>>();
	std::unique_ptr<std::vector<double>> fvals = std::make_unique<std::vector<double>>();
	std::unique_ptr<std::vector<std::vector<double>>> rhoM = std::make_unique<std::vector<std::vector<double>>>();
	std::unique_ptr<std::vector<std::vector<double>>> derrhodpM = std::make_unique<std::vector<std::vector<double>>>();
	std::unique_ptr<std::vector<std::vector<double>>> derrhodhM = std::make_unique<std::vector<std::vector<double>>>();
	std::unique_ptr<std::vector<std::vector<double>>> qualityM = std::make_unique<std::vector<std::vector<double>>>();

	std::unique_ptr<BilinInterp> rhoInterp;
	std::unique_ptr<BilinInterp> derrhodpInterp;
	std::unique_ptr<BilinInterp> derrhodhInterp;
	std::unique_ptr<BilinInterp> qualityInterp;

	double time{ 0.0 };
	double dt{ 0.0 };

	void initialize(double, double, double, double, double, double, double, double, double, double, double, double); // initialize the system with boundary conditions for pipe and initial values
	void guessProperties(); // Method to read fluid properties from tables
	void calculateFlows(); // Method to calculate flows
	void calculateFlows2();

};
// ***********************************************************************


// Printing methods
void printVec(const std::vector<double>&);
void printVecP(std::vector<double*>&);
void printMatrix(const std::vector<std::vector<double>>&);
void printState(std::unique_ptr<Pipe>&, std::ofstream&);
void printConstants(std::unique_ptr<System>&, std::ofstream&);
void printFlows(std::unique_ptr<Pipe>&);
void printPressures(std::unique_ptr<Pipe>&);
void makeTransposeFile(int, int, std::string);
void printResult(std::unique_ptr<System>&, std::vector<std::unique_ptr<std::ofstream>>&);


// ******************** Solver methods ***********************

void mnewt(int, std::unique_ptr<System>&, double, double);
void ludcmp(std::vector<std::vector<double>>&, std::vector<int>&, double*, int);
void solve(std::vector<std::vector<double>>&, const std::vector<double>&, std::vector<double>&, std::vector<int>&, int);
void solveExplicit2(std::unique_ptr<System>&);


// ******************** Other methods ***********************


#endif  // CSYSTEM_H
