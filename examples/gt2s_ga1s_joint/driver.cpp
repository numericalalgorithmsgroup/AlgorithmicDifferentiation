#include <iostream>
#include <cmath>
using namespace std;

#include "dco.hpp"

using namespace dco;

typedef gt1s<double> DCO_BASE_MODE;
typedef DCO_BASE_MODE::type DCO_BASE_TYPE;
typedef ga1s<DCO_BASE_TYPE> DCO_MODE;
typedef DCO_MODE::type DCO_TYPE;
typedef DCO_MODE::tape_t DCO_TAPE_TYPE;
typedef DCO_TAPE_TYPE::iterator_t DCO_TAPE_POSITION_TYPE;

#include "f.hpp"

void driver(const int n, double& xv, double& xt2, double& xa1, double& xt2a1) {
  DCO_TYPE x;
  passive_value(x)=xv; 
  derivative(value(x))=xt2; 
  DCO_MODE::global_tape=DCO_TAPE_TYPE::create();
  DCO_MODE::global_tape->register_variable(x);
  DCO_TYPE x_in=x;
  DCO_TAPE_POSITION_TYPE p=DCO_MODE::global_tape->get_position();
  f(n,x);
  xv=passive_value(x);
  xt2=derivative(value(x));
  value(derivative(x))=xa1; 
  derivative(derivative(x))=xt2a1; 
  DCO_MODE::global_tape->interpret_adjoint_and_reset_to(p);
  xa1=value(derivative(x_in)); 
  xt2a1=derivative(derivative(x_in)); 
  DCO_TAPE_TYPE::remove(DCO_MODE::global_tape);
}
