#include "simulation.h"
#include <armadillo>

int main() {

	arma::mat A = arma::randu<arma::mat>(4, 5);
	arma::mat B = arma::randu<arma::mat>(4, 5);

	arma::cout << A*B.t() << std::endl;

	return 0;
}