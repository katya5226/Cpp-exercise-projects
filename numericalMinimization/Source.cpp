#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "../../code/nr3.h"
#include "../../code/amoeba.h"
#include "../../code/mins.h"
#include "../../code/mins_ndim.h"


struct ElEnergy {
	Doub operator()(VecDoub_I& x) {

		double S = 0, distance = 0;
		int i = 0, j = 0;
		int n = x.size();

		int m = n + 3;
		double* k = new double[m];
		k[0] = 0;
		k[1] = 0;
		k[2] = 0;
		for (i = 3; i <= m - 1; i++) k[i] = x[i - 3];

		for (i = 0; i <= m - 2; i = i + 2) {
			for (j = i + 2; j <= m - 1; j = j + 2) {

				distance = pow(sin(k[i + 1]) * cos(k[i]) - sin(k[j + 1]) * cos(k[j]), 2) +
					pow(sin(k[i + 1]) * sin(k[i]) - sin(k[j + 1]) * sin(k[j]), 2) +
					pow(cos(k[i + 1]) - cos(k[j + 1]), 2);

				distance = sqrt(distance);
				S = S + pow(distance, -1);
			}
		}
		cout << '\n' << S;
		return S;
	}
};

void randomCoors(const int n, Doub* c) {
	srand(time(NULL));
	double randNum;

	for (int i = 0; i < 2 * n - 3; i++) {
		randNum = (rand() % 314) * 0.01;
		c[i] = randNum;
	}
}

int main() {
	
	ElEnergy S;

	const int n = 4;
	Doub coordinates[2 * n - 3];
	randomCoors(n, coordinates);

	for (double coord : coordinates) {
		cout << coord << '\n';
	}
	
	VecDoub p(2*n-3, coordinates);
	VecDoub final;

	Powell<ElEnergy> powell(S);
	final = powell.minimize(p);

	cout << "\nRezultat:\n";

	for (int i = 0; i < 2 * n - 3; i++) {
		cout << final[i] << '\n';
	}

	return 0;
}
