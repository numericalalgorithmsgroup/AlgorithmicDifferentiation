#include<iostream>
#include<cmath>
#include<vector>
using namespace std;

#include "dco.hpp"

typedef dco::ga1s<double> DCO_MODE;
typedef DCO_MODE::type DCO_TYPE;
typedef DCO_MODE::tape_t DCO_TAPE_TYPE;

#include "f.h"

void driver() {
  const int n=1000, s=100;
  const double x0=1;
  vector<DCO_TYPE> p(n,1); 
  DCO_MODE::global_tape=DCO_TAPE_TYPE::create();
  for (int i=0;i<n;i++) 
    DCO_MODE::global_tape->register_variable(p[i]);
  DCO_TYPE x=x0; 
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
  for (int i=n/2-3;i<n/2+3;i++) 
    cout << "dx/dp[" << i << "]=" << dco::derivative(p[i]) << endl;
  DCO_TAPE_TYPE::remove(DCO_MODE::global_tape);
}
