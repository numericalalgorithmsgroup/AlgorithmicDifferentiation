#include<vector>
using namespace std;

#include "dco.hpp"
using namespace dco;

typedef ga1s<double> DCO_BASE_MODE;
typedef DCO_BASE_MODE::type DCO_BASE_TYPE;
typedef DCO_BASE_MODE::tape_t DCO_BASE_TAPE_TYPE;
typedef ga1s<DCO_BASE_TYPE> DCO_MODE;
typedef DCO_MODE::type DCO_TYPE;
typedef DCO_MODE::tape_t DCO_TAPE_TYPE;

#include "f.hpp" 

void driver(
    const vector<double>& xv,   
    vector<double>& xa2, 
    vector<double>& xa1,       
    vector<double>& xa1a2,     
    vector<double>& yv, 	      
    vector<double>& ya2,      
    vector<double>& ya1,      
    vector<double>& ya1a2     
) {
  
  DCO_BASE_MODE::global_tape=DCO_BASE_TAPE_TYPE::create();
  DCO_MODE::global_tape=DCO_TAPE_TYPE::create();
  const size_t n=xv.size(), m=yv.size();
  vector<DCO_TYPE> x(n), y(m);

  for (size_t j=0;j<n;j++) { 
    x[j]=xv[j]; 
    DCO_BASE_MODE::global_tape->register_variable(value(x[j]));
    DCO_MODE::global_tape->register_variable(x[j]);
  }

  f(x,y); 

  for (size_t j=0;j<m;j++) { 
    derivative(y[j])=ya1[j];
    DCO_BASE_MODE::global_tape->register_variable(derivative(y[j]));
  }
  
  DCO_MODE::global_tape->interpret_adjoint();

  for (size_t j=0;j<n;j++) {
    xa1[j]=value(derivative(x[j]));
    derivative(derivative(x[j]))=xa1a2[j];
  }
  for (size_t j=0;j<m;j++) {
    derivative(value(y[j])) = ya2[j];
  }
  DCO_BASE_MODE::global_tape->interpret_adjoint();
  
  for (size_t j=0;j<n;j++) {
    xa2[j]=derivative(value(x[j]));
  }

  for (size_t j=0;j<m;j++) {
    yv[j]=value(value(y[j]));
    ya1a2[j] = derivative(derivative(y[j]));
  }

  DCO_BASE_TAPE_TYPE::remove(DCO_BASE_MODE::global_tape);
  DCO_TAPE_TYPE::remove(DCO_MODE::global_tape);
}
