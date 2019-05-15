#include<iostream>
#include<vector>
using namespace std;

#include "driver.hpp"

int main() {
  const int n=4, m=2; cout.precision(15);
  vector<double> x(n), y(m); 
  vector<vector<double> > J(m,x);
  vector<vector<double> > Hm(n,x);
  vector<vector<vector<double> > > H(m,Hm);
  // initialization of inputs
  for (int i=0;i<n;i++) x[i]=1; 
  // driver 
  t2s_t1s_driver(x,y,J,H);
  // results
  for (int j=0;j<m;j++)
    cout << "y[" << j << "]=" << y[j] << endl;
  for (int j=0;j<m;j++)
    for (int i=0;i<n;i++)
      cout << "F'[" << j << "][" << i << "]=" << J[j][i] << endl;
  for (int j=0;j<m;j++)
    for (int i1=0;i1<n;i1++)
      for (int i2=0;i2<n;i2++)
        cout << "F''[" << j << "][" << i1 << "][" << i2 
	     << "]=" << H[j][i1][i2] << endl;
  return 0;
}
