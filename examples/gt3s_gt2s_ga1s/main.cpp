#include<iostream>
#include<vector>
using namespace std;

#include "driver.hpp" 

int main() {
  const int n=4,m=2;
  vector<double> x(n), xt3(n), xa1(n), xa1t3(n), xt2(n), xt2t3(n), xa1t2(n), xa1t2t3(n);
  vector<double> y(m), yt3(m), ya1(m), ya1t3(m), yt2(m), yt2t3(m), ya1t2(m), ya1t2t3(m);
  // initialization of inputs
  for (int i=0;i<n;i++) x[i]=xt3[i]=xt2[i]=xt2t3[i]=xa1[i]=xa1t3[i]=xa1t2[i]=xa1t2t3[i]=1;
  for (int j=0;j<m;j++) ya1[j]=ya1t3[j]=ya1t2[j]=ya1t2t3[j]=1;
  // driver
  driver(x,xt3,xt2,xt2t3,xa1,xa1t3,xa1t2,xa1t2t3,
     y,yt3,yt2,yt2t3,ya1,ya1t3,ya1t2,ya1t2t3);
  // results
  for (int j=0;j<m;j++)
    cout << "y[" << j << "]=" << y[j] << endl;
  for (int j=0;j<m;j++)
    cout << "y^{(3)}[" << j << "]=" << yt3[j] << endl;
  for (int i=0;i<n;i++)
    cout << "x_{(1)}[" << i << "]=" << xa1[i] << endl;
  for (int i=0;i<n;i++)
    cout << "x_{(1)}^{(3)}[" << i << "]=" << xa1t3[i] << endl;
  for (int j=0;j<m;j++)
    cout << "y^{(2)}[" << j << "]=" << yt2[j] << endl;
  for (int j=0;j<m;j++)
    cout << "y^{(2,3)}[" << j << "]=" << yt2t3[j] << endl;
  for (int i=0;i<n;i++)
    cout << "x_{(1)}^{(2)}[" << i << "]=" << xa1t2[i] << endl;
  for (int i=0;i<n;i++)
    cout << "x_{(1)}^{(2,3)}[" << i << "]=" << xa1t2t3[i] << endl;
  for (int j=0;j<m;j++)
    cout << "y_{(1)}[" << j << "]=" << ya1[j] << endl;
  for (int j=0;j<m;j++)
    cout << "y_{(1)}^{(3)}[" << j << "]=" << ya1t3[j] << endl;
  for (int j=0;j<m;j++)
    cout << "y_{(1)}^{(2)}[" << j << "]=" << ya1t2[j] << endl;
  for (int j=0;j<m;j++)
    cout << "y_{(1)}^{(2,3)}[" << j << "]=" << ya1t2t3[j] << endl;
  return 0;
}
