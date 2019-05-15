#include <vector>
using namespace std;

#include "dco.hpp" 
using namespace dco;

typedef double DCO_BASE_TYPE;
typedef ga1sm<DCO_BASE_TYPE> DCO_MODE;
typedef DCO_MODE::type DCO_TYPE;
typedef DCO_MODE::tape_t DCO_TAPE_TYPE;

#include "f.hpp"
		   
void driver(
    const vector<double>& xv, vector<double>& xa,     
    vector<double>& yv, vector<double>& ya      
) {
  DCO_TAPE_TYPE *tape=DCO_TAPE_TYPE::create();
  size_t n=xv.size(), m=yv.size();
  vector<DCO_TYPE> x(n), y(m);
  for (size_t i=0;i<n;i++) {
    x[i]=xv[i];
    tape->register_variable(x[i]);
  }
  f(x,y);
  for (size_t i=0;i<m;i++) {
    tape->register_output_variable(y[i]);
    yv[i]=value(y[i]); derivative(y[i])=ya[i];
  }
  for (size_t i=0;i<n;i++) derivative(x[i])=xa[i];
  tape->interpret_adjoint();
  for (size_t i=0;i<n;i++) xa[i]=derivative(x[i]);
  for (size_t i=0;i<m;i++) ya[i]=derivative(y[i]);
  DCO_TAPE_TYPE::remove(tape);
}
