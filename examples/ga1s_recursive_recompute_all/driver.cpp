#include <iostream>
#include <cstdlib>
#include <cassert>
using namespace std;

#include "dco.hpp"
using namespace dco;

typedef ga1s<double> DCO_MODE;
typedef DCO_MODE::type DCO_TYPE;
typedef DCO_MODE::tape_t DCO_TAPE_TYPE;
typedef DCO_TAPE_TYPE::iterator_t DCO_TAPE_POSITION_TYPE;

#include "f.hpp"

void driver(const int n, const int stride, double& xv, double& xa1) {
  DCO_TYPE x=xv;
  DCO_MODE::global_tape=DCO_TAPE_TYPE::create();
  DCO_MODE::global_tape->register_variable(x);
  DCO_TYPE x_in=x;

  f<DCO_MODE>(n,stride,x);

  DCO_MODE::global_tape->register_output_variable(x);
  derivative(x)=1;
  
  DCO_MODE::global_tape->interpret_adjoint();

  xv=value(x);
  xa1=derivative(x_in);
  DCO_TAPE_TYPE::remove(DCO_MODE::global_tape);
}

