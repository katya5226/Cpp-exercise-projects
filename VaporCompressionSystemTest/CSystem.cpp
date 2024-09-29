#include "Csystem.h"
#include "readData.h"
//using namespace CoolProp;


template <typename T> int sgn(T val) {
	return (T(0) <= val) - (val < T(0));
}

// ControlVolume constructor
ControlVolume::ControlVolume(std::string aparent, int i, int nf) : parent(aparent), index(i), numFaces(nf) {
	deltaHflow.resize(static_cast<int>(numFaces / 2 + 0.5), 0.0);
	massFlow.resize(numFaces, 0.1);
	velocity.resize(numFaces, 10.0);
	velocityOld.resize(numFaces, 10.0);
	directions.resize(numFaces);
	neighbours.resize(numFaces);
	upstream.resize(numFaces);
}

// Pipe constructor
Pipe::Pipe(std::string aparent, int i, int n) : parent(aparent), index(i), numCV(n) {

	cvStart = std::make_shared<ControlVolume>("pipe", -1, 2);
	cvEnd = std::make_shared<ControlVolume>("pipe", -1, 2);

	for (int i = 0; i < n; i++) {
		controlVolumes.push_back(std::make_shared<ControlVolume>("pipe", i, 2));  // constructs numCV control volumes inside the pipe
	}
	for (int i = 0; i < n; i++) {
		if (i == 0) controlVolumes[i]->neighbours[1] = controlVolumes[1];
		else if (i == numCV - 1) controlVolumes[i]->neighbours[0] = controlVolumes[numCV - 2];
		else {
			controlVolumes[i]->neighbours[0] = controlVolumes[i - 1];
			controlVolumes[i]->neighbours[1] = controlVolumes[i + 1];
		}
	}
	int num = numCV * numvar;
	rhs.resize(num);  // prepares the rhs vector
	jacobi.resize(num);  // prepares the jacobi matrix
	for (int i = 0; i < num; i++) {
		jacobi[i].resize(num);
	}
}

void Pipe::constructStateVecs() {
	for (int i = 0; i < numCV; i++) {
		std::shared_ptr<ControlVolume> cv = controlVolumes[i];
		stateVec.push_back(&(cv->p));
		stateVec.push_back(&(cv->h));
		stateVec.push_back(&(cv->velocity[0]));
		stateVecOld.push_back(&(cv->pOld));
		stateVecOld.push_back(&(cv->hOld));
		stateVecOld.push_back(&(cv->velocityOld[0]));
	}
}

void Pipe::calcJacobi() {

	int num = numCV * numvar;
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num; j++) {
			jacobi[i][j] = 0.0;
		}
	}

	//int ii{ 0 };
	//std::shared_ptr<ControlVolume> cv;
	//double hm{ 0.0 };
	//double mflow{ 0.0 };

	//std::ofstream outFile;
	//outFile.open("results/solving.txt", std::ios_base::app);

	//for (int i = 0; i < numCV; i++) {

	//	ii = numvar * i;
	//	cv = controlVolumes[i];
	//	cv->a = cvV * (cv->rho * cv->derrhodp + cv->derrhodh);
	//	hm = cv->upstream[0]->h * cv->massFlow[0] + cv->upstream[1]->h * cv->massFlow[1] + cv->deltaHflow[0];
	//	mflow = cv->massFlow[0] + cv->massFlow[1];

	//	//std::cout << cv->p << "\n";
	//	//std::cout << cv->massFlow[0] << "\n";

	//	jacobi[ii][ii] = 1;
	//	jacobi[ii][ii + 1] = (dt/cv->a) * cv->derrhodh * cv->mfdiff;
	//	//jacobi[ii][ii + 1] = (dt / cv->a) * 0.001 * cv->mfdiff;
	//	jacobi[ii + 1][ii] = 0;
	//	jacobi[ii + 1][ii + 1] = 1 - (dt / cv->a) * cv->derrhodp * cv->mfdiff;


	//	// *** corrected
	//	jacobi[ii][ii] = 1;
	//	jacobi[ii][ii + 1] = (dt / cv->a) * cv->derrhodh * cv->mfdiff;
	//	//jacobi[ii][ii + 2] = -dt * (cv->upstream[0]->rho *
	//	//	(cv->h - cv->upstream[0]->h) * cv->derrhodh / cv->a +
	//	//	((1 / cvL) - cv->derrhodh / cv->a) / cv->derrhodp);
	//	jacobi[ii][ii + 2] = -(1 / cv->derrhodp) * (dt / cvL) * (
	//		((1 / cv->derrhodp - cv->h) / (1 - cv->derrhodh * (cv->derrhodh / cv->derrhodp + cv->rho))) * cv->upstream[0]->rho -
	//		cv->derrhodh / (cv->derrhodh / cv->derrhodp + cv->rho) * cv->upstream[0]->rho * cv->h);

	//	jacobi[ii + 1][ii] = 0;
	//	jacobi[ii + 1][ii + 1] = 1 - (dt / cv->a) * cv->derrhodp * cv->mfdiff;
	//	//jacobi[ii + 1][ii + 2] = -dt * (cv->upstream[0]->rho *
	//	//	(-1) * (cv->h - cv->upstream[0]->h) /
	//	//	(cv->a * cv->derrhodp) + cv->upstream[0]->rho / cv->a);
	//	jacobi[ii + 1][ii + 2] = -(dt / cvL) / (cv->derrhodh / cv->derrhodp + cv->rho) *
	//		((1 / (cv->derrhodp) - cv->h) * cv->upstream[0]->rho + cv->upstream[0]->h * cv->upstream[0]->rho);

	//	jacobi[ii + 2][ii] = dt / (cvL * (cv->upstream[0]->rho));
	//	jacobi[ii + 2][ii + 1] = 0;
	//	jacobi[ii + 2][ii + 2] = 1 - (2 * dt / cvL) * alpha * abs(cv->velocity[0]);

	//	// *** end corrected


	//	//std::cout << "\n\n" << (dt / cv->a) * cv->derrhodh * cv->mfdiff << "\n";
	//	//std::cout << jacobi[ii][ii + 1] << "\n";
	//	//std::cout << "\n\n" << (dt / cv->a) * cv->derrhodp * cv->mfdiff << "\n";
	//	//std::cout << jacobi[ii + 1][ii + 1] << "\n";

	//}
	//outFile << "\n********************************\n";
	//for (int i = 0; i < jacobi.size(); i++) {
	//	for (int j = 0; j < jacobi[i].size(); j++) {
	//		outFile << std::setprecision(6) << jacobi[i][j] << "\t";
	//	}
	//	outFile << "\n";
	//}
	//outFile << "********************************\n";
	//outFile.close();


		//ADD GABER
	int ii{ 0 };
	std::shared_ptr<ControlVolume> cv;

	for (int i = 0; i < numCV; ++i) {
		ii = numvar * i;
		cv = controlVolumes[i];

		cv->K = cvA / cvV * pow(cv->derrhodh, -1) * pow((1 + cv->rho * pow(cv->derrhodp, 1) * pow(cv->derrhodh, -1)), -1);
		cv->he = (cv->upstream[1]->h - cv->h);
		cv->hw = (cv->upstream[0]->h - cv->h);

		//WEST/LEFT JACOBI u_i = (u_iw,u_ie,0,0) - > u_i = (u_iw,0,0,0)
		jacobi[ii][ii] = 1; // F_p/p
		jacobi[ii][ii + 1] = dt * ((cv->velocity[0] * cv->upstream[0]->rho + cv->velocity[1] * cv->upstream[1]->rho) *
			(cv->rho * cv->K * cv->derrhodp + (cvA / cvV)));  // F_p/h
		jacobi[ii][ii + 2] = -dt * cv->upstream[0]->rho * (cv->rho * cv->K +
			cv->hw * (cv->rho * cv->K * cv->derrhodp + (cvA / cvV))); // F_p/u

		jacobi[ii + 1][ii] = 0;//F_h/p
		jacobi[ii + 1][ii + 1] = 1 + dt * cv->K * cv->derrhodp * (cv->velocity[0] * cv->upstream[0]->rho + cv->velocity[1] * cv->upstream[1]->rho);//F_h/h
		jacobi[ii + 1][ii + 2] = -dt * cv->K * cv->upstream[0]->rho * (1 + cv->derrhodp * cv->hw); //F_h/u

		jacobi[ii + 2][ii] = (cvA / cvV) * (dt / cv->upstream[0]->rho); //F_u/p 
		jacobi[ii + 2][ii + 1] = (dt * cv->velocity[0] / cv->upstream[0]->rho) * ((cv->velocity[0] * cv->upstream[0]->rho + cv->velocity[1] * cv->upstream[1]->rho) *
			(cv->K * cv->derrhodp * (cv->rho * cv->upstream[0]->derrhodp - cv->upstream[0]->derrhodh) - (cvA * cv->upstream[0]->derrhodp / cvV))); // F_u/h 
		//jacobi[ii + 2][ii + 2] = 1 - (dt / cv->upstream[0]->rho) * ((cvA / cvV) * (std::abs(cv->velocity[0]) + cv->velocity[0]) * (cv->upstream[0]->rho - alpha * cv->upstream[0]->rho) +
		//	(cvA * cv->upstream[0]->derrhodp / cvV) * (2 * cv->upstream[0]->rho * cv->velocity[0] * cv->hw + cv->upstream[1]->rho * cv->velocity[1] * cv->he) -
		//	cv->K * (cv->rho * cv->upstream[0]->derrhodp + cv->upstream[0]->derrhodh) * (2 * cv->upstream[0]->rho * cv->velocity[0] * (1 + cv->derrhodp * cv->hw) +
		//		cv->upstream[1]->rho * cv->velocity[1] * (1 + cv->derrhodp * cv->he)));  //F_u/u
		jacobi[ii + 2][ii + 2] = 1 - (2 * dt / cvL) * alpha * abs(cv->velocity[0]);

	}

}

