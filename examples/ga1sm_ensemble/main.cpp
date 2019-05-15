#include <cassert>
#include <cstdlib>
#include <iostream>
using namespace std;

#include "driver.hpp"

int main(int argc, char* argv[]) {
    cout.precision(15);
    int n = 10, m = 10;
    if (argc==3) {
        n=atoi(argv[1]); assert(n>0);
        m=atoi(argv[2]); assert(m>0);
    }
    double x=2.1,xa1=0.0,y,ya1=1.0;
    driver(n,m,x,xa1,y,ya1);
    cout << "y=" << y << endl;
    cout << "x_{(1)}=" << xa1 << endl;
    return 0;
}

