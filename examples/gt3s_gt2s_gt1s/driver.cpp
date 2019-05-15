#include<iostream>
using namespace std;

#include "dco.hpp" 
using namespace dco;

typedef gt1s<double> DCO_BASE_BASE_MODE;
typedef DCO_BASE_BASE_MODE::type DCO_BASE_BASE_TYPE;
typedef gt1s<DCO_BASE_BASE_TYPE> DCO_BASE_MODE;
typedef DCO_BASE_MODE::type DCO_BASE_TYPE;
typedef gt1s<DCO_BASE_TYPE> DCO_MODE;
typedef DCO_MODE::type DCO_TYPE;

#include "f.hpp"

void driver(
    const vector<double>& xv, 	   
    const vector<double>& xt3, 	   
    const vector<double>& xt1, 	   
    const vector<double>& xt1t3,   
    const vector<double>& xt2, 	   
    const vector<double>& xt2t3,   
    const vector<double>& xt1t2,   
    const vector<double>& xt1t2t3, 
    vector<double>& yv,		   
    vector<double>& yt3, 	   
    vector<double>& yt1, 	   
    vector<double>& yt1t3, 	   
    vector<double>& yt2, 	   
    vector<double>& yt2t3, 	   
    vector<double>& yt1t2,	   
    vector<double>& yt1t2t3	   
) {
  const size_t n=xv.size(), m=yv.size();
  vector<DCO_TYPE> x(n), y(m);
  for (size_t i=0;i<n;i++) {
    value(value(value(x[i])))=xv[i];
    value(value(derivative(x[i])))=xt1[i];
    value(derivative(value(x[i])))=xt2[i];
    derivative(value(value(x[i])))=xt3[i];
    value(derivative(derivative(x[i])))=xt1t2[i];
    derivative(derivative(value(x[i])))=xt2t3[i];
    derivative(value(derivative(x[i])))=xt1t3[i];
    derivative(derivative(derivative(x[i]))),xt1t2t3[i];
  }
  f(x,y);
  for (size_t j=0;j<m;j++) {
    yt1t2t3[j]=derivative(derivative(derivative(y[j])));
    yt2t3[j]=derivative(derivative(value(y[j])));
    yt1t3[j]=derivative(value(derivative(y[j])));
    yt1t2[j]=value(derivative(derivative(y[j])));
    yt1[j]=value(value(derivative(y[j])));
    yt2[j]=value(derivative(value(y[j])));
    yt3[j]=derivative(value(value(y[j])));
    yv[j]=value(value(value(y[j])));
  }
}
