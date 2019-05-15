#include <iostream>
using namespace std;

#include "dco.hpp" // definition of dco::p1f::type

int val_idx(int i, int n) {
  return (i+n)%n;
}

void f(
    int n,                          // number of active inputs
    int m,                          // number of active outputs
    const dco::p1f::type * const x, // active inputs
    dco::p1f::type * const y        // active outputs
) {
  for (int i = 0; i < m; i++) {
    y[i] = x[val_idx(i-1, n)] * x[val_idx(i, n)] * x[val_idx(i+1, n)];
  }
}

void p1f_driver(
    int n,                  // number of active inputs
    int m,                  // number of active inputs
    const double * const x, // active inputs x
    double * const y       // active outputs y
) {
  dco::p1f::type *p1f_x=new dco::p1f::type[n];
  dco::p1f::type *p1f_y=new dco::p1f::type[m];

  // initialization of values of active inputs
  // and activation
  for (int i=0;i<n;i++) {
    p1f_x[i] = x[i];
    dco::p1f::set(p1f_x[i], true, i);
  }

  // overloaded function evaluation
  f(n,m,p1f_x,p1f_y);

  // extraction of adjoints of active outputs
  for (int i=0;i<m;i++) {
    dco::p1f::get(p1f_y[i],y[i]);
    for (int j = 0; j < n; j++) {
      bool dep; dco::p1f::get(p1f_y[i],dep,j);
      if (dep) cout << "* ";
      else cout << "  ";
    }
    cout << endl;
  }

  delete [] p1f_y; delete [] p1f_x;
}

int main() {
  const int n=20, m=20;
  double *x=new double[n];
  double *y=new double[m];
  // initialization of inputs
  for (int i=0;i<n;i++) { x[i]=1.2; }
  // driver
  p1f_driver(n,m,x,y);
  // results
  for (int i=0;i<m;i++)
    cout << "y[" << i << "]=" << y[i] << endl;
  delete [] y; delete [] x;
  return 0;
}

