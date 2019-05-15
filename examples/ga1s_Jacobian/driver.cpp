#include <vector>
using namespace std;

#include "dco.hpp" 
using namespace dco;

typedef double AD_BASE_TYPE;
typedef ga1s<AD_BASE_TYPE> AD_MODE;
typedef AD_MODE::type AD_TYPE;
typedef AD_MODE::tape_t AD_TAPE_TYPE;

#include "f.hpp"
		   
void a1s_driver(
    const vector<double>& xv, vector<double>& yv,         
    vector<vector<double> >& J 
) {
  AD_MODE::global_tape=AD_TAPE_TYPE::create();
  const size_t n=xv.size(), m=yv.size();
  vector<AD_TYPE> x(n), y(m);
  for (size_t i=0;i<n;i++) {
    x[i]=xv[i];
    AD_MODE::global_tape->register_variable(x[i]);
  }
  f(x,y);
  for (size_t i=0;i<m;i++) {
    AD_MODE::global_tape->register_output_variable(y[i]);
    yv[i]=value(y[i]);
  }

  for (size_t j=0;j<m;j++) {
    derivative(y[j])=1;
    for (size_t i=0;i<n;i++) derivative(x[i])=0;
    AD_MODE::global_tape->interpret_adjoint();
    for (size_t i=0;i<n;i++) J[j][i]=derivative(x[i]);
    AD_MODE::global_tape->zero_adjoints();
  }
  AD_TAPE_TYPE::remove(AD_MODE::global_tape);
}