void Pipe::calcRHS() {

	int num = numCV * numvar;
	for (int i = 0; i < num; i++) {
		rhs[i] = 0.0;
	}

	int ii{ 0 };
	std::shared_ptr<ControlVolume> cv;
	double hm{ 0.0 };
	double mflow{ 0.0 };
	double vcomponent1{ 0.0 };
	double vcomponent2{ 0.0 };

	std::ofstream outFile;
	outFile.open("C:/Users/katja/source/repos/VaporCompressionSystemTest/VaporCompressionSystem/results/solving.txt", std::ios_base::app);

	//for (int i = 0; i < numCV; i++) {

	//	ii = numvar * i;
	//	cv = controlVolumes[i];
	//	cv->a = cvV * (cv->rho * cv->derrhodp + cv->derrhodh);

	//	//std::cout << cv->p << "\n";
	//	//std::cout << cv->massFlow[0] << "\n";
	//	//std::cout << cv->massFlow[1] << "\n";

	//	//std::cout << cv->upstream[0]->h << "\n";
	//	//std::cout << cv->upstream[1]->h << "\n";

	//	hm = cv->upstream[0]->h * cv->massFlow[0] + cv->upstream[1]->h * cv->massFlow[1] + cv->deltaHflow[0];
	//	vcomponent1 = 0.5 * cvA * (cv->upstream[0]->rho * pow(cv->velocity[0], 3) + cv->upstream[1]->rho * pow(cv->velocity[1],3));
	//	vcomponent2 = 0.5 * pow(cv->velocity[0], 2);

	//	mflow = cv->massFlow[0] + cv->massFlow[1];

	//	//std::cout << hm << "\n";
	//	//std::cout << mflow << "\n";
	//	//std::cout << cv->derrhodh * hm * dt / cv->a << "\n";
	//	//std::cout << cv->derrhodh * hm * dt / cv->a - (cv->h * cv->derrhodh + cv->rho) * mflow * dt / cv->a << "\n";

	//	//cv->Fp = cv->p - cv->pOld + cv->derrhodh * hm * dt / cv->a - (cv->h * cv->derrhodh + cv->rho) * mflow * dt / cv->a;

	//	//cv->Fh = cv->h - cv->hOld - cv->derrhodp * hm * dt / cv->a + (cv->h * cv->derrhodp - 1) * mflow * dt / cv->a;

	//	double dpdt = (1 / cv->a) * ((-1) * cv->derrhodh * cvA * hm + (cv->h * cv->derrhodh + cv->rho) * mflow);
	//	double dhdt = (1 / cv->a) * (cv->derrhodp * hm - (cv->h * cv->derrhodp - 1) * mflow);

	//	cv->Fp = cv->p - cv->pOld + cv->derrhodh * (hm + vcomponent1) * dt / cv->a - ((cv->h + vcomponent2) * cv->derrhodh + cv->rho) * mflow * dt / cv->a;

	//	cv->Fh = cv->h - cv->hOld - cv->derrhodp * (hm + vcomponent1) * dt / cv->a + ((cv->h + vcomponent2) * cv->derrhodp - 1) * mflow * dt / cv->a;

	//	//cv->Fu = cv->velocity[0] - cv->velocityOld[0] + (2 * dt * cv->velocity[0] / (cv->upstream[0]->rho + cv->rho)) * (cv->upstream[0]->derrhodp * dpdt + cv->upstream[0]->derrhodh * dhdt) -
	//	//	(2 * dt / cvL) * (cv->upstream[0]->rho / (cv->upstream[0]->rho + cv->rho)) * pow(cv->velocity[0], 2) + (2 * dt / cvL) * (cv->rho / (cv->upstream[0]->rho + cv->rho)) * pow(cv->velocity[1], 2) -
	//	//	(2 * dt / cvL) * (1 / (cv->upstream[0]->rho + cv->rho)) * (cv->upstream[0]->p - cv->p) + (2 * dt / cvL) * (alpha / (cv->upstream[0]->rho + cv->rho)) * pow(cv->velocity[0], 2) +
	//	//	GRAVITY * dt * cv->dz / cvL;

	//	if (i == 0) {
	//		cv->Fu = cv->velocity[0] - cv->velocityOld[0] - (1 / (cvL * cv->upstream[0]->rho)) * (cvStart->p - cv->p - alpha * cv->upstream[0]->rho * cv->velocity[0] * abs(cv->velocity[0]));
	//	}
	//	else {
	//		cv->Fu = cv->velocity[0] - cv->velocityOld[0] - (1 / (cvL * cv->upstream[0]->rho)) * (controlVolumes[i-1]->p - cv->p - alpha * cv->upstream[0]->rho * cv->velocity[0] * abs(cv->velocity[0]));
	//	}

	//	//std::cout << cv->Fp << "\n";

	//	rhs[ii] = cv->Fp;
	//	rhs[ii + 1] = cv->Fh;
	//	rhs[ii + 2] = cv->Fu;

	//}


		//GABER
	for (int i = 0; i < numCV; ++i) {
		ii = numvar * i;
		cv = controlVolumes[i];

		cv->K = (cvA / cvV) * pow(cv->derrhodh, -1) * pow((1 + cv->rho * pow(cv->derrhodp, 1) * pow(cv->derrhodh, -1)), -1);

		cv->Wuh_i = cv->upstream[0]->rho * cv->velocity[0] * (1 + cv->derrhodp * (cv->upstream[0]->h - cv->h)) +
			cv->upstream[1]->rho * cv->velocity[1] * (1 + cv->derrhodp * (cv->upstream[1]->h - cv->h));

		cv->Zuh_i = (cvA / cvV) * (cv->upstream[0]->rho * cv->velocity[0] * (cv->upstream[0]->h - cv->h) +
			cv->upstream[1]->rho * cv->velocity[1] * (cv->upstream[1]->h - cv->h));

		cv->Fp = cv->p - cv->pOld - dt * (cv->rho * cv->K * cv->Wuh_i - cv->Zuh_i);
		cv->Fh = cv->h - cv->hOld - dt * cv->K * cv->Wuh_i;
		//cv->Fu = cv->velocity[0] - cv->velocityOld[0] - (dt / cv->upstream[0]->rho) * ((cvA / cvV) * (cv->velocity[0] * std::abs(cv->velocity[0]) * (cv->upstream[0]->rho - alpha * cv->upstream[0]->rho) +
		//	cv->upstream[1]->rho * cv->velocity[1] * std::abs(cv->velocity[1]) + cv->pOld - cv->p) - cv->velocity[0] * cv->upstream[0]->derrhodp * (cv->rho * cv->K * cv->Wuh_i - cv->Zuh_i) -
		//	cv->velocity[0] * cv->upstream[0]->derrhodh * cv->K * cv->Wuh_i);

		if (i == 0) {
			cv->Fu = cv->velocity[0] - cv->velocityOld[0] - (1 / (cvL * cv->upstream[0]->rho)) * (cvStart->p - cv->p - alpha * cv->upstream[0]->rho * cv->velocity[0] * abs(cv->velocity[0]));
		}
		else {
			cv->Fu = cv->velocity[0] - cv->velocityOld[0] - (1 / (cvL * cv->upstream[0]->rho)) * (controlVolumes[i-1]->p - cv->p - alpha * cv->upstream[0]->rho * cv->velocity[0] * abs(cv->velocity[0]));
		}

		rhs[ii] = cv->Fp;
		rhs[ii + 1] = cv->Fh;
		rhs[ii + 2] = cv->Fu;
	}
	outFile << "Rhs:\n";
	for (int i = 2; i < rhs.size() - 3; i+=3) {
		outFile << std::setprecision(6) << rhs[i] << "\t";
	}
	outFile << "\n";
	outFile.close();
}

