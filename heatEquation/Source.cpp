#include <iostream>
#include <fstream>
#include <vector>
#include "../../code/nr3.h"
//#include "../../code/tridag.h"
using namespace std;


void tridag(VecDoub_I& a, VecDoub_I& b, VecDoub_I& c, VecDoub_I& r, VecDoub_O& u)
{
	Int j, n = a.size();
	Doub bet;
	VecDoub gam(n);
	if (b[0] == 0.0) throw("Error 1 in tridag");
	u[0] = r[0] / (bet = b[0]);
	u[0] = 1;
	for (j = 1; j < n; j++) {
		gam[j] = c[j - 1] / bet;
		bet = b[j] - a[j] * gam[j];
		if (bet == 0.0) throw("Error 2 in tridag");
		u[j] = (r[j] - a[j] * u[j - 1]) / bet;
	}
	for (j = (n - 2); j >= 0; j--)
		if (j != 0) {
			u[j] -= gam[j + 1] * u[j + 1];
		}
		//std::cout << gam[j+1] << endl;
		//std::cout << u[j] << endl;
}


int main() {

	Doub alpha = 0.5;
	int J = 10;
	double a[10];
	double b[10];
	double c[10];
	for (int i = 0; i < J; i++) {
		a[i] = -alpha;
		b[i] = (1 + 2 * alpha);
		c[i] = -alpha;
	}

	VecDoub aa(J, a);
	VecDoub bb(J, b);
	VecDoub cc(J, c);
	VecDoub u(J);
	for (int i = 1; i < J; i++) {
		u[i] = 0;
	}
	VecDoub r(J); r[0] = 1;
	for (int i = 1; i < J; i++) {
		r[i] = 0;
	}

	ofstream myfile;
	myfile.open("solution.txt");

	for (int j = 0; j < 1000; j+=10) {

		tridag(aa, bb, cc, r, u);

		for (int i = 0; i < J; i++) {
			myfile << u[i] << '\n';
			r[i] = u[i];
			r[0] = 1;
		}
		myfile << "\n\n";
	}

	myfile.close();

	return 0;
}