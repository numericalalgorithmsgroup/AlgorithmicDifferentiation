#include<iostream>
#include<vector>
using namespace std;

#include "dco.hpp" 
using namespace dco;

typedef gt1s<double> DCO_BASE_MODE;
typedef DCO_BASE_MODE::type DCO_BASE_TYPE;
typedef gt1s<DCO_BASE_TYPE> DCO_MODE;
typedef DCO_MODE::type DCO_TYPE;

#include "../x22.hpp" 

template<typename T>
void driver(const vector<T>& xv, T& yv, vector<T>& g, vector<vector<T> >& h)  {
  size_t n=xv.size();
  vector<DCO_TYPE> x(n); DCO_TYPE y; 
  for (size_t i=0;i<n;i++) { 
    for (size_t j=0;j<n;j++) { 
      for (size_t k=0;k<n;k++) x[k]=xv[k];
      derivative(value(x[i]))=1;
      value(derivative(x[j]))=1;
      f(x,y); 
      h[i][j]=derivative(derivative(y));
    }
    g[i]=derivative(value(y));
  } 
  yv=passive_value(y);
}

int main(int c, char* v[]) {
  assert(c==2); (void)c;
  cout.precision(15);
  size_t n=atoi(v[1]);
  vector<vector<double> > H(n, vector<double>(n));
  vector<double> x(n), g(n); double y;
  for (size_t i=0;i<n;i++) x[i]=cos(double(i));
  driver(x,y,g,H);
  cout << y << endl;
  for (size_t i=0;i<n;i++)
    cout << g[i] << endl;
  for (size_t i=0;i<n;i++)
    for (size_t j=0;j<n;j++)
      cout << H[i][j] << endl;
  return 0;
}
