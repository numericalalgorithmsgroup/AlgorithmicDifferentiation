#include <iostream>
using namespace std;

#include "driver.hpp"

int main() {
  double x=1,p=5,xa1=1,pa1=0;
  driver(p,pa1,x,xa1);
  cout.precision(15);
  cout << "x=" << x << endl;
  cout << "p_{(1)}=" << pa1 << endl;
  return 0;
}
