#include <cassert>
#include <cstdlib>
#include <iostream>
using namespace std;

#include "driver.hpp"

int main() {
  cout.precision(15);
  int n=10; int m=10; 
  double x=2.1,xt2=1.0,xa1=0.0,xa1t2=0.0,y,yt2,ya1=1.0,ya1t2=0.0;
  driver(n,m,x,xt2,xa1,xa1t2,y,yt2,ya1,ya1t2);
  cout << "y=" << y << endl;
  cout << "y^{(2)}=" << yt2 << endl;
  cout << "x_{(1)}=" << xa1 << endl;
  cout << "x_{(1)}^{(2)}=" << xa1t2 << endl;
  return 0;
}

