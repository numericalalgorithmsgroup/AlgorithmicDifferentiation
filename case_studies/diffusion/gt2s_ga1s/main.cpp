#include <cstdlib>
#include <iostream>
using namespace std;
#include "dco.hpp"
using namespace dco;
typedef ga1s<gt1s<double>::type> DCO_MODE;
typedef DCO_MODE::type DCO_TYPE;
typedef DCO_MODE::tape_t DCO_TAPE_TYPE;
typedef DCO_TAPE_TYPE::iterator_t DCO_TAPE_POSITION_TYPE;

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
  DCO_MODE::global_tape=DCO_TAPE_TYPE::create();

  for(size_t i=0;i<n;i++) {
    ca[i]=c[i];
    Ta[i]=T[i];
    DCO_MODE::global_tape->register_variable(ca[i]);
  }
  DCO_TAPE_POSITION_TYPE p=DCO_MODE::global_tape->get_position();
  for(size_t i=0;i<n;i++) {
    for(size_t j=0;j<n;j++) Ta[j]=T[j];
    if (i>0) DCO_MODE::global_tape->zero_adjoints();
    derivative(value(ca[i]))=1;
    f(ca,m,Ta,O,va);
    value(derivative(va))=1;
    DCO_MODE::global_tape->interpret_adjoint();
    for(size_t j=0;j<n;j++) derivative(value(ca[j]))=0;
    for(size_t j=0;j<n;j++) d2vdc2[j][i]=derivative(derivative(ca[j]));
    DCO_MODE::global_tape->reset_to(p);
  }
  DCO_TAPE_TYPE::remove(DCO_MODE::global_tape);
  cout.precision(15);
  for(size_t i=0;i<n;i++)
    for(size_t j=0;j<n;j++)
      cout << "d2vdc2[" << i << "][" << j << "]=" << d2vdc2[i][j] << endl;

  return 0;
}
