#include<vector>
#include<iostream>
using namespace std;
#include "dco.hpp"
using namespace dco;
#include "../x22.hpp"

template<typename T>
void gt1v_driver(const vector<T>& xv, T& yv, vector<T>& g) {
  size_t n=xv.size(); const size_t l=100; assert(!(n%l));
  typedef typename gt1v<T,l>::type DCO_TYPE;
  vector<DCO_TYPE> x(n); DCO_TYPE y; 
  for (size_t j=0;j<n/l;j++) { 
    for (size_t i=0;i<n;i++) x[i]=xv[i];
    for (size_t i=0;i<l;i++) derivative(x[j*l+i])[i]=1.;
    f(x,y); 
    for (size_t i=0;i<l;i++) g[j*l+i]=derivative(y)[i];
  }
  yv=value(y);
}

int main(int c, char* v[]) {
  assert(c==2); (void)c;
  cout.precision(15);
  size_t n=atoi(v[1]); 
  vector<double> x(n), g(n); double y; 
  for (size_t i=0;i<n;i++) x[i]=cos(double(i)); 
  gt1v_driver(x,y,g); 
  cout << y << endl;
  for (size_t i=0;i<n;i++) 
    cout << g[i] << endl; 
  return 0;
}
