#include <iostream>
#include <cmath>
using namespace std;

#include "dco.hpp"
using namespace dco;
typedef ga1s<double> DCO_MODE;
typedef DCO_MODE::type DCO_TYPE;
typedef DCO_MODE::tape_t DCO_TAPE_TYPE;
typedef DCO_TAPE_TYPE::iterator_t DCO_TAPE_POSITION_TYPE;

#include "f.hpp"

void driver(const int n, double& xv, double& xa) {
  DCO_TYPE x=xv; 
  DCO_MODE::global_tape=DCO_TAPE_TYPE::create();
  DCO_MODE::global_tape->register_variable(x);
  DCO_TYPE x_in=x;
  DCO_TAPE_POSITION_TYPE p=DCO_MODE::global_tape->get_position();
  f(n,x);
  derivative(x)=xa;
  cerr << "ts0=" << dco::size_of(DCO_MODE::global_tape) << "B" << endl;
  DCO_MODE::global_tape->interpret_adjoint_and_reset_to(p);
  xv=value(x);
  xa=derivative(x_in);
  DCO_TAPE_TYPE::remove(DCO_MODE::global_tape);
}
