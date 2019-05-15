#include <vector>
using namespace std;

#include "dco.hpp" 
using namespace dco;

const DCO_INTEGRAL_TAPE_INT l=5;

typedef double DCO_BASE_TYPE;
typedef ga1vm<DCO_BASE_TYPE,l> DCO_MODE;
typedef DCO_MODE::type DCO_TYPE;
typedef DCO_MODE::tape_t DCO_TAPE_TYPE;

#include "f.hpp"
		   
void driver(
  const vector<double>& xv, vector<vector<double> >& xa,     
  vector<double>& yv, vector<vector<double> >& ya      
) {
  DCO_MODE::tape_t *tape=DCO_TAPE_TYPE::create();
  size_t n=xv.size(), m=yv.size();
  vector<DCO_TYPE> x(n), y(m);
  for (size_t i=0;i<n;i++) {
    x[i]=xv[i];
    tape->register_variable(x[i]);
  }
  f(x,y);
  for (size_t i=0;i<m;i++) {
    tape->register_output_variable(y[i]);
    yv[i]=value(y[i]); 
    for (int j=0;j<l;j++) derivative(y[i])[j] = ya[i][j];
  }
  for (size_t i=0;i<n;i++) {
    for (DCO_TAPE_INT j=0;j<l;j++) derivative(x[i])[j] = xa[i][j];
  }
  tape->interpret_adjoint();
  for (size_t i=0;i<n;i++) {
    for (DCO_TAPE_INT j=0;j<l;j++) xa[i][j]=derivative(x[i])[j];
  }
  for (size_t i=0;i<m;i++) {
    for (DCO_TAPE_INT j=0;j<l;j++) ya[i][j]=derivative(y[i])[j];
  }
  DCO_TAPE_TYPE::remove(tape);
}
