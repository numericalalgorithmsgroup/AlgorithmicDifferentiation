#include <cassert>
#include <iostream>
using namespace std;

#include <dco.hpp>
typedef dco::ga1s<double> DCO_MODE;
typedef DCO_MODE::type DCO_TYPE;
typedef DCO_MODE::tape_t DCO_TAPE_TYPE;
DCO_TAPE_TYPE*& DCO_TAPE_POINTER=DCO_MODE::global_tape;

#include "../config.h"
#include "../ad_data_view.hpp"
#include "mc.hpp"

int main(int argc, char* argv[]) {
  if(argc!=2) { cerr << "Please specify input scenario file, e.g. scenario_1.in\n"; exit(-1); }
  cout.precision(15);
  ifstream vols(argv[1]); 
  if(vols.fail()) { cerr << "Cannot open scenario file '" << argv[1] << "'\n"; exit(-1); }
  ACTIVE_INPUTS<DCO_TYPE> X(S0,r,K,T,vols); vols.close();
  PASSIVE_INPUTS XP(N,M);
  ACTIVE_OUTPUTS<DCO_TYPE> Y;
  PASSIVE_OUTPUTS YP;

  // XM[xmsz] is an array pointing to all active inputs
  unsigned int xmsz = 4+X.sigmaSq.a.size()+X.sigmaSq.b.size();
  DCO_TYPE **XM=new DCO_TYPE*[xmsz];
  XM[0]=&X.S0; XM[1]=&X.r; XM[2]=&X.K; XM[3]=&X.T;
  for (unsigned int i=0;i<X.sigmaSq.a.size();i++)
    XM[i+4]=&X.sigmaSq.a[i];
  for (unsigned int i=0;i<X.sigmaSq.b.size();i++)
    XM[i+4+X.sigmaSq.a.size()]=&X.sigmaSq.b[i];

  DCO_TAPE_POINTER=DCO_TAPE_TYPE::create();

  for (unsigned int i=0;i<xmsz;i++) 
    DCO_TAPE_POINTER->register_variable(*XM[i]);

  price(X,XP,Y,YP);

  cerr << "Tape size: " 
       << dco::size_of(DCO_TAPE_POINTER)/1.e6 
       << "MB" << endl << endl;

  DCO_TAPE_POINTER->register_output_variable(Y.V);
  dco::derivative(Y.V)=1;
  DCO_TAPE_POINTER->interpret_adjoint();

  cout << "Y=" << dco::value(Y.V) << " in (" << Y.V-3*YP.ci << ", " << Y.V+3*YP.ci << ")" << endl;

  for (unsigned int i=0;i<xmsz;i++) 
    cout << "dY/dX[" << i << "]=" << dco::derivative(*XM[i]) << endl;

  DCO_TAPE_TYPE::remove(DCO_TAPE_POINTER);
  delete [] XM;
  return 0;
}
