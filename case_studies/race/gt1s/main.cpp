#include<vector>
#include<iostream>
using namespace std;
#include "dco.hpp"
using namespace dco;
#include "../x22.hpp"

template<typename T>
void gt1s_driver(const vector<T>& xv, T& yv, vector<T>& g) {
  typedef typename gt1s<T>::type DCO_TYPE;
  size_t n=xv.size();
  vector<DCO_TYPE> x(n); DCO_TYPE y; 
  for (size_t i=0;i<n;i++) { 
    for (size_t j=0;j<n;j++) x[j]=xv[j];
    derivative(x[i])=1.;
    f(x,y); 
    g[i]=derivative(y);
  } 
  yv=value(y);
}

int main(int c, char* v[]) {
  assert(c==2); (void)c;
  cout.precision(15);
  size_t n=atoi(v[1]); 
  vector<double> x(n), g(n); double y; 
  for (size_t i=0;i<n;i++) x[i]=cos(double(i)); 
  gt1s_driver(x,y,g); 
  cout << y << endl;
  for (size_t i=0;i<n;i++) 
    cout << g[i] << endl; 
  return 0;
}
