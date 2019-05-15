#include <iostream>
using namespace std;

#include "driver.hpp"

int main() {
  double xv=1,pv=5,xa=1,pa=0;
  driver(pv,pa,xv,xa);
  cout.precision(15);
  cout << "x=" << xv << endl;
  cout << "p_{(1)}=" << pa << endl;
  return 0;
}