//void Pipe::calcRHS() {
//
//	int ii{ 0 };
//	std::shared_ptr<ControlVolume> cv;
//	double hm{ 0.0 };
//	double mflow{ 0.0 };
//	double vcomponent1{ 0.0 };
//	double vcomponent2{ 0.0 };
//
//	//std::ofstream outFile;
//	//outFile.open("results/solving.txt", std::ios_base::app);
//
//	for (int i = 0; i < numCV; i++) {
//
//		ii = numvar * i;
//		cv = controlVolumes[i];
//		cv->a = cvL * (cv->rho * cv->derrhodp + cv->derrhodh);
//
//		//std::cout << cv->p << "\n";
//		//std::cout << cv->massFlow[0] << "\n";
//		//std::cout << cv->massFlow[1] << "\n";
//
//		//std::cout << cv->upstream[0]->h << "\n";
//		//std::cout << cv->upstream[1]->h << "\n";
//
//		hm = cv->upstream[0]->h * cv->massFlow[0] + cv->upstream[1]->h * cv->massFlow[1] + cv->deltaHflow[0];
//		vcomponent1 = 0.5 * cvA * (cv->upstream[0]->rho * pow(cv->velocity[0], 3) + cv->upstream[1]->rho * pow(cv->velocity[1], 3));
//		vcomponent2 = 0.5 * pow(cv->velocity[0], 2);
//
//		mflow = cv->massFlow[0] + cv->massFlow[1];
//
//		//std::cout << hm << "\n";
//		//std::cout << mflow << "\n";
//		//std::cout << cv->derrhodh * hm * dt / cv->a << "\n";
//		//std::cout << cv->derrhodh * hm * dt / cv->a - (cv->h * cv->derrhodh + cv->rho) * mflow * dt / cv->a << "\n";
//
//		//cv->Fp = cv->p - cv->pOld + cv->derrhodh * hm * dt / cv->a - (cv->h * cv->derrhodh + cv->rho) * mflow * dt / cv->a;
//
//		//cv->Fh = cv->h - cv->hOld - cv->derrhodp * hm * dt / cv->a + (cv->h * cv->derrhodp - 1) * mflow * dt / cv->a;
//
//		cv->Fp = cv->p - cv->pOld + cv->derrhodh * (hm + vcomponent1) * dt / cv->a - ((cv->h + vcomponent2) * cv->derrhodh + cv->rho) * mflow * dt / cv->a;
//
//		cv->Fh = cv->h - cv->hOld - cv->derrhodp * (hm + vcomponent1) * dt / cv->a + ((cv->h + vcomponent2) * cv->derrhodp - 1) * mflow * dt / cv->a;
//
//		//std::cout << cv->Fp << "\n";
//
//		rhs[ii] = cv->Fp;
//		rhs[ii + 1] = cv->Fh;
//
//	}
//}

