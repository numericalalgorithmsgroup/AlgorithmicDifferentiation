#include "dco.hpp"
#include "f.hpp"

void driver (double& x, double& xt1) {
	dco::gt1s<double>::type t1s_x = x;
	dco::derivative(t1s_x) = xt1;
	f(t1s_x);
	x = dco::value(t1s_x);
	xt1 = dco::derivative(t1s_x);
}
