#include<iostream>
#include<vector>
using namespace std;

#include "dco.hpp" 
using namespace dco;

typedef gt1s<double> DCO_BASE_BASE_MODE;
typedef DCO_BASE_BASE_MODE::type DCO_BASE_BASE_TYPE;
typedef gt1s<DCO_BASE_BASE_TYPE> DCO_BASE_MODE;
typedef DCO_BASE_MODE::type DCO_BASE_TYPE;
typedef ga1s<DCO_BASE_TYPE> DCO_MODE;
typedef DCO_MODE::type DCO_TYPE;
typedef DCO_MODE::tape_t DCO_TAPE_TYPE;

#include "f.hpp" 

void driver(
    const vector<double>& xv,   
    const vector<double>& xt3,  
    const vector<double>& xt2,  
    const vector<double>& xt2t3,
    vector<double>& xa1,       
    vector<double>& xa1t3,    
    vector<double>& xa1t2,   
    vector<double>& xa1t2t3,
    vector<double>& yv,	   
    vector<double>& yt3, 
    vector<double>& yt2,
    vector<double>& yt2t3,    
    vector<double>& ya1,     
    vector<double>& ya1t3,  
    vector<double>& ya1t2, 
    vector<double>& ya1t2t3
) {
  DCO_MODE::global_tape=DCO_TAPE_TYPE::create();
  const size_t n=xv.size(), m=yv.size();
  vector<DCO_TYPE> x(n), y(m);
  for (size_t i=0;i<n;i++) {
    DCO_MODE::global_tape->register_variable(x[i]);
    value(value(value(x[i])))=xv[i];
    derivative(value(value(x[i])))=xt3[i];
    value(derivative(value(x[i])))=xt2[i];
    derivative(derivative(value(x[i])))=xt2t3[i];
  }
  f(x,y);
  for (size_t i=0;i<n;i++) {
    value(value(derivative(x[i])))=xa1t3[i];
    derivative(value(derivative(x[i])))=xa1t3[i];
    value(derivative(derivative(x[i])))=xa1t2[i];
    derivative(derivative(derivative(x[i])))=xa1t2t3[i];
  }
  for (size_t i=0;i<m;i++) {
    yv[i]=value(value(value(y[i])));
    yt3[i]=derivative(value(value(y[i])));
    yt2[i]=value(derivative(value(y[i])));
    yt2t3[i]=derivative(derivative(value(y[i])));
    DCO_MODE::global_tape->register_output_variable(y[i]);
    derivative(derivative(derivative(y[i])))=ya1t2t3[i];
    value(derivative(derivative(y[i])))=ya1t2[i];
    derivative(value(derivative(y[i])))=ya1t3[i];
    value(value(derivative(y[i])))=ya1[i];
  }
  DCO_MODE::global_tape->interpret_adjoint();
  for (size_t i=0;i<n;i++) {
    xa1t2t3[i]=derivative(derivative(derivative(x[i])));
    xa1t2[i]=value(derivative(derivative(x[i])));
    xa1t3[i]=derivative(value(derivative(x[i])));
    xa1[i]=value(value(derivative(x[i])));
  }
  for (size_t i=0;i<m;i++) {
    ya1t2t3[i]=derivative(derivative(derivative(y[i])));
    ya1t2[i]=value(derivative(derivative(y[i])));
    ya1t3[i]=derivative(value(derivative(y[i])));
    ya1[i]=value(value(derivative(y[i])));
  }
  DCO_TAPE_TYPE::remove(DCO_MODE::global_tape);
}
