#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

#include "dco.hpp"

typedef dco::gt1s<double>::type DCO_BASE_TYPE;
typedef dco::ga1s<DCO_BASE_TYPE> DCO_MODE;
typedef DCO_MODE::type DCO_TYPE;
typedef DCO_MODE::tape_t DCO_TAPE_TYPE;

#include "f.h"

void driver() {
  const int n=100, s=10;
  const double x0=1;
  vector<DCO_TYPE> p(n,1); 
  vector<vector<double> > H(n,vector<double>(n,0)); 
  DCO_MODE::global_tape=DCO_TAPE_TYPE::create();
  for (int i=0;i<n;i++) 
    DCO_MODE::global_tape->register_variable(p[i]);
  DCO_TAPE_TYPE::position_t tpos=DCO_MODE::global_tape->get_position();
  for (int j=0;j<n;j++) {
    DCO_TYPE x=x0; 
    dco::derivative(dco::value(p[j]))=1;
    DCO_MODE::jacobian_preaccumulator_t jp(DCO_MODE::global_tape);
    for (int i=0;i<n;i+=s) {
      jp.start();
      euler(i,min(i+s,n),x,p);
      jp.register_output(x);
      jp.finish();
    }
    DCO_MODE::global_tape->register_output_variable(x);
    dco::derivative(x)=1;
    DCO_MODE::global_tape->interpret_adjoint();
    for (int i=0;i<n;i++) {
      H[i][j]=dco::derivative(dco::derivative(p[i])); 
      dco::derivative(p[i])=0; 
    }
    DCO_MODE::global_tape->reset_to(tpos);
    dco::derivative(dco::value(p[j]))=0;
  }
  DCO_TAPE_TYPE::remove(DCO_MODE::global_tape);
  for (int j=n/2-1;j<n/2+1;j++) 
    for (int i=n/2-1;i<n/2+1;i++) 
      cout << "ddx/dp[" << j << "]dp[" << i << "]=" << H[j][i] << endl;
}
