#include "dco.hpp"
using namespace dco;
#include "f.hpp"

void driver (const double& pv, const double& pt1, double& xv, double& xt1) {
  gt1s<double>::type x=xv,p=pv;
  derivative(p)=pt1;
  f(p,x); 
  xv=value(x);
  xt1=derivative(x); 
}
