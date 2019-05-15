#include <iostream>
#include <vector>
using namespace std;

#include "driver.hpp"

int main() {
  const int n=4, m=2; cout.precision(15);
  vector<double> xv(n), xa(n), yv(m), ya(m), yp(m);
  for (int i=0;i<n;i++) { xv[i]=1; xa[i]=1; }
  for (int i=0;i<m;i++) ya[i]=1; 
  driver(xv,xa,yv,ya, yp);
  for (int i=0;i<m;i++)
    cout << "y[" << i << "]=" << yv[i] << endl;
  for (int i=0;i<m;i++)
    cout << "yp[" << i << "]=" << yp[i] << endl;
  for (int i=0;i<n;i++)
    cout << "x_{(1)}[" << i << "]=" << xa[i] << endl;
  return 0;
}


