#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <cfloat>
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
  size_t n=atoi(argv[1]), m=atoi(argv[2]);
  vector<double> c(n);
  for (size_t i=0;i<n;i++) c[i]=0.01;
  vector<double> T(n);
  for (size_t i=0;i<n-1;i++) T[i]=300.;
  T[n-1]=1700.;
  ifstream ifs("O.txt");
  vector<double> O(n);
  for (size_t i=0;i<n;i++) ifs >> O[i] ;
  vector<double> cp(n,0),Tp(n,0);
  vector<vector<double> > d2vdc2(n,vector<double>(n,0));
  double vp1, vp2;
  for (size_t i=0;i<n;i++) {
    for (size_t j=0;j<n;j++) {
      double h=(c[j]==0) ? sqrt(sqrt(DBL_EPSILON)) : sqrt(sqrt(DBL_EPSILON))*abs(c[j]); 
      for (size_t k=0;k<n;k++) { cp[k]=c[k]; Tp[k]=T[k]; }
      cp[i]+=h; cp[j]+=h;
      f(cp,m,Tp,O,vp2);
      for (size_t k=0;k<n;k++) { cp[k]=c[k]; Tp[k]=T[k]; }
      cp[i]-=h; cp[j]+=h;
      f(cp,m,Tp,O,vp1);
      vp2-=vp1;
      for (size_t k=0;k<n;k++) { cp[k]=c[k]; Tp[k]=T[k]; }
      cp[i]+=h; cp[j]-=h;
      f(cp,m,Tp,O,vp1);
      vp2-=vp1;
      for (size_t k=0;k<n;k++) { cp[k]=c[k]; Tp[k]=T[k]; }
      cp[i]-=h; cp[j]-=h;
      f(cp,m,Tp,O,vp1);
      vp2+=vp1;
      d2vdc2[i][j]=vp2/(4*h*h);
    }
  }
  cout.precision(15);
  for (size_t i=0;i<n;i++)
    for (size_t j=0;j<n;j++)
       cout << "d2vdc2[" << i << "][" << j << "]="
               << d2vdc2[i][j] << endl;
  return 0;
}
