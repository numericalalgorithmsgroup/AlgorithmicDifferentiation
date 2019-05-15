#include<vector>
using namespace std;

#include "dco.hpp"
using namespace dco;

typedef gt1s<double> DCO_BASE_MODE;
typedef DCO_BASE_MODE::type DCO_BASE_TYPE;
typedef ga1s<DCO_BASE_TYPE> DCO_MODE;
typedef DCO_MODE::type DCO_TYPE;
typedef DCO_MODE::tape_t DCO_TAPE_TYPE;

#include "f.hpp" 

void driver(
    const vector<double>& xv,   
    const vector<double>& xt2, 
    vector<double>& xa1,       
    vector<double>& xa1t2,     
    vector<double>& yv, 	      
    vector<double>& yt2,      
    vector<double>& ya1,      
    vector<double>& ya1t2     
) {
  DCO_MODE::global_tape=DCO_TAPE_TYPE::create();
  const size_t n=xv.size(), m=yv.size();
  vector<DCO_TYPE> x(n), y(m);
  for (size_t i=0;i<n;i++) {
    x[i]=xv[i];
    DCO_MODE::global_tape->register_variable(x[i]);
    derivative(value(x[i]))=xt2[i];
  }
  f(x,y);
  for (size_t i=0;i<n;i++) {
    value(derivative(x[i]))=xa1[i];
    derivative(derivative(x[i]))=xa1t2[i];
  }
  for (size_t i=0;i<m;i++) {
    yv[i]=passive_value(y[i]);
    yt2[i]=derivative(value(y[i]));
    DCO_MODE::global_tape->register_output_variable(y[i]);
    value(derivative(y[i]))=ya1[i];
    derivative(derivative(y[i]))=ya1t2[i];
  }
  DCO_MODE::global_tape->interpret_adjoint();
  for (size_t i=0;i<n;i++) {
    xa1t2[i]=derivative(derivative(x[i]));
    xa1[i]=value(derivative(x[i]));
  }
  for (size_t i=0;i<m;i++) {
    ya1t2[i]=derivative(derivative(y[i]));
    ya1[i]=value(derivative(y[i]));
  }
  DCO_TAPE_TYPE::remove(DCO_MODE::global_tape);
}
