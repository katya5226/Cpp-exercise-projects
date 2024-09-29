#include "Csystem.h"

using namespace std;


void mnewt(int ntrial, std::unique_ptr<System>& system, double tolx, double tolf) {
	int i, n = system->pipe->numvar * system->pipe->numCV;
	double errx, errf;
	double* d = new double(1.0);

	vector<int> indx(n, 0);
	vector<double> p = vector<double>(n, 0.0);

	for (int k = 0; k < ntrial; k++) {

		system->pipe->calcJacobi();
		system->pipe->calcRHS();

		errf = 0.0;
		for (i = 0; i < n; i++) errf += fabs(system->pipe->rhs[i]);
		if (errf <= tolf) {
			delete d;
			return;
		}
		for (i = 0; i < n; i++) {
			p[i] = -system->pipe->rhs[i];
			system->pipe->rhs[i] *= -1;
		}
		ludcmp(system->pipe->jacobi, indx, d, n);
		solve(system->pipe->jacobi, system->pipe->rhs, p, indx, n);
		errx = 0.0;
		for (i = 0; i < n; i++) {
			errx += fabs(p[i]);
			*(system->pipe->stateVec[i]) += p[i];
		}
		if (errx <= tolx) {
			delete d;
			return;
		}
		system->guessProperties();
		system->calculateFlows2();
	}
	delete d;
	return;
}

void ludcmp(vector<vector<double>>& a, vector<int>& indx, double* d, int n) {

	const double TINY = 1.0e-40;
	int i, imax = 0, j, k;
	double big, dum, sum, temp;

	vector<double> vv = vector<double>(n, 0.0);

	*d = 1.0;
	for (i = 0; i < n; i++) {
		big = 0.0;
		for (j = 0; j < n; j++)
			if ((temp = fabs(a[i][j])) > big) big = temp;
		if (big == 0.0) throw "Singular matrix in routine ludcmp";
		vv[i] = 1.0 / big;
	}
	for (k = 0; k < n; k++) {
		big = 0.0;
		for (i = k; i < n; i++) {
			temp = vv[i] * abs(a[i][k]);
			if (temp > big) {
				big = temp;
				imax = i;
			}
		}
		if (k != imax) {
			for (j = 0; j < n; j++) {
				temp = a[imax][j];
				a[imax][j] = a[k][j];
				a[k][j] = temp;
			}
			*d = -(*d);
			vv[imax] = vv[k];
		}
		indx[k] = imax;
		if (a[k][k] == 0.0) a[k][k] = TINY;
		for (i = k + 1; i < n; i++) {
			temp = a[i][k] /= a[k][k];
			for (j = k + 1; j < n; j++)
				a[i][j] -= temp * a[k][j];
		}
	}

}


void solve(vector<vector<double>>& lu, const vector<double>& b, vector<double>& x, vector<int>& indx, int n) {

	int i, ii = 0, ip, j;
	double sum;
	if (b.size() != n || x.size() != n)
		throw("LUdcmp::solve bad sizes");
	for (i = 0; i < n; i++) x[i] = b[i];

	for (i = 0; i < n; i++) {
		ip = indx[i];
		sum = x[ip];
		x[ip] = x[i];
		if (ii != 0)
			for (j = ii - 1; j < i; j++) sum -= lu[i][j] * x[j];
		else if (sum != 0.0) ii = i + 1;
		x[i] = sum;
	}
	for (i = n - 1; i >= 0; i--) {
		sum = x[i];
		for (j = i + 1; j < n; j++) sum -= lu[i][j] * x[j];
		x[i] = sum / lu[i][i];
	}

}

