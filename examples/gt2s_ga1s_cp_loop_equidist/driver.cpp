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
// instantiate global tape 
DCO_TAPE_TYPE*& DCO_TAPE_POINTER=DCO_MODE::global_tape;

#include "f.hpp"

void driver(const int n, const int m, double& x, double& xt2, double& xa1, double& xt2a1) {
  DCO_TYPE t2s_a1s_x;
  DCO_BASE_TYPE v;
  v = value(t2s_a1s_x);
  value(v) = x;
  derivative(v) = xt2;
  value(t2s_a1s_x) = v;
  DCO_TAPE_POINTER=DCO_TAPE_TYPE::create();
  DCO_TAPE_POINTER->register_variable(t2s_a1s_x);
  DCO_TYPE x_indep=t2s_a1s_x;
  DCO_TAPE_POSITION_TYPE p=DCO_MODE::global_tape->get_position();
  f(n,m,t2s_a1s_x);
  cerr << "ts0=" << dco::size_of(DCO_MODE::global_tape) << "B" << endl;
  v = derivative(t2s_a1s_x);
  value(v) = xa1;
  derivative(v) = xt2a1;
  derivative(t2s_a1s_x) = v;
  DCO_TAPE_POINTER->interpret_adjoint_and_reset_to(p);
  v = value(t2s_a1s_x);
  x = value(v);
  xt2 = derivative(v);
  v = derivative(x_indep);
  xa1 = value(v);
  xt2a1 = derivative(v);
  DCO_TAPE_TYPE::remove(DCO_TAPE_POINTER);
}
