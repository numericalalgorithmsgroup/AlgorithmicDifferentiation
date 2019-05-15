#include <vector>
using namespace std;

#include "dco.hpp"
using namespace dco;

typedef double DCO_BASE_TYPE;
typedef ga1s<DCO_BASE_TYPE> DCO_MODE;
typedef DCO_MODE::type DCO_TYPE;
typedef DCO_MODE::tape_t DCO_TAPE_TYPE;

#include "f.hpp"

void driver(
    const vector<double>& xv, vector<double>& xa,
    vector<double>& yv, vector<double>& ya
) {
  DCO_MODE::global_tape=DCO_TAPE_TYPE::create();
  size_t n=xv.size(), m=yv.size();
  vector<DCO_TYPE> x(n), y(m);
  for (size_t i=0;i<n;i++) {
    x[i]=xv[i];
    DCO_MODE::global_tape->register_variable(x[i]);
  }
  f(x,y);
  for (size_t i=0;i<m;i++) {
    DCO_MODE::global_tape->register_output_variable(y[i]);
    yv[i]=value(y[i]); derivative(y[i])=ya[i];
  }
  for (size_t i=0;i<n;i++) derivative(x[i])=xa[i];
  DCO_MODE::global_tape->interpret_adjoint();
  for (size_t i=0;i<n;i++) xa[i]=derivative(x[i]);
  for (size_t i=0;i<m;i++) ya[i]=derivative(y[i]);
  DCO_TAPE_TYPE::remove(DCO_MODE::global_tape);
}


#include <cfloat>

void fd_driver (
    const vector<double>& xv, vector<double>& xa, vector<double>& xa1t2x,
    vector<double>& yv, vector<double>& yt2x, vector<double>& ya) {
  size_t n=xv.size(), m=yv.size();
  vector<double> h(n),xap(n),xvp(n),yvp(m),yap(m);
  for (size_t i=0;i<m;i++) yap[i]=ya[i];
  for (size_t i=0;i<n;i++) {
    xap[i]=xa[i];
    h[i]=(xv[i]==0) ? sqrt(DBL_EPSILON) : sqrt(DBL_EPSILON)*abs(xv[i]);
    xvp[i]=xv[i]+h[i];
  }
  driver(xv,xa,yv,ya);
  driver(xvp,xap,yvp,yap);
  for (size_t i=0;i<m;i++) 
    yt2x[i]=(yvp[i]-yv[i])/h[i];
  for (size_t i=0;i<n;i++) 
    xa1t2x[i]=(xap[i]-xa[i])/h[i];
}
