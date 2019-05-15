#include<iostream>
#include<cfloat>
#include<cmath>
#include<cassert>
#include<cstdlib>
#include<vector>
using namespace std;

#include "../x22.hpp"

template<typename T>
void cfd_driver(const vector<T> &x, T &y, vector<T> &g) {
  size_t n=x.size();
  vector<T> x_ph(n), x_mh(n);
  T y_ph, y_mh;
  f(x,y);
  for (size_t i=0;i<n;i++) {
    for (size_t j=0;j<n;j++)  x_ph[j]=x_mh[j]=x[j];
    T h=(x[i]==0) ? sqrt(DBL_EPSILON) : sqrt(DBL_EPSILON)*abs(x[i]);
    x_ph[i]+=h;
    f(x_ph,y_ph);
    x_mh[i]-=h;
    f(x_mh,y_mh);
    g[i]=(y_ph-y_mh)/(2*h);
  }
}

int main(int c, char* v[]) {
  assert(c==2); (void)c;
  cout.precision(15);
  size_t n=atoi(v[1]);
  vector<double> x(n), g(n); double y;
  for (size_t i=0;i<n;i++) x[i]=cos(double(i));
  cfd_driver(x,y,g);
  cout << y << endl;
  for (size_t i=0;i<n;i++)
    cout << g[i] << endl;
  return 0;
}

