#include<iostream>
using namespace std;

#include "dco.hpp"
using namespace dco;

typedef ga1s<double> DCO_MODE;
typedef DCO_MODE::type DCO_TYPE;
typedef DCO_MODE::tape_t DCO_TAPE_TYPE;
typedef DCO_TAPE_TYPE::iterator_t DCO_TAPE_POSITION_TYPE;

#include "f.hpp"

void driver (const double& pv, double& pa, double& xv, const double& xa) {
  DCO_MODE::global_tape=DCO_TAPE_TYPE::create();
  DCO_TYPE x=xv,p=pv;
  DCO_MODE::global_tape->register_variable(p);
  f(p,x); 
  cerr << "ts=" << dco::size_of(DCO_MODE::global_tape) << "B" << endl;
  xv=value(x);
  DCO_MODE::global_tape->register_output_variable(x);
  derivative(x)=xa;
  DCO_MODE::global_tape->interpret_adjoint();
  pa=derivative(p);
  DCO_TAPE_TYPE::remove(DCO_MODE::global_tape);
}
