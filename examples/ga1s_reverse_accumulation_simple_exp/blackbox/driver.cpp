#include <iostream>
using namespace std;
#include "dco.hpp"
using namespace dco;

#include "my_exp.hpp"

void driver (const double& p, double& pa1, double& x, double& xa1) {
  ga1s<double>::global_tape= ga1s<double>::tape_t::create();
  ga1s<double>::type a1s_x=x,a1s_p=p;
  ga1s<double>::global_tape->register_variable(a1s_p);
  my_exp(a1s_p,a1s_x); 
  my_exp(a1s_p,a1s_x); 
  cerr << "tape size=" << dco::size_of(dco::ga1s<double>::global_tape) << endl;
  x = value(a1s_x);
  ga1s<double>::global_tape->register_output_variable(a1s_x);
  derivative(a1s_x) = xa1;
  ga1s<double>::global_tape->interpret_adjoint();
  pa1 = derivative(a1s_p);
  ga1s<double>::tape_t::remove(ga1s<double>::global_tape);
}
