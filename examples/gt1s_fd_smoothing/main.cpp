#include <cstdlib>
#include <iostream>
using namespace std;

#include "driver.hpp"

int main() {
    double x = 0.1,xt1=1;
    driver(x,xt1);
    cout.precision(15);
    cout << "x=" << x << endl;
    cout << "x^{(1)}=" << xt1 << endl;
    return 0;
}
