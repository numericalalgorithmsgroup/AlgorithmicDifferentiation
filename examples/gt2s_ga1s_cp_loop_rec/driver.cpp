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
typedef DCO_TAPE_TYPE::iterator_t DCO_TAPE_ITERATOR_TYPE;

#define VERBOSE

#include "f.hpp"

void driver(const int n, const int stride, double& x, double& xt2, double& xa1, double& xt2a1) {
  DCO_TYPE t2s_a1s_x;
  DCO_BASE_TYPE v;
  v = value(t2s_a1s_x);
  value(v) = x;
  derivative(v) = xt2;
  value(t2s_a1s_x) = v;
  DCO_MODE::global_tape=DCO_TAPE_TYPE::create();
  DCO_MODE::global_tape->register_variable(t2s_a1s_x);
  DCO_TYPE x_indep=t2s_a1s_x;
  DCO_TAPE_ITERATOR_TYPE to_be_reset_to=DCO_MODE::global_tape->get_position();
  f<DCO_MODE>(0,n,stride,t2s_a1s_x);
  v = derivative(t2s_a1s_x);
  value(v) = xa1;
  derivative(v) = xt2a1;
  derivative(t2s_a1s_x) = v;
  DCO_MODE::global_tape->interpret_adjoint_and_reset_to(to_be_reset_to);
  v = value(t2s_a1s_x);
  x = value(v);
  xt2 = derivative(v);
  v = derivative(x_indep);
  xa1 = value(v);
  xt2a1 = derivative(v);
  DCO_TAPE_TYPE::remove(DCO_MODE::global_tape);
}
