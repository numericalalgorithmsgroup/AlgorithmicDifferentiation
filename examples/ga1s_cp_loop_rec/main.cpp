#include <cassert>
#include <cstdlib>
#include <iostream>
using namespace std;

#include "driver.hpp"

int main() {
  cout.precision(15);
  int n=10;
  int stride=2;
  double x=2.1,xa1=1.0;
  driver(n,stride,x,xa1);
  cout << "x=" << x << endl;
  cout << "x_{(1)}=" << xa1 << endl;
  return 0;
}

