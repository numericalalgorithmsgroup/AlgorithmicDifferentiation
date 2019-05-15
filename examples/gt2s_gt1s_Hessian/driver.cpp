#include<iostream>
using namespace std;

#include "dco.hpp" // definition of AD data types
using namespace dco;

typedef gt1s<double>::type t1s_type;
typedef gt1s<t1s_type>::type t2s_t1s_type;

#include "f.hpp"

void t2s_t1s_driver(
    const vector<double>& x, 	         // active inputs x
    vector<double>& y, 		         // active outputs y
    vector<vector<double> >& J,          // Jacobian
    vector<vector<vector<double> > >& H  // Hessian
) {
  const int n=x.size(), m=y.size();
  vector<t2s_t1s_type> t2s_t1s_x(n), t2s_t1s_y(m);
  // initialization of values, first and second directional
  // derivatives of active inputs
  for (int l=0;l<n;l++) {
    for (int k=0;k<n;k++) {
      for (int i=0;i<n;i++) {
        t1s_type v = value(t2s_t1s_x[i]);
        value(v) = x[i];
        derivative(v) = 0;
        if (i==k)
          derivative(v) = 1;
        value(t2s_t1s_x[i]) = v;
         v= derivative(t2s_t1s_x[i]);
         value(v) = 0;
        if (i==l)
          value(v) = 1;
        derivative(v) = 0;
        derivative(t2s_t1s_x[i]) = v;
      }
      // overloaded function evaluation
      f(t2s_t1s_x,t2s_t1s_y);
      // extraction of values, first and second directional
      // derivatives from active outputs
      for (int j=0;j<m;j++) {
        t1s_type v;
        v = value(t2s_t1s_y[j]);
        if (k+l==0)
          y[j] = value(v);
        J[j][k] = derivative(v);
        v = derivative(t2s_t1s_y[j]);
        H[j][l][k] = derivative(v);
      }
    }
  }
}
