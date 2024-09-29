#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include <fstream>
#include <iterator>
#include <memory>
#include <exception>
#include <chrono>

template <class T> const T& min(const T& a, const T& b) {
	return !(b < a) ? a : b;
}
template <class T> const T& max(const T& a, const T& b) {
	return !(b > a) ? a : b;
}


class BaseInterp {
public:
	int n, mm, jsav, cor, dj;
	std::vector<double> xx, yy;

	BaseInterp(std::vector<double>& x, std::vector<double>& y, int m);

	double interp(double x);

	int locate(const double);
	int hunt(const double);

	double virtual rawinterp(int jlo, double x) = 0;
	//double rawinterp(int j, double x);

};


class LinInterp : public BaseInterp {
public:
	LinInterp(std::vector<double>& xv, std::vector<double>& yv) : BaseInterp(xv, yv, 2) {}
	double rawinterp(int j, double x);
};

class BilinInterp {
public:
	int m, n;
	std::vector<std::vector<double>>& y;
	LinInterp x1terp, x2terp;

	BilinInterp(std::vector<double>& x1v, std::vector<double>& x2v, std::vector<std::vector<double>>& ym);

	double interp(double x1p, double x2p);
};

#endif