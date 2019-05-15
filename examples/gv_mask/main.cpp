#include<iostream>
#include<vector>
#include<cstdlib>
#include<cmath>
using namespace std;

#include "driver.hpp"

int main() {
  const int m=12, n=12; cout.precision(15);
  vector<double> x(n), y(m);
  for (int i=0;i<n;i++) { x[i]=sin(static_cast<double>(i+1)); }
  driver(x,y);
  for (int i=0;i<m;i++) 
    cout << "y[" << i << "]=" << y[i] << endl;
  return 0;
}
