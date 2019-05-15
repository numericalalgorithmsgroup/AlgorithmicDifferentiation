#include <iostream>
using namespace std;

#include "driver.hpp"

int main() {
    cout.precision(15);
    int n=10; int m=2; 
    double xv=2.1, xa=1.0;
    driver(n,m,xv,xa);
    cout << "x=" << xv << endl;
    cout << "x_{(1)}=" << xa << endl;
    return 0;
}

