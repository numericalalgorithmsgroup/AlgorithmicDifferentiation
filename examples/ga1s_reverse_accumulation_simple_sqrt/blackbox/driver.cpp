#include <iostream>
using namespace std;
#include "dco.hpp"

#include "my_sqrt.hpp"

void driver (const double& p, double& pa1, double& x, double& xa1) {
  dco::ga1s<double>::global_tape= dco::ga1s<double>::tape_t::create();
  dco::ga1s<double>::type a1s_x=x,a1s_p=p;
  dco::ga1s<double>::global_tape->register_variable(a1s_p);
  my_sqrt(a1s_p,a1s_x); 
  my_sqrt(a1s_p,a1s_x); 
  cerr << "tape size=" << dco::size_of(dco::ga1s<double>::global_tape) << endl;
  dco::value(a1s_x) = x;
  dco::ga1s<double>::global_tape->register_output_variable(a1s_x);
  dco::derivative(a1s_x) = xa1;
  dco::ga1s<double>::global_tape->interpret_adjoint();
  pa1 = dco::derivative(a1s_p);
  dco::ga1s<double>::tape_t::remove(dco::ga1s<double>::global_tape);
}
