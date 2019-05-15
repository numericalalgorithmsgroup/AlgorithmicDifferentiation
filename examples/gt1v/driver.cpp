#include<iostream>
#include<vector>
using namespace std;
#include "dco.hpp" 
using namespace dco;
#include "f.hpp"

const DCO_INTEGRAL_TAPE_INT l=4;

typedef double DCO_BASE_MODE;
typedef gt1v<DCO_BASE_MODE, l> DCO_MODE;
typedef DCO_MODE::type DCO_TYPE;

void driver(
    const vector<double>& x,      
    const vector<vector<double> >& xt1, 
    vector<double>& y, 	          
    vector<vector<double> >& yt1  
) {
  const size_t n=x.size(), m=y.size(); 
  vector<DCO_TYPE> t1v_x(n), t1v_y(m);
  for (size_t i=0;i<n;i++) {
    value(t1v_x[i])=x[i];
    for (DCO_TAPE_INT j=0;j<l;j++) 
      derivative(t1v_x[i])[j]=xt1[i][j];
  }
  f(t1v_x,t1v_y);
  for (size_t i=0;i<m;i++) {
    y[i]=value(t1v_y[i]);
    for (DCO_TAPE_INT j=0;j<l;j++) 
      yt1[i][j]=derivative(t1v_y[i])[j];
  }
}
