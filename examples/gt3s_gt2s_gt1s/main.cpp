#include<iostream>
#include<vector>
using namespace std;

#include "driver.hpp"

int main() {
  const int n=4, m=2; cout.precision(15);
  vector<double> x(n), xt3(n), xt1(n), xt1t3(n), xt2(n), xt2t3(n), xt1t2(n), xt1t2t3(n);
  vector<double> y(m), yt3(m), yt1(m), yt1t3(m), yt2(m), yt2t3(m), yt1t2(m), yt1t2t3(m);
  for (int i=0;i<n;i++) x[i]=xt3[i]=xt1[i]=xt1t3[i]=xt2[i]=xt2t3[i]=xt1t2[i]=xt1t2t3[i]=1;
  driver(x,xt3,xt1,xt1t3,xt2,xt2t3,xt1t2,xt1t2t3,
         y,yt3,yt1,yt1t3,yt2,yt2t3,yt1t2,yt1t2t3);
  for (int j=0;j<m;j++)
    cout << "y[" << j << "]=" << y[j] << endl;
  for (int j=0;j<m;j++)
    cout << "y^{(3)}[" << j << "]=" << yt3[j] << endl;
  for (int j=0;j<m;j++)
    cout << "y^{(1)}[" << j << "]=" << yt1[j] << endl;
  for (int j=0;j<m;j++)
    cout << "y^{(1,3)}[" << j << "]=" << yt1t3[j] << endl;
  for (int j=0;j<m;j++)
    cout << "y^{(2)}[" << j << "]=" << yt2[j] << endl;
  for (int j=0;j<m;j++)
    cout << "y^{(2,3)}[" << j << "]=" << yt2t3[j] << endl;
  for (int j=0;j<m;j++)
    cout << "y^{(1,2)}[" << j << "]=" << yt1t2[j] << endl;
  for (int j=0;j<m;j++)
    cout << "y^{(1,2,3)}[" << j << "]=" << yt1t2t3[j] << endl;
  return 0;
}
