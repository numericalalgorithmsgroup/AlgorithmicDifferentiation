#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "../include/f.hpp"

int main(int argc, char* argv[]){
  cout.precision(15);
  if (argc!=3) {
    cerr << "2 parameters expected:" << endl
	 << "  1. number of spatial finite difference grid points" << endl
	 << "  2. number of implicit Euler steps" << endl;
    return -1;
  }
  size_t  n=atoi(argv[1]), m=atoi(argv[2]);
  vector<double> c(n);
  for (size_t i=0;i<n;i++) c[i]=0.01;
  vector<double> T(n);
  for (size_t i=0;i<n-1;i++) T[i]=300.;
  T[n-1]=1700.;
  vector<double> O(n,0);
  double v;
  ofstream ofs("O.txt");
  f(c,m,T,O,v);
  for (size_t i=0;i<n;i++) ofs << T[i]+(double) rand()/RAND_MAX << endl;
  return 0;
}