void Pipe::replaceOldNew() {
	for (int i = 0; i < numCV * numvar; i++) {
		*stateVecOld[i] = *stateVec[i];
	}
	//for (int i = 0; i < numCV; i++) {
	//	controlVolumes[i]->velocityOld[0] = controlVolumes[i]->velocity[0];
	//}
}

// Separator constructor
Separator::Separator(std::string aparent, std::shared_ptr<ControlVolume>& cvIn, std::shared_ptr<ControlVolume>& cvOut) : parent(aparent) {
	cvSep = std::make_shared<ControlVolume>("separator", 0, 2);
	this->cvIn = cvIn;
	this->cvOut = cvOut;
}

// Separator calculations
void Separator::f(double& ln, double lt, double dl, double& f) {
	double phi = (ln - lt) * PI / dl;
	if (ln <= (lt - dl / 2)) f = 1;
	else if ((lt - dl / 2) < ln && ln < (lt + dl / 2)) f = -0.5 * sin(phi) + 0.5;
	else if (ln > (lt + dl / 2)) f = 0;
}

void Separator::calculatehOut() {

	// calculate rhoLiquid here or at an appropriate point

	lNom = (1 - cvSep->x) * cvSep->rho / cvSep->rhoLiquid;
	f(lNom, 0.05, 0.1, f1);
	f(lNom, 0.95, 0.1, f2);
	hOut = f2 * cvSep->h + (1 - f2) * (f1 * cvSep->h + (1 - f1) * (xOut * (cvSep->hVapor - cvSep->hLiquid) + cvSep->hLiquid));
}

// Valve constructor
Valve::Valve(std::string aparent, std::shared_ptr<ControlVolume>& cvIn, std::shared_ptr<ControlVolume>& cvOut) {
	this->cvIn = cvIn;
	this->cvOut = cvOut;
}

void Valve::calculatemf() {
	double mf = knu * nomA * sgn(cvIn->p - cvOut->p) * sqrt(2 * cvIn->rho * abs(cvIn->p - cvOut->p));

	// cvOut->h = cvIn->h
}

// System constructor
System::System(int pipeCVnum) {
	pipe = std::make_unique<Pipe>("noparent", 0, pipeCVnum);
	pipe->constructStateVecs();
	//Fluid = shared_ptr <AbstractState>(AbstractState::factory("BICUBIC&HEOS", fluid));

	pressures = std::make_unique<std::vector<double>>();
	enthalpies = std::make_unique<std::vector<double>>();
	fvals = std::make_unique<std::vector<double>>();
	rhoM = std::make_unique<std::vector<std::vector<double>>>();
	derrhodpM = std::make_unique<std::vector<std::vector<double>>>();
	derrhodhM = std::make_unique<std::vector<std::vector<double>>>();
	qualityM = std::make_unique<std::vector<std::vector<double>>>();

}

