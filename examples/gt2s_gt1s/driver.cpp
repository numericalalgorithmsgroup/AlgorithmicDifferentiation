#include<iostream>
using namespace std;

#include "dco.hpp" 
using namespace dco;
typedef gt1s<double> DCO_BASE_MODE;
typedef DCO_BASE_MODE::type DCO_BASE_TYPE;
typedef gt1s<DCO_BASE_TYPE> DCO_MODE;
typedef DCO_MODE::type DCO_TYPE;

#include "f.hpp"

void driver(
    const vector<double>& xv, 	
    const vector<double>& xt1, 	
    const vector<double>& xt2, 	
    const vector<double>& xt1t2, 
    vector<double>& yv, 		
    vector<double>& yt1, 	
    vector<double>& yt2, 	
    vector<double>& yt1t2	
) {
  const size_t n=xv.size(), m=yv.size();
  vector<DCO_TYPE> x(n), y(m);
  for (size_t i=0;i<n;i++) {
    value(value(x[i]))=xv[i];
    derivative(value(x[i]))=xt1[i];
    value(derivative(x[i]))=xt2[i];
    derivative(derivative(x[i]))=xt1t2[i];
  }
  f(x,y);
  for (size_t i=0;i<m;i++) {
    yv[i]=passive_value(y[i]);
    yt1[i]=derivative(value(y[i]));
    yt2[i]=value(derivative(y[i]));
    yt1t2[i]=derivative(derivative(y[i]));
  }
}
