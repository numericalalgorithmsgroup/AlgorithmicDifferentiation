#include <iostream>
using namespace std;

#include "driver.hpp"

int main() {
  cout.precision(15); 
  int n=10; int m=10; 
  double xv=2.1,xa=0.0,yv,ya=1.0;
  driver(n,m,xv,xa,yv,ya);
  cout << "y=" << yv << endl;
  cout << "x_{(1)}=" << xa << endl;
  return 0;
}