void System::initialize(double dtime, double cvL, double cvA, double dHf, double hL, double hR, double mFin, double p, double h, double pL, double pR, double alpha) {
	std::cout << "Initialization\n";

	dt = dtime;
	pipe->dt = dtime;

	pipe->cvL = cvL;
	pipe->cvA = cvA;
	pipe->cvV = cvL * cvA;

	// set boundary condition at the pipe inlet
	pipe->massFlowIn = mFin;
	pipe->cvStart->h = hL;
	pipe->cvEnd->h = hR;
	pipe->cvStart->hOld = hL;
	pipe->cvEnd->hOld = hR;
	pipe->time = &time;
	pipe->cvStart->p = pL;
	pipe->cvEnd->p = pR;
	pipe->cvStart->pOld = pL;
	pipe->cvEnd->pOld = pR;
	pipe->cvStart->velocity[0] = 10.0;
	pipe->cvStart->velocity[1] = -10.0;
	pipe->cvEnd->velocity[0] = 81.0;
	pipe->cvStart->velocityOld[0] = 10.0;
	pipe->cvStart->velocityOld[1] = -10.0;
	pipe->cvEnd->velocityOld[0] = 81.0;
	std::cout << "pL: " << pL << ", hL: " << hL << std::endl;
	//Fluid->update(HmassP_INPUTS, hL, pL);
	//std::cout << "Fluid->rhomass(): " << Fluid->rhomass() << "\n\n";
	//pipe->cvStart->rho = Fluid->rhomass();
	//Fluid->update(HmassP_INPUTS, hR, pR);
	pipe->cvStart->rho = 500;
	//pipe->cvEnd->rho = Fluid->rhomass();
	pipe->cvEnd->rho = 200;
	//pipe->alpha = alpha * (pipe->cvV / pipe->cvA) / (4 * sqrt(pipe->cvA / PI));
	pipe->alpha = alpha * pipe->cvL / (4 * sqrt(pipe->cvA / PI));

	readPressEnth(*pressures, *enthalpies);
	readData(*pressures, *enthalpies, *fvals, *rhoM, "rho.txt");
	readData(*pressures, *enthalpies, *fvals, *derrhodpM, "derrhodp.txt");
	readData(*pressures, *enthalpies, *fvals, *derrhodhM, "derrhodh.txt");
	readData(*pressures, *enthalpies, *fvals, *qualityM, "quality.txt");

	rhoInterp = std::make_unique<BilinInterp>(*pressures, *enthalpies, *rhoM);
	derrhodpInterp = std::make_unique<BilinInterp>(*pressures, *enthalpies, *derrhodpM);
	derrhodhInterp = std::make_unique<BilinInterp>(*pressures, *enthalpies, *derrhodhM);
	qualityInterp = std::make_unique<BilinInterp>(*pressures, *enthalpies, *qualityM);


	std::vector<double> pStartingVals = {
		774485, 773663, 772791, 771906, 771013, 770118, 769222, 768320, 767411, 766494,
		765572, 764648, 763720, 762783, 761838, 760885, 759928, 758967, 757997, 757018,
		756029, 755035, 754037, 753030, 752012, 750983, 749949, 748911, 747863, 746803,
		745733, 744658, 743576, 742484, 741380, 740268, 739151, 738025, 736887, 735739,
		734585, 733425, 732254, 731071, 729881, 728687, 727483, 726266, 725042, 723814,
		722576, 721325, 720067, 718804, 717531, 716245, 714951, 713653, 712343, 711019,
		709688, 708351, 707001, 705637, 704266, 702885, 701489, 700082, 698665, 697236,
		695789, 694332, 692864, 691377, 689876, 688364, 686834, 685285, 683723, 682144,
		680544, 678928, 677295, 675639, 673965, 672274, 670557, 668822, 667066, 665285,
		663484, 661658, 659808, 657937, 656036, 654113, 652166, 650190, 648189, 646157,
		644098, 642013, 639895, 637749, 635569, 633359, 631114, 628836, 626524, 624175,
		621789, 619364, 616898, 614390, 611837, 609240, 606594, 603899, 601151, 598349,
		595490, 592569, 589586, 586532, 583407, 580205, 576918, 573547, 570080, 566508,
		562830, 559035, 555107, 551032, 546805, 542411, 537825, 533023, 527978, 522656,
		517012, 510993, 504540, 497560, 489921, 481440, 471851, 460722, 447282, 305697 };

	std::vector<double> vStartingVals ={
		9.95983, 9.98711, 10.0309, 10.0778, 10.1258, 10.1748, 10.2225, 10.2707, 10.3197, 10.3695,
		10.4202, 10.4708, 10.5211, 10.572, 10.6239, 10.6768, 10.7305, 10.7832, 10.8366, 10.891,
		10.9465, 11.0032, 11.0588, 11.115, 11.1724, 11.231, 11.2908, 11.3495, 11.409, 11.4698,
		11.5319, 11.5947, 11.6568, 11.72, 11.7845, 11.8505, 11.9161, 11.982, 12.0492, 12.1179,
		12.1874, 12.2563, 12.3263, 12.3978, 12.4709, 12.543, 12.616, 12.6906, 12.7668, 12.8424,
		12.9186, 12.9964, 13.0759, 13.155, 13.2347, 13.316, 13.3991, 13.4817, 13.5651, 13.6502,
		13.7374, 13.8234, 13.9109, 14.0004, 14.0912, 14.1817, 14.2739, 14.3683, 14.463, 14.5585,
		14.6562, 14.7559, 14.8552, 14.9565, 15.0606, 15.1648, 15.2704, 15.3788, 15.4886, 15.5992,
		15.7127, 15.8284, 15.9445, 16.0635, 16.1854, 16.3077, 16.4331, 16.5615, 16.6906, 16.8233,
		16.9585, 17.0952, 17.236, 17.3786, 17.5238, 17.6737, 17.824, 17.9787, 18.1367, 18.2971,
		18.4627, 18.6296, 18.8014, 18.9767, 19.1555, 19.3395, 19.5259, 19.719, 19.914, 20.1156,
		20.3206, 20.5319, 20.7477, 20.9699, 21.1972, 21.4315, 21.6713, 21.9192, 22.1727, 22.4359,
		22.7047, 22.984, 23.2708, 23.5678, 23.8761, 24.1939, 24.525, 24.8684, 25.2247, 25.5974,
		25.9866, 26.3919, 26.8172, 27.265, 27.7372, 28.2339, 28.7597, 29.3192, 29.9166, 30.5576,
		31.2489, 31.9997, 32.8214, 33.7243, 34.7317, 35.8715, 37.1844, 38.7307, 40.6164, 43.0302, 84.3758 };


	double dpStart = (pL - pR) / pipe->numCV;
	double duStart = (pipe->cvEnd->velocity[0] - pipe->cvStart->velocity[0]) / (pipe->numCV + 2);

	for (int i = 0; i < pipe->numCV; i++) {
		std::shared_ptr<ControlVolume> cv = pipe->controlVolumes[i];
		cv->deltaHflow.at(0) = dHf;
		//cv->p = pL - i*dpStart;
		//cv->p = p;
		cv->p = pStartingVals[i];
		//cv->h = hStartingVals[i];
		cv->h = h;
		//cv->velocity[0] = - pipe->cvStart->velocity[1] + duStart * i;
		cv->velocity[0] = vStartingVals[i];
		if (i == pipe->numCV - 1) {
			cv->velocity[1] = -pipe->cvEnd->velocity[0];
		}
		else {
			cv->velocity[1] = -vStartingVals[i + 1];
		}
		cv->pOld = cv->p;
		cv->hOld = cv->h;
		cv->velocityOld[0] = cv->velocity[0];
		cv->velocityOld[1] = cv->velocity[1];
		//std::cout << cv->u << "\n";
	}
	pipe->cvStart->velocityOld[1] = -pipe->controlVolumes[0]->velocity[0];
	pipe->cvEnd->velocityOld[0] = -pipe->controlVolumes[pipe->numCV-1]->velocity[1];
	pipe->cvStart->velocity[1] = pipe->cvStart->velocityOld[1];
	pipe->cvEnd->velocity[0] = pipe->cvEnd->velocityOld[0];
	guessProperties();
	calculateFlows2();
}

