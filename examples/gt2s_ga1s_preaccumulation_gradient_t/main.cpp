#include <cassert>
#include <cstdlib>
#include <iostream>
using namespace std;

#include "driver.hpp"

int main() {
    int n=10; cout.precision(15);
    double x=2.1,xa1=1.0,xt2=1.0,xt2a1=0.0;
    driver(n,x,xt2,xa1,xt2a1);
    cout << "x=" << x << endl;
    cout << "x^{(2)}=" << xt2 << endl;
    cout << "x_{(1)}=" << xa1 << endl;
    cout << "x_{(1)}^{(2)}=" << xt2a1 << endl;
    return 0;
}

