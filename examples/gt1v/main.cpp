#include<iostream>
#include<vector>
using namespace std;

#include "driver.hpp"

int main() {
  cout.precision(15);
  const int m=2, n=4; 
  vector<double> x(n),y(m);
  vector<vector<double> > xt1(n, vector<double>(n)), yt1(m, vector<double>(n));
  for (int i=0;i<n;i++) { 
    x[i]=1; 
    for (int j=0;j<n;j++) xt1[i][j]=0;
    xt1[i][i]=1; 
  }
  driver(x,xt1,y,yt1);
  for (int j=0;j<m;j++) 
    cout << "y[" << j << "]=" << y[j] << endl;
  for (int j=0;j<m;j++) 
    for (int i=0;i<n;i++) 
      cout << "y^{(1)}[" << j << "][" << i << "]=" 
	   << yt1[j][i] << endl;
  return 0;
}