void System::guessProperties() {

	pipe->cvStart->rho = rhoInterp->interp(pipe->cvStart->p, pipe->cvStart->h);
	pipe->cvStart->derrhodp = derrhodpInterp->interp(pipe->cvStart->p, pipe->cvStart->h);
	pipe->cvStart->derrhodh = derrhodhInterp->interp(pipe->cvStart->p, pipe->cvStart->h);

	//pipe->controlVolumes[pipe->numCV - 1]->p = 303000;

	//std::ofstream outFile;
	//outFile.open("results/solving.txt", std::ios_base::app);
	//outFile << "Guess properties ..." << std::endl;

	double habs{ 0.0 };

	for (int i = 0; i < pipe->numCV; i++) {
		std::shared_ptr<ControlVolume> cv = pipe->controlVolumes[i];

		habs = cv->h - pow((cv->velocity[0]/2 + cv->velocity[1]/2), 2) / 2;

		if (cv->p < 1000) cv->p = 1000;
		if (cv->p > 10000000) cv->p = 10000000;
		if (cv->h < 80000) cv->h = 80000;
		if (cv->h > 800000) cv->h = 800000;

		cv->rho = rhoInterp->interp(cv->p, cv->h);
		cv->derrhodp = derrhodpInterp->interp(cv->p, cv->h);
		cv->derrhodh = derrhodhInterp->interp(cv->p, cv->h);
		cv->x = qualityInterp->interp(cv->p, cv->h);

		//outFile << "p: " << cv->p << std::endl;
		//outFile << "h: " << cv->h << std::endl;
		//outFile << "rho: " << cv->rho << std::endl;
		//outFile << "derrhodp: " << cv->derrhodp << std::endl;
		//outFile << "derrhodh: " << cv->derrhodh << std::endl;
	}
	//outFile.close();
}

void System::calculateFlows() {

	std::shared_ptr<ControlVolume> cv;
	std::shared_ptr<ControlVolume> cvLeft;

	double dp, dp1;
	double mfs, mf;
	double v;
	double rho;
	
	dp = pipe->controlVolumes[0]->p - pipe->cvStart->p + pipe->controlVolumes[0]->rho * GRAVITY * pipe->controlVolumes[0]->dz;
	//dp = pipe->controlVolumes[0]->p - pipe->cvStart->p +
	//pipe->controlVolumes[0]->rho * pow(pipe->controlVolumes[0]->velocity[1], 2) - pipe->cvStart->rho*pow(pipe->controlVolumes[0]->velocity[0],2);

	if (dp >= 0) {
		pipe->controlVolumes[0]->directions[0] = -1;
		pipe->controlVolumes[0]->upstream[0] = pipe->controlVolumes[0];
		rho = pipe->controlVolumes[0]->rho;
	}
	else {
		pipe->controlVolumes[0]->directions[0] = 1;
		pipe->controlVolumes[0]->upstream[0] = pipe->cvStart;
		rho = pipe->cvStart->rho;
	}

	mf = abs(pipe->cvA * sqrt(rho * abs(dp) / pipe->alpha));
	v = mf / (rho * pipe->cvA);
	pipe->controlVolumes[0]->massFlow[0] = mf * pipe->controlVolumes[0]->directions[0];
	pipe->controlVolumes[0]->velocity[0] = v * pipe->controlVolumes[0]->directions[0];
 	
	for (int i = 1; i < pipe->numCV; i++) {
		cv = pipe->controlVolumes[i];
		cvLeft = pipe->controlVolumes[i - 1];

		dp = cv->p - cvLeft->p; // +cv->rho * pow(cv->velocity[1], 2) - cvLeft->rho * pow(cv->velocity[0], 2) + cv->rho * GRAVITY * cv->dz;

		if (dp >= 0) {
			cv->directions[0] = -1;
			cvLeft->directions[1] = 1;
			cv->upstream[0] = cv;
			cvLeft->upstream[1] = cv;
			rho = cv->rho;
		}
		else {
			cv->directions[0] = 1;
			cvLeft->directions[1] = -1;
			cv->upstream[0] = cvLeft;
			cvLeft->upstream[1] = cvLeft;
			rho = cvLeft->rho;
		}

		mf = abs(pipe->cvA * sqrt(rho * abs(dp) / pipe->alpha));
		v = mf / (rho * pipe->cvA);

		cv->massFlow[0] = mf * cv->directions[0];
		cv->velocity[0] = v * cv->directions[0];
		cvLeft->massFlow[1] = mf * cvLeft->directions[1];
		cvLeft->velocity[1] = v * cvLeft->directions[1];
	}

	dp = pipe->cvEnd->p - pipe->controlVolumes[pipe->numCV - 1]->p; // +5 * 49 * 49;
	// +pipe->cvEnd->rho * pow(pipe->cvEnd->velocity[1], 2) - pipe->controlVolumes[pipe->numCV - 1]->rho * pow(pipe->controlVolumes[pipe->numCV - 1]->velocity[1], 2);

	if (dp >= 0) {
		pipe->controlVolumes[pipe->numCV - 1]->directions[1] = 1;
		pipe->controlVolumes[pipe->numCV - 1]->upstream[1] = pipe->cvEnd;
		rho = pipe->cvEnd->rho;
	}
	else {
		pipe->controlVolumes[pipe->numCV - 1]->directions[1] = -1;
		pipe->controlVolumes[pipe->numCV - 1]->upstream[1] = pipe->controlVolumes[pipe->numCV - 1];
		rho = pipe->controlVolumes[pipe->numCV - 1]->rho;
	}
	mf = abs(pipe->cvA * sqrt(rho * abs(dp) / pipe->alpha));
	v = mf / (rho * pipe->cvA);
	pipe->controlVolumes[pipe->numCV - 1]->massFlow[1] = mf * pipe->controlVolumes[pipe->numCV - 1]->directions[1];
	pipe->controlVolumes[pipe->numCV - 1]->velocity[1] = v * pipe->controlVolumes[pipe->numCV - 1]->directions[1];
	pipe->controlVolumes[pipe->numCV - 1]->velocity[1] = pipe->cvEnd->velocity[0] * pipe->controlVolumes[pipe->numCV - 1]->directions[1];

	for (int i = 0; i < pipe->numCV; i++) {
		cv = pipe->controlVolumes[i];

		if (cv->directions[0] == 1 && cv->directions[1] == 1) {
			cv->flowCase = 1;
			cv->mj = 0;
			cv->mfdiff = -1 * (cv->massFlow[0] + cv->massFlow[1]);
		}
		if (cv->directions[0] == 1 && cv->directions[1] == -1) {
			cv->flowCase = 2;
			cv->mj = cv->massFlow[1];
			cv->mfdiff = -1 * cv->massFlow[0];
		}
		if (cv->directions[0] == -1 && cv->directions[1] == 1) {
			cv->flowCase = 3;
			cv->mj = cv->massFlow[0];
			cv->mfdiff = -1 * cv->massFlow[1];
		}
		if (cv->directions[0] == -1 && cv->directions[1] == -1) {
			cv->flowCase = 4;
			cv->mj = cv->massFlow[0] + cv->massFlow[1];
			cv->mfdiff = 0;
		}
	}
	//std::ofstream outFile;
	//outFile.open("results/solving.txt", std::ios_base::app);
	//outFile << "massFlows:\n";
	//for (int i = 0; i < pipe->numCV; i++) {
	//	cv = pipe->controlVolumes[i];
	//	outFile << cv->massFlow[0] << "\t";
	//}
	//outFile << "\n";
	//outFile.close();

}

