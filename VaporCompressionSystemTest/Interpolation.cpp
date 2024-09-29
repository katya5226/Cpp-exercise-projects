#include "interpolation.h"


BaseInterp::BaseInterp(std::vector<double>& x, std::vector<double>& y, int m) : n(x.size()), mm(m), jsav(0), cor(0), xx(x), yy(y){
	dj = min<int>(1, static_cast<int>(pow((double)n, 0.25)));
}

double BaseInterp::interp(double x) {
	int jlo = cor ? hunt(x) : locate(x);
	return rawinterp(jlo, x);
}

int BaseInterp::locate(const double x) {
	int ju, jm, jl;
	if (n < 2 || mm < 2 || mm >n) throw("Locate size error");

	bool ascnd = (xx[n - 1] >= xx[0]);
	jl = 0;
	ju = n - 1;
	while (ju - jl > 1) {
		jm = (ju + jl) >> 1;
		if (x >= xx[jm] == ascnd)
			jl = jm;
		else
			ju = jm; 
	}
	cor = abs(jl - jsav) > dj ? 0 : 1;
	jsav = jl;
	return max(0, min(n - mm, jl - ((mm - 2) >> 1)));
}

int BaseInterp::hunt(const double x) {
	int jl = jsav, jm, ju, inc = 1;
	if (n < 2 || mm <2 || mm>n) throw("Hunt size error");
	bool ascnd = (xx[n - 1] >= xx[0]);
	if (jl < 0 || jl > n - 1) {
		jl = 0;
		ju = n - 1;
	}
	else {
		if (x >= xx[jl] == ascnd) {
			for (;;) {
				ju = jl + inc;
				if (ju >= n - 1) { ju = n - 1; break; }
				else if (x < xx[ju] == ascnd) break;
				else {
					jl = ju;
					inc += inc;
				}
			}
		}
		else {
			ju = jl;
			for (;;) {
				jl = jl - inc;
				if (jl <= 0) { jl = 0; break; }
				else if (x >= xx[jl] == ascnd) break;
				else {
					ju = jl;
					inc += inc;
				}
			}
		}
	}
	while (ju - jl > 1) {
		jm = (ju + jl) >> 1;
		if (x >= xx[jm] == ascnd) jl = jm;
		else ju = jm;
	}
	cor = abs(jl - jsav) > dj ? 0 : 1;
	jsav = jl;
	return max(0, min(n - mm, jl - ((mm - 2) >> 1)));
}

//LinInterp::LinInterp(std::vector<double>& xv, std::vector<double>& yv) : BaseInterp(xv, yv, 2) {}

double LinInterp::rawinterp(int j, double x) {
	if (xx[j] == xx[j + 1]) return yy[j];
	else return yy[j] + ((x - xx[j]) / (xx[j + 1] - xx[j])) * (yy[j + 1] - yy[j]);
}

BilinInterp::BilinInterp(std::vector<double>& x1v, std::vector<double>& x2v, std::vector<std::vector<double>>& ym) : m(x1v.size()), n(x2v.size()), y(ym),
x1terp(x1v, x1v), x2terp(x2v, x2v) {}


double BilinInterp::interp(double x1p, double x2p) {
	int i, j;
	double yy, t, u;

	i = x1terp.cor ? x1terp.hunt(x1p) : x1terp.locate(x1p);
	j = x2terp.cor ? x2terp.hunt(x2p) : x2terp.locate(x2p);


	t = (x1p - x1terp.xx[i]) / (x1terp.xx[i + 1] - x1terp.xx[i]);
	u = (x2p - x2terp.xx[j]) / (x2terp.xx[j + 1] - x2terp.xx[j]);

	yy = (1. - t) * (1. - u) * y[i][j] + t * (1. - u) * y[i + 1][j]
		+ (1. - t) * u * y[i][j + 1] + t * u * y[i + 1][j + 1];

	return yy;
}

