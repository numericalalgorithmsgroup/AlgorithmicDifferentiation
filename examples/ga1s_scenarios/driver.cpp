#include "dco.hpp" 
using namespace dco;
typedef double AD_BASE_TYPE;
typedef ga1s<AD_BASE_TYPE> AD_MODE;
typedef AD_MODE::type AD_TYPE;
typedef AD_MODE::tape_t AD_TAPE_TYPE;

void driver(int n, double& xv, double& xa, const double& pv, double& pa) {
  AD_MODE::global_tape=AD_TAPE_TYPE::create();
  AD_TYPE x=xv, p=pv;
  AD_MODE::global_tape->register_variable(p);
  AD_MODE::global_tape->register_variable(x);
  AD_TYPE x_in=x;

  AD_TAPE_TYPE::iterator_t p0=AD_MODE::global_tape->get_position();
  AD_TAPE_TYPE::iterator_t p1=AD_MODE::global_tape->get_position();

  for (int i=0;i<n;i++) {
    x=sin(x*p);
    if (i==n/2) p1=AD_MODE::global_tape->get_position();
  }

  AD_MODE::global_tape->register_output_variable(x);
  derivative(x)=xa; derivative(p)=pa;
  AD_MODE::global_tape->interpret_adjoint_to(p1);

  for (int i=0;i<n;i++) {
    x=sin(x*p);
  }
  xv=value(x);

  AD_MODE::global_tape->interpret_adjoint_to(p0);
  xa=derivative(x_in); pa=derivative(p);
  AD_TAPE_TYPE::remove(AD_MODE::global_tape);
}
