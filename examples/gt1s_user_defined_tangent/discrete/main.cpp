#include <iostream>
using namespace std;

#include "driver.hpp"

int main() {
  double x=1,p=5,xt1=0,pt1=1;
  driver(p,pt1,x,xt1);
  cout.precision(15);
  cout << "x=" << x << endl;
  cout << "x^{(1)}=" << xt1 << endl;
  return 0;
}
