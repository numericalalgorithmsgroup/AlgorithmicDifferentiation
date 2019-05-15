#include <vector>
using namespace std;

#include "dco.hpp" 
using namespace dco;

const int l=5;

typedef double DCO_BASE_TYPE;
typedef ga1v<DCO_BASE_TYPE,l> DCO_MODE;
typedef DCO_MODE::type DCO_TYPE;
typedef DCO_MODE::tape_t DCO_TAPE_TYPE;

#include "f.hpp"
		   
void driver(
  const vector<double>& xv, vector<vector<double> >& xa,     
  vector<double>& yv, vector<vector<double> >& ya      
) {
  DCO_MODE::global_tape=DCO_TAPE_TYPE::create();
  int n=xv.size(), m=yv.size();
  vector<DCO_TYPE> x(n), y(m);
  for (int i=0;i<n;i++) {
    x[i]=xv[i];
    DCO_MODE::global_tape->register_variable(x[i]);
  }
  f(x,y);
  for (int i=0;i<m;i++) {
    DCO_MODE::global_tape->register_output_variable(y[i]);
    yv[i]=value(y[i]); 
    for (int j=0;j<l;j++) derivative(y[i])[j] = ya[i][j];
  }
  for (int i=0;i<n;i++) {
    for (int j=0;j<l;j++) derivative(x[i])[j] = xa[i][j];
  }
  DCO_MODE::global_tape->interpret_adjoint();
  for (int i=0;i<n;i++) {
    for (int j=0;j<l;j++) xa[i][j]=derivative(x[i])[j];
  }
  for (int i=0;i<m;i++) {
    for (int j=0;j<l;j++) ya[i][j]=derivative(y[i])[j];
  }
  DCO_TAPE_TYPE::remove(DCO_MODE::global_tape);
}
