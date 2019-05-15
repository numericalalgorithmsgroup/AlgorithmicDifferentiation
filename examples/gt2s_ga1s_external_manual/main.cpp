#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

#include "driver.hpp" 

int main() {
    cout.precision(15);
    int n=5; 
    vector<double> x(n), xa1(n), xt2(n), xa1t2(n);
    double y, ya1, yt2, ya1t2;
    for (int i=0;i<n;i++) { x[i]=cos(double(i)); xt2[i]=1; xa1[i]=0; xa1t2[i]=0; }
    y=0, yt2=0, ya1=1; ya1t2=0;
    driver(x,xt2,xa1,xa1t2,y,yt2,ya1,ya1t2);
    cout << "y=" << y << endl;
    for (int i=0;i<n;i++)
        cout << "x_{(1)}[" << i << "]=" << xa1[i] << endl;
    cout << "y^{(2)}=" << yt2 << endl;
    for (int i=0;i<n;i++)
        cout << "x_{(1)}^{(2)}[" << i << "]=" << xa1t2[i] << endl;
    cout << "y_{(1)}=" << ya1 << endl;
    cout << "y_{(1)}^{(2)}=" << ya1t2 << endl;
    return 0;
}
