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
    vector<double>& yv, vector<double>& ya, vector<double>& yp
) {
  DCO_MODE::global_tape=DCO_TAPE_TYPE::create();
  size_t n=xv.size(), m=yv.size();
  vector<DCO_TYPE> x(n), y(m);
  for (size_t i=0;i<n;i++) {
    x[i]=xv[i];
    DCO_MODE::global_tape->register_variable(x[i]);
  }
  f(x,y);

  std::vector<double> py(n);
#ifdef DCO_CPP11
  typedef gbcp<DCO_TYPE>::type DCO_GBCP_TYPE;
  auto const& px = create_gbcp<vector<DCO_GBCP_TYPE>>(x);
  f(px,py);
#else
  for (size_t i=0;i<m;i++) py[i] = dco::value(y[i]);
#endif
  for (size_t i=0;i<m;i++) {
    DCO_MODE::global_tape->register_output_variable(y[i]);
    yv[i]=value(y[i]); derivative(y[i])=ya[i];
  }
  for (size_t i=0;i<n;i++) derivative(x[i])=xa[i];

  DCO_MODE::global_tape->write_to_dot();
  DCO_MODE::global_tape->interpret_adjoint();
  for (size_t i=0;i<n;i++) xa[i]=derivative(x[i]);
  for (size_t i=0;i<m;i++) ya[i]=derivative(y[i]);
  for (size_t i=0;i<m;i++) yp[i]=py[i];
  DCO_TAPE_TYPE::remove(DCO_MODE::global_tape);
}
