#include <cassert>
#include <iostream>
using namespace std;

#include <dco.hpp>
typedef dco::gt1s<double> T1S_MODE;
typedef T1S_MODE::type T1S_TYPE;

#include "../config.h"
#include "../ad_data_view.hpp"
#include "../primal/pdesolver.hpp"

int main(int argc, char* argv[]) {
  if(argc!=2) { cerr << "Please specify input scenario file, e.g. scenario_1.in\n"; exit(-1); }
  cout.precision(15);
  ifstream vols(argv[1]); 
  if(vols.fail()) { cerr << "Cannot open scenario file '" << argv[1] << "'\n"; exit(-1); }
  ACTIVE_INPUTS<T1S_TYPE> X(S0,r,K,T,vols); vols.close();
  PASSIVE_INPUTS XP(N,M);
  ACTIVE_OUTPUTS<T1S_TYPE> Y; 

  // XM[xmsz] is an array pointing to all active inputs
  unsigned int xmsz = 4+X.sigmaSq.a.size()+X.sigmaSq.b.size();
  T1S_TYPE **XM=new T1S_TYPE*[xmsz];
  XM[0]=&X.S0; XM[1]=&X.r; XM[2]=&X.K; XM[3]=&X.T;
  for (unsigned int i=0;i<X.sigmaSq.a.size();i++)
    XM[i+4]=&X.sigmaSq.a[i];
  for (unsigned int i=0;i<X.sigmaSq.b.size();i++)
    XM[i+4+X.sigmaSq.a.size()]=&X.sigmaSq.b[i];

  for (unsigned int i=0;i<xmsz;i++) {
    dco::derivative(*XM[i])=1; 
    price(X,XP,Y);
    if (!i) cout << "Y=" << dco::value(Y.V) << endl;
    cout << "dY/dX[" << i << "]=" << dco::derivative(Y.V) << endl;
    dco::derivative(*XM[i])=0.0;
  }

  delete [] XM;
  return 0;
}