void solveExplicit2(std::unique_ptr<System>& system) {

	double V = system->pipe->cvV;
	double L = system->pipe->cvL;
	double uL, uR, rhoL, rhoR = 0.0;
	double C1, C2, C3, C4, D1, D2, RHS1, RHS2, RHS3, dpdt, dhdt, dudt = 1.0;
	double dp, dh, du, du1 = 0.0;
	int n = system->pipe->numCV;

	//system->pipe->cvEnd->velocityOld[0] = 0.1926 / (system->pipe->cvA * system->pipe->controlVolumes[n - 1]->rho);
	//system->pipe->controlVolumes[n - 1]->velocityOld[1] = -system->pipe->cvEnd->velocityOld[0];
	std::shared_ptr<ControlVolume> cvLast = system->pipe->controlVolumes[n - 1];

	for (int i = 0; i < n; i++) {
		std::shared_ptr<ControlVolume> cv = system->pipe->controlVolumes[i];
		std::shared_ptr<ControlVolume> cvLeft = (i == 0) ? system->pipe->cvStart : system->pipe->controlVolumes[i - 1];
		std::shared_ptr<ControlVolume> cvLeftLeft = (i > 1) ? system->pipe->controlVolumes[i - 2] : system->pipe->cvStart;
		std::shared_ptr<ControlVolume> cvRight = (i == n - 1) ? system->pipe->cvEnd : system->pipe->controlVolumes[i + 1];
		std::shared_ptr<ControlVolume> cvRightRight = (i < n - 2) ? system->pipe->controlVolumes[i + 1] : system->pipe->cvEnd;

		//cv->velocityOld[0] = 0.1926 / (system->pipe->cvA * cvLeft->rho);
		//cvLeft->velocityOld[1] = -cv->velocityOld[0];

		RHS1 = system->pipe->cvA * (cv->upstream[0]->rho * cv->velocityOld[0] + cv->upstream[1]->rho * cv->velocityOld[1]);
		RHS3 = system->pipe->cvA * (cv->upstream[0]->hOld * cv->velocityOld[0] * cv->upstream[0]->rho +
			cv->upstream[1]->hOld * cv->velocityOld[1] * cv->upstream[1]->rho + cv->deltaHflow[0]);
		C1 = cv->rho / cv->derrhodh + cv->hOld;
		C2 = V * (C1 * cv->derrhodp - cv->derrhodp * cv->hOld + 1);
		D1 = RHS3 - (cv->rho / cv->derrhodh) * RHS1;
		D2 = V * cv->derrhodp * (cv->hOld - cv->rho / cv->derrhodh);
		dpdt = (C1 * RHS1 - RHS3) / C2;
		//dpdt = D1 / D2;
		dhdt = (RHS1 - V * cv->derrhodp * dpdt) / (V * cv->derrhodh);
		//dhdt = 0.0;
		uL = 0.5 * (cvLeft->velocityOld[0] + cv->velocityOld[0]);
		uR = 0.5 * (cv->velocityOld[0] + cvRight->velocityOld[0]);
		rhoL = (uL > 0) ? 0.5 * (cvLeftLeft->rho + cvLeft->rho) : 0.5 * (cvLeft->rho + cv->rho);
		rhoR = 0.5 * (cvLeft->rho + cv->rho);
		C3 = rhoL * abs(uL) * uL - rhoR * abs(uR) * uR -
			system->pipe->alpha * cv->upstream[0]->rho * cv->velocityOld[0] * cv->velocityOld[0];// -
			//system->pipe->alpha * cv->upstream[0]->rho * cv->velocityOld[0] * cv->velocityOld[0];
		//std::cout << cv->index << "\t" << C3 << "\n";
		/*C3 = cv->upstream[0]->rho * abs(cv->velocityOld[0]) * cv->velocityOld[0] +
			cv->upstream[1]->rho * abs(cv->velocityOld[1]) * cv->velocityOld[1];*///-
			//abs(cv->velocityOld[0]) * (cv->upstream[0]->rho * cv->velocityOld[0] +
			//	cv->upstream[1]->rho * cv->velocityOld[1] + cvLeft->pOld - cv->pOld); //-
				//system->pipe->alpha * cv->upstream[0]->rho * cv->velocityOld[0] * cv->velocityOld[0]);

		C4 = (cv->velocityOld[0] / (L * cv->upstream[0]->rho)) * (cv->upstream[0]->derrhodp * dpdt + cv->upstream[0]->derrhodh * dhdt);
		dudt = (1 / (L * cv->upstream[0]->rho)) * (C3 + cvLeft->pOld - cv->pOld) - C4;

		dp = dpdt * system->dt;
		dh = dhdt * system->dt;
		du = dudt * system->dt;

		//std::cout << C3 << "\t" << cvLeft->pOld - cv->pOld << "\t" << C4 << "\t" << cv->velocity[0] << "\t" << du << "\n";
		//std::cout << cv->derrhodp * dpdt + cv->derrhodh * dhdt << "\n";

		cv->p += dp;
		cv->h += dh;
		//cv->velocity[0] = (i == 0) ? cv->velocity[0] : cv->velocity[0] + du;
		cv->velocity[0] = cv->velocity[0] + du;
		cvLeft->velocity[1] = -cv->velocity[0];
		cv->massFlow[0] = system->pipe->cvA * cv->upstream[0]->rho * cv->velocity[0];
		cvLeft->massFlow[1] = -cv->massFlow[0];

		//RHS1 = system->pipe->cvA * (cv->upstream[0]->rho * cv->velocity[0] + cv->upstream[1]->rho * cv->velocity[1]);
		//RHS3 = system->pipe->cvA * (cv->upstream[0]->hOld * cv->velocity[0] * cv->upstream[0]->rho +
		//	cv->upstream[1]->hOld * cv->velocity[1] * cv->upstream[1]->rho + cv->deltaHflow[0]);
		//C1 = cv->rho / cv->derrhodh + cv->hOld;
		//C2 = V * (C1 * cv->derrhodp - cv->derrhodp * cv->hOld + 1);
		//dpdt = (C1 * RHS1 - RHS3) / C2;
		//dhdt = (RHS1 - V * cv->derrhodp * dpdt) / (V * cv->derrhodh);

		//dp = dpdt * system->dt;
		//dh = dhdt * system->dt;
		//cv->p += dp;
		//cv->h += dh;

		//system->pipe->controlVolumes[n-1]->p = 315000;
		//system->pipe->controlVolumes[0]->p = 770000;
		//system->pipe->controlVolumes[n - 1]->pOld = 315000;

		if (cv->p < 1000) cv->p = 1000;
		if (cv->p > 10000000) cv->p = 10000000;
		if (cv->h < 80000) cv->h = 80000;
		if (cv->h > 800000) cv->h = 800000;

	}
	system->pipe->cvEnd->velocity[0] = system->pipe->massFlowIn / (system->pipe->cvA * system->pipe->controlVolumes[n - 1]->rho);
	system->pipe->controlVolumes[n - 1]->velocity[1] = -system->pipe->cvEnd->velocity[0];
	system->pipe->cvEnd->massFlow[0] = system->pipe->massFlowIn;
	system->pipe->controlVolumes[n - 1]->massFlow[1] = -system->pipe->massFlowIn;
	//std::cout << "\n\n";



	//system->pipe->cvEnd->velocity[0] =
	//	(system->pipe->alpha * system->pipe->controlVolumes[n - 2]->rho * pow(cvLast->velocityOld[0],2) +
	//		cvLast->pOld - system->pipe->cvEnd->pOld - 0.5 *(cvLast->rho + system->pipe->controlVolumes[n - 2]->rho) * cvLast->velocityOld[0] -
	//		0.5 * system->pipe->controlVolumes[n - 2]->rho * system->pipe->controlVolumes[n - 2]->velocityOld[0])/(0.5 * cvLast->rho);



	for (int i = 0; i < system->pipe->numCV; i++) {
		std::shared_ptr<ControlVolume> cv = system->pipe->controlVolumes[i];
		//outFile << "dp: " << cv -> dp << "\t";
		//outFile << "dh: " << cv -> dh << "\n";
	}
}