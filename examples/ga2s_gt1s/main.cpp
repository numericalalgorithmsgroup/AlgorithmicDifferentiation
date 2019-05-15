#include<iostream>
#include<vector>
using namespace std;

#include "driver.hpp" 

int main() {
  const int n=4,m=2; cout.precision(15);
  vector<double> xv(n), xt1(n), xa2(n), xt1a2(n);
  vector<double> yv(m), yt1(m), ya2(m), yt1a2(m);
  for (int i=0;i<n;i++) { xv[i]=1; xa2[i]=1; xt1[i]=1; xt1a2[i]=1; }
  for (int i=0;i<m;i++) { ya2[i]=1; yt1a2[i]=1; }
  driver(xv,xa2,xt1,xt1a2,yv,ya2,yt1,yt1a2);
  for (int i=0;i<m;i++)
    cout << "y[" << i << "]=" << yv[i] << endl;
  for (int i=0;i<n;i++)
    cout << "x_{(2)}[" << i << "]=" << xa2[i] << endl;
  for (int i=0;i<m;i++)
    cout << "y^{(1)}[" << i << "]=" << yt1[i] << endl;
  for (int i=0;i<n;i++)
    cout << "x_{(2)}^{(1)}[" << i << "]=" << xt1a2[i] << endl;
  return 0;
}
