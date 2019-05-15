#include <cstdlib>
#include <iostream>
#include <fstream>
using namespace std;
#include "dco.hpp"
using namespace dco;

typedef gt1s<gt1s<double>::type>::type DCO_TYPE;

#include "../include/f.hpp"

int main(int argc, char* argv[]){
  if (argc!=3) {
    cerr << "2 parameters expected:" << endl
	 << "  1. number of spatial finite difference grid points" << endl
	 << "  2. number of implicit Euler steps" << endl;
    return -1;
  }
  size_t n=atoi(argv[1]), m=atoi(argv[2]);
  vector<double> c(n);
  for (size_t i=0;i<n;i++) c[i]=0.01;
  vector<double> T(n);
  for (size_t i=0;i<n-1;i++) T[i]=300.;
  T[n-1]=1700.;
  ifstream ifs("O.txt");
  vector<double> O(n);
  for (size_t i=0;i<n;i++) ifs >> O[i] ;
  vector<vector<double> > d2vdc2(n,vector<double>(n,0));
  vector<DCO_TYPE> ca(n);
  vector<DCO_TYPE> Ta(n);
  DCO_TYPE va;
  for(size_t i=0;i<n;i++) { 
    for(size_t j=0;j<n;j++) { 
      for(size_t k=0;k<n;k++) { ca[k]=c[k]; Ta[k]=T[k]; }
      value(derivative(ca[i]))=1.0; derivative(value(ca[j]))=1.0;
      f(ca,m,Ta,O,va);
      d2vdc2[i][j]=derivative(derivative(va));
    }
  }
  cout.precision(15);
  for(size_t i=0;i<n;i++) 
    for(size_t j=0;j<n;j++) 
      cout << "dvdc[" << i << "][" << j << "]=" << d2vdc2[i][j] << endl;
  return 0;
}
