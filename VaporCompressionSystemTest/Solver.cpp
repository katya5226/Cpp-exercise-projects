#include "CSystem.h"

using namespace std;


void mnewt(int ntrial, std::unique_ptr<System>& system, double tolx, double tolf) {
	//std::ofstream outFile;
	//outFile.open("results/solving.txt", std::ios_base::app);
	//outFile << "\nStarting mnewt ...\n";
	//outFile.close();

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
		//outFile.open("results/solving.txt", std::ios_base::app);
		//outFile << "Statevec corrections:\n";
		for (i = 0; i < n; i++) {
			errx += fabs(p[i]);
			*(system->pipe->stateVec[i]) += p[i];			
			//outFile << p[i] << "\t";
		}
		//outFile << "\n";
		//outFile << "New Statevec:\n";
		//for (int i = 0; i < system->pipe->stateVec.size(); i++) {
		//	outFile << std::setprecision(6) << *system->pipe->stateVec[i] << "\t";
		//}
		//outFile << "\n";
		//std::cout << "\n";
		if (errx <= tolx) {
			delete d;
			return;
		}
		//outFile << "\n";
		//outFile.close();
		system->guessProperties();
		system->calculateFlows();
	}

	for (i = 0; i < n; i++) {
		//std::cout << *(system->pipe->stateVec[i]) << "\t";
	}
	//outFile.open("results/solving.txt", std::ios_base::app);
	//outFile << "\n";
	delete d;
	//outFile << "\nEnding mnewt ...\n";
	//outFile.close();
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

void solveExplicit(std::unique_ptr<System>& system) {
	//std::ofstream outFile;
	//outFile.open("results/solving.txt", std::ios_base::app);
	//outFile << "Explicit solving for dp and dh ...\n";

	for (int i = 0; i < system->pipe->numCV; i++) {
		std::shared_ptr<ControlVolume> cv = system->pipe->controlVolumes[i];
		cv->a = system->pipe->cvV * (cv->rho * cv->derrhodp + cv->derrhodh);

		cv->dp = -(cv->derrhodh) * (cv->upstream[0]->hOld * cv->massFlow[0] + cv->upstream[1]->hOld * cv->massFlow[1] + cv->deltaHflow[0]) * system->dt / cv->a +
			(cv->h * cv->derrhodh + cv->rho) * (cv->massFlow[0] + cv->massFlow[1]) * system->dt / cv->a;
		cv->dh = cv->derrhodp * (cv->upstream[0]->hOld * cv->massFlow[0] + cv->upstream[1]->hOld * cv->massFlow[1] + cv->deltaHflow[0]) * system->dt / cv->a -
			(cv->h * cv->derrhodp - 1) * (cv->massFlow[0] + cv->massFlow[1]) * system->dt / cv->a;

		cv->p += cv->dp;
		cv->h += cv->dh;

		if (cv->p < 1000) cv->p = 1000;
		if (cv->p > 10000000) cv->p = 10000000;
		if (cv->h < 80000) cv->h = 80000;
		if (cv->h > 800000) cv->h = 800000;

	}

	//for (int i = 0; i < system->pipe->numCV; i++) {
	//	std::shared_ptr<ControlVolume> cv = system->pipe->controlVolumes[i];
	//	outFile << "dp: " << cv -> dp << "\t";
	//	outFile << "dh: " << cv -> dh << "\n";

	//}

}