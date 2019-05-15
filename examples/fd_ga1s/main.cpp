#include <iostream>
#include <vector>
using namespace std;

#include "driver.hpp"

int main() {
  const int n=4, m=2; cout.precision(15);
  vector<double> xv(n), xa(n), xa1t2x(n), yv(m), yt2x(m), ya(m);
  for (int i=0;i<n;i++) { xv[i]=1; xa[i]=1; }
  for (int i=0;i<m;i++) ya[i]=1; 
  fd_driver(xv,xa,xa1t2x,yv,yt2x,ya);
  for (int i=0;i<m;i++)
    cout << "y[" << i << "]=" << yv[i] << endl;
  for (int i=0;i<n;i++)
    cout << "x_{(1)}[" << i << "]=" << xa[i] << endl;
  for (int i=0;i<m;i++)
    cout << "y^{(2)}[" << i << "]~=" << yt2x[i] << endl;
  for (int i=0;i<n;i++)
    cout << "x_{(1)}^{(2)}[" << i << "]~=" << xa1t2x[i] << endl;
  return 0;
}