//void System::calculateFlows2() {
//
//	std::shared_ptr<ControlVolume> cv;
//	std::shared_ptr<ControlVolume> cvLeft;
//	std::shared_ptr<ControlVolume> cvRight;
//	std::shared_ptr<ControlVolume> cvFirst = pipe->controlVolumes[0];
//	std::shared_ptr<ControlVolume> cvLast = pipe->controlVolumes[pipe->numCV - 1];
//
//	double mf = pipe->massFlowIn;
//	//cvFirst->massFlow[0] = mf;// pipe->cvA* pipe->cvStart->rho* cvFirst->velocity[0];
//	//cvFirst->velocity[0] = mf / (pipe->cvA * pipe->cvStart->rho);
//	//cvFirst->velocityOld[0] = mf / (pipe->cvA * pipe->cvStart->rho);
//	cvFirst->massFlow[0] = pipe->cvA * pipe->cvStart->rho * cvFirst->velocity[0];
//	cvFirst->directions[0] = (cvFirst->velocity[0] > 0) ? 1 : -1;
//	pipe->cvStart->directions[1] = -cvFirst->directions[0];
//	pipe->cvStart->velocity[1] = -cvFirst->velocity[0];
//	pipe->cvStart->velocityOld[1] = -cvFirst->velocityOld[0];
//	pipe->cvStart->massFlow[1] = -cvFirst->massFlow[0];
//	cvFirst->upstream[0] = (cvFirst->velocity[0] > 0) ? pipe->cvStart : cvFirst;
//	pipe->cvStart->upstream[1] = (cvFirst->velocity[0] > 0) ? pipe->cvStart : cvFirst;
//
//	pipe->cvEnd->velocity[0] =
//		(pipe->alpha * pipe->controlVolumes[pipe->numCV - 2]->rho * pow(cvLast->velocityOld[0],2) +
//			cvLast->pOld - pipe->cvEnd->pOld - 0.5 *(cvLast->rho + pipe->controlVolumes[pipe->numCV - 2]->rho) * cvLast->velocityOld[0] -
//			0.5 * pipe->controlVolumes[pipe->numCV - 2]->rho * pipe->controlVolumes[pipe->numCV - 2]->velocityOld[0])/(0.5 * cvLast->rho);
//	double mfOut = pipe->cvEnd->velocity[0] * pipe->cvA * cvLast->rho;
//
//
//	//pipe->cvEnd->velocity[0] = mf / (pipe->cvA * cvLast->rho);
//	//pipe->cvEnd->velocityOld[0] = mf / (pipe->cvA * cvLast->rho);
//	pipe->cvEnd->velocityOld[0] = pipe->cvEnd->velocity[0];
//	pipe->cvEnd->directions[0] = 1;
//	pipe->cvEnd->massFlow[0] = mfOut;
//	cvLast->directions[1] = -1;
//	cvLast->velocity[1] = -pipe->cvEnd->velocity[0];
//	cvLast->velocityOld[1] = -pipe->cvEnd->velocity[0];
//	cvLast->massFlow[1] = -mfOut;
//	pipe->cvEnd->upstream[0] = cvLast;
//	cvLast->upstream[1] = cvLast;
//
//	for (int i = 1; i < pipe->numCV; i++) {
//		cv = pipe->controlVolumes[i];
//		cvLeft = (i == 0) ? pipe->cvStart : pipe->controlVolumes[i - 1];
//		cvRight = (i == pipe->numCV - 1) ? pipe->cvEnd : pipe->controlVolumes[i + 1];
//
//		if (cv->velocity[0] <= 0) {
//			cv->directions[0] = -1;
//			cvLeft->directions[1] = 1;
//			cv->upstream[0] = cv;
//			cvLeft->upstream[1] = cv;
//		}
//		else {
//			cv->directions[0] = 1;
//			cvLeft->directions[1] = -1;
//			cv->upstream[0] = cvLeft;
//			cvLeft->upstream[1] = cvLeft;
//		}
//		cv->massFlow[0] = pipe->cvA * cv->velocity[0] * cv->upstream[0]->rho;
//		cvLeft->velocity[1] = -cv->velocity[0];
//		cvLeft->velocityOld[1] = -cv->velocityOld[0];
//		cvLeft->massFlow[1] = -cv->massFlow[0];
//	}
//
//	for (int i = 0; i < pipe->numCV; i++) {
//		cv = pipe->controlVolumes[i];
//
//		if (cv->directions[0] == 1 && cv->directions[1] == 1) {
//			cv->flowCase = 1;
//			cv->mj = 0;
//			cv->mfdiff = -1 * (cv->massFlow[0] + cv->massFlow[1]);
//		}
//		if (cv->directions[0] == 1 && cv->directions[1] == -1) {
//			cv->flowCase = 2;
//			cv->mj = cv->massFlow[1];
//			cv->mfdiff = -1 * cv->massFlow[0];
//		}
//		if (cv->directions[0] == -1 && cv->directions[1] == 1) {
//			cv->flowCase = 3;
//			cv->mj = cv->massFlow[0];
//			cv->mfdiff = -1 * cv->massFlow[1];
//		}
//		if (cv->directions[0] == -1 && cv->directions[1] == -1) {
//			cv->flowCase = 4;
//			cv->mj = cv->massFlow[0] + cv->massFlow[1];
//			cv->mfdiff = 0;
//		}
//	}
//
//}

