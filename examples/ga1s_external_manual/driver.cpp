#include <vector>
using namespace std;

#include "dco.hpp"
using namespace dco;
typedef ga1s<double> DCO_MODE;
typedef DCO_MODE::type DCO_TYPE;
typedef DCO_MODE::tape_t DCO_TAPE_TYPE;
typedef DCO_TAPE_TYPE::iterator_t DCO_TAPE_POSITION_TYPE;

#include "f.hpp"

void driver(
    const vector<double>& xv, 
    vector<double>& xa1,      
    double& yv,               
    double& ya1    
) {
  size_t n=xv.size();
  vector<DCO_TYPE> x(n);
  vector<DCO_TYPE> x_in(n);
  DCO_MODE::global_tape=DCO_TAPE_TYPE::create();
  for (size_t i=0;i<n;i++) {
    DCO_MODE::global_tape->register_variable(x[i]);
    value(x[i])=xv[i];
    derivative(x[i])=xa1[i];
    x_in[i]=x[i];
  }
  DCO_TYPE y;
  DCO_TAPE_POSITION_TYPE p=DCO_MODE::global_tape->get_position();
  f(x,y);
  cerr << "ts=" << dco::size_of(DCO_MODE::global_tape) << "B" << endl;
  yv=value(y);
  derivative(y)=ya1;
  DCO_MODE::global_tape->interpret_adjoint_and_reset_to(p);
  for (size_t i=0;i<n;i++) 
    xa1[i]=derivative(x_in[i]); 
  DCO_TAPE_TYPE::remove(DCO_MODE::global_tape);
}

