#include<iostream>
#include<vector>
#include<cstdlib>
#include<cmath>
using namespace std;

#include "driver.hpp"

int main() {
  const int m=12, n=12; cout.precision(15);
  vector<double> xv(n), xt(n), yv(m), yt(m);
  for (int i=0;i<n;i++) { xv[i]=sin(static_cast<double>(i+1)); xt[i]=1; }
  driver(xv,xt,yv,yt);
  for (int i=0;i<m;i++) 
    cout << "y[" << i << "]=" << yv[i] << endl;
  for (int i=0;i<n;i++)
    cout << "y^{(1)}[" << i << "]=" << yt[i] << endl;
  return 0;
}
