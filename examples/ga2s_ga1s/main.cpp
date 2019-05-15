#include<iostream>
#include<vector>
using namespace std;

#include "driver.hpp" 

int main() {
  const int n=4,m=2; cout.precision(15);
  vector<double> xv(n), xa1(n), xa2(n), xa1a2(n);
  vector<double> yv(m), ya1(m), ya2(m), ya1a2(m);
  for (int i=0;i<n;i++) { xv[i]=1; xa2[i]=1; xa1[i]=1; xa1a2[i]=1; }
  for (int i=0;i<m;i++) { ya2[i]=1; ya1a2[i]=1; ya1[i]=1;}
  driver(xv,xa2,xa1,xa1a2,yv,ya2,ya1,ya1a2);
  for (int i=0;i<m;i++)
    cout << "y[" << i << "]=" << yv[i] << endl;
  for (int i=0;i<m;i++)
    cout << "y_{(1)}[" << i << "]=" << ya1[i] << endl;
  for (int i=0;i<n;i++)
    cout << "x_{(2)}[" << i << "]=" << xa2[i] << endl;
  for (int i=0;i<m;i++)
    cout << "y_{(1,2)}[" << i << "]=" << ya1a2[i] << endl;
  for (int i=0;i<n;i++)
    cout << "x_{(1)}[" << i << "]=" << xa1[i] << endl;
  for (int i=0;i<n;i++)
    cout << "x_{(1,2)}[" << i << "]=" << xa1a2[i] << endl;
  return 0;
}
