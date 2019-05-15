#include<iostream>
#include<vector>
#include<cstdlib>
#include<cmath>
#include<cmath>
using namespace std;

#include "driver.hpp"

int main() {
  const int m=12, n=12; cout.precision(15);
  vector<double> xv(n), xa(n), yv(m), ya(m);
  for (int i=0;i<n;i++) { xv[i]=sin(static_cast<double>(i+1)); xa[i]=1; }
  for (int i=0;i<m;i++) ya[i]=1; 
  driver(xv,xa,yv,ya);
  for (int i=0;i<m;i++) 
    cout << "y[" << i << "]=" << yv[i] << endl;
  for (int i=0;i<n;i++)
    cout << "x_{(1)}[" << i << "]=" << xa[i] << endl;
  return 0;
}