void System::calculateFlows2() {

	std::shared_ptr<ControlVolume> cv;
	std::shared_ptr<ControlVolume> cvLeft;
	std::shared_ptr<ControlVolume> cvRight;
	std::shared_ptr<ControlVolume> cvFirst = pipe->controlVolumes[0];
	std::shared_ptr<ControlVolume> cvLast = pipe->controlVolumes[pipe->numCV - 1];

	double mf = pipe->massFlowIn;
	//cvFirst->massFlow[0] = mf;// pipe->cvA* pipe->cvStart->rho* cvFirst->velocity[0];
	//cvFirst->velocity[0] = mf / (pipe->cvA * pipe->cvStart->rho);
	//cvFirst->velocityOld[0] = mf / (pipe->cvA * pipe->cvStart->rho);
	cvFirst->massFlow[0] = pipe->cvA * pipe->cvStart->rho * cvFirst->velocity[0];
	cvFirst->directions[0] = (cvFirst->velocity[0] > 0) ? 1 : -1;
	pipe->cvStart->directions[1] = -cvFirst->directions[0];
	pipe->cvStart->velocity[1] = -cvFirst->velocity[0];
	pipe->cvStart->velocityOld[1] = -cvFirst->velocityOld[0];
	pipe->cvStart->massFlow[1] = -cvFirst->massFlow[0];
	cvFirst->upstream[0] = (cvFirst->velocity[0] > 0) ? pipe->cvStart : cvFirst;
	pipe->cvStart->upstream[1] = (cvFirst->velocity[0] > 0) ? pipe->cvStart : cvFirst;

	//pipe->cvEnd->velocity[0] =
	//	(pipe->alpha * pipe->controlVolumes[pipe->numCV - 2]->rho * pow(cvLast->velocityOld[0], 2) +
	//		cvLast->pOld - pipe->cvEnd->pOld - 0.5 * (cvLast->rho + pipe->controlVolumes[pipe->numCV - 2]->rho) * cvLast->velocityOld[0] -
	//		0.5 * pipe->controlVolumes[pipe->numCV - 2]->rho * pipe->controlVolumes[pipe->numCV - 2]->velocityOld[0]) / (0.5 * cvLast->rho);
	//double mfOut = pipe->cvEnd->velocity[0] * pipe->cvA * cvLast->rho;

	//pipe->cvEnd->velocity[0] = cvFirst->massFlow[0] / (pipe->cvA * pipe->controlVolumes[pipe->numCV - 1]->rho);
	pipe->cvEnd->velocity[0] = pipe->controlVolumes[pipe->numCV - 2]->rho * pipe->controlVolumes[pipe->numCV - 1]->velocity[0] / (pipe->controlVolumes[pipe->numCV - 1]->rho);
	pipe->cvEnd->velocityOld[0] = pipe->cvEnd->velocity[0];
	pipe->controlVolumes[pipe->numCV - 1]->velocity[1] = -pipe->cvEnd->velocity[0];
	pipe->controlVolumes[pipe->numCV - 1]->velocityOld[1] = -pipe->cvEnd->velocity[0];
	//pipe->cvEnd->massFlow[0] = cvFirst->massFlow[0];
	//pipe->controlVolumes[pipe->numCV - 1]->massFlow[1] = -cvFirst->massFlow[0];


	//pipe->cvEnd->velocity[0] = mf / (pipe->cvA * cvLast->rho);
	//pipe->cvEnd->velocityOld[0] = mf / (pipe->cvA * cvLast->rho);
	//pipe->cvEnd->velocityOld[0] = pipe->cvEnd->velocity[0];
	if (pipe->cvEnd->velocity[0] >= 0) {
		pipe->cvEnd->directions[0] = 1;

	}
	//pipe->cvEnd->directions[0] = 1;
	//pipe->cvEnd->massFlow[0] = mfOut;
	cvLast->velocity[1] = -pipe->cvEnd->velocity[0];
	if (cvLast->velocity[1] <= 0) {
		cvLast->directions[1] = -1;
	}
	//cvLast->directions[1] = -1;
	//cvLast->velocityOld[1] = -pipe->cvEnd->velocity[0];
	//cvLast->massFlow[1] = -mfOut;
	pipe->cvEnd->upstream[0] = cvLast;
	cvLast->upstream[1] = cvLast;

	for (int i = 1; i < pipe->numCV; i++) {
		cv = pipe->controlVolumes[i];
		cvLeft = (i == 0) ? pipe->cvStart : pipe->controlVolumes[i - 1];
		cvRight = (i == pipe->numCV - 1) ? pipe->cvEnd : pipe->controlVolumes[i + 1];

		if (cv->velocity[0] <= 0) {
			cv->directions[0] = -1;
			cvLeft->directions[1] = 1;
			cv->upstream[0] = cv;
			cvLeft->upstream[1] = cv;
		}
		else {
			cv->directions[0] = 1;
			cvLeft->directions[1] = -1;
			cv->upstream[0] = cvLeft;
			cvLeft->upstream[1] = cvLeft;
		}
		cv->massFlow[0] = pipe->cvA * cv->velocity[0] * cv->upstream[0]->rho;
		//cvLeft->velocity[1] = -cv->velocity[0];
		//cvLeft->velocityOld[1] = -cv->velocityOld[0];
		//cvLeft->massFlow[1] = -cv->massFlow[0];
	}

	for (int i = 0; i < pipe->numCV; i++) {
		cv = pipe->controlVolumes[i];

		if (cv->directions[0] == 1 && cv->directions[1] == 1) {
			cv->flowCase = 1;
			cv->mj = 0;
			cv->mfdiff = -1 * (cv->massFlow[0] + cv->massFlow[1]);
		}
		if (cv->directions[0] == 1 && cv->directions[1] == -1) {
			cv->flowCase = 2;
			cv->mj = cv->massFlow[1];
			cv->mfdiff = -1 * cv->massFlow[0];
		}
		if (cv->directions[0] == -1 && cv->directions[1] == 1) {
			cv->flowCase = 3;
			cv->mj = cv->massFlow[0];
			cv->mfdiff = -1 * cv->massFlow[1];
		}
		if (cv->directions[0] == -1 && cv->directions[1] == -1) {
			cv->flowCase = 4;
			cv->mj = cv->massFlow[0] + cv->massFlow[1];
			cv->mfdiff = 0;
		}
	}

}