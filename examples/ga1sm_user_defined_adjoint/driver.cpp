#include "dco.hpp"
typedef dco::ga1sm<double> AD_MODE;
typedef AD_MODE::type AD_TYPE;
typedef AD_MODE::tape_t AD_TAPE_TYPE;
typedef AD_TAPE_TYPE::iterator_t AD_TAPE_ITERATOR_TYPE;

#include "f.hpp"

void driver (const double& p, double& pa1, double& x, double& xa1) {
  // exception safety through safe pointer -> user
  AD_TAPE_TYPE* AD_TAPE_POINTER=AD_TAPE_TYPE::create();
  AD_TYPE a1s_x=x,a1s_p=p;
  AD_TAPE_POINTER->register_variable(a1s_p);
  f<AD_MODE>(a1s_p,a1s_x);
  x = dco::value(a1s_x);
  AD_TAPE_POINTER->register_output_variable(a1s_x);
  dco::derivative(a1s_x) = xa1;
  AD_TAPE_POINTER->interpret_adjoint();
  pa1 = dco::derivative(a1s_p);
  AD_TAPE_TYPE::remove(AD_TAPE_POINTER);
}
