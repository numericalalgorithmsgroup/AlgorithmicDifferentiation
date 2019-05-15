#include<iostream>
#include<vector>
using namespace std;

#include "driver.hpp"

int main() {
  const int n=4, m=2; cout.precision(15);
  vector<double> xv(n), xt1(n), xt2(n), xt1t2(n);
  vector<double> yv(m), yt1(m), yt2(m), yt1t2(m);
  for (int i=0;i<n;i++) { xv[i]=1; xt1[i]=1; xt2[i]=1; xt1t2[i]=1;}
  driver(xv,xt1,xt2,xt1t2,yv,yt1,yt2,yt1t2);
  for (int i=0;i<m;i++)
    cout << "y[" << i << "]=" << yv[i] << endl;
  for (int i=0;i<m;i++)
    cout << "y^{(1)}[" << i << "]=" << yt1[i] << endl;
  for (int i=0;i<m;i++)
    cout << "y^{(2)}[" << i << "]=" << yt2[i] << endl;
  for (int i=0;i<m;i++)
    cout << "y^{(1,2)}[" << i << "]=" << yt1t2[i] << endl;
  return 0;
}
