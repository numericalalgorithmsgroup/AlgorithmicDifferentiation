#include<iostream>
#include<vector>
using namespace std;

#include "driver.hpp" 

int main() {
  const int n=4,m=2; cout.precision(15);
  vector<double> xv(n), xa1(n), xt2(n), xa1t2(n);
  vector<double> yv(m), ya1(m), yt2(m), ya1t2(m);
  for (int i=0;i<n;i++) { xv[i]=1; xt2[i]=1; xa1[i]=1; xa1t2[i]=0; }
  for (int i=0;i<m;i++) { ya1[i]=1; ya1t2[i]=0; }
  driver(xv,xt2,xa1,xa1t2,yv,yt2,ya1,ya1t2);
  for (int i=0;i<m;i++)
    cout << "y[" << i << "]=" << yv[i] << endl;
  for (int i=0;i<n;i++)
    cout << "x_{(1)}[" << i << "]=" << xa1[i] << endl;
  for (int i=0;i<m;i++)
    cout << "y^{(2)}[" << i << "]=" << yt2[i] << endl;
  for (int i=0;i<n;i++)
    cout << "x_{(1)}^{(2)}[" << i << "]=" << xa1t2[i] << endl;
  return 0;
}
