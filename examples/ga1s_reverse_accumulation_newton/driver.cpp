#include <iostream>
using namespace std;
#include "dco.hpp"

// #include "my_sqrt.hpp"
#include "my_exp.hpp"

void driver (const double& p, double& pa1, double& x, double& xa1) {
  my_exp(p,x); 
  dco::ga1s<double>::global_tape= dco::ga1s<double>::tape_t::create();
  dco::ga1s<double>::type a1s_x=x,a1s_p=p;
  dco::ga1s<double>::global_tape->register_variable(a1s_p);
  dco::ga1s<double>::tape_t::iterator_t i=dco::ga1s<double>::global_tape->get_position();
  my_exp(a1s_p,a1s_x); 
  cerr << "size of global tape = " << dco::size_of(dco::ga1s<double>::global_tape) << endl;
  x = dco::value(a1s_x);
  dco::ga1s<double>::global_tape->register_output_variable(a1s_x);
  double xa1_old=xa1+1;
  while (std::fabs(xa1_old-xa1)>1e-15) { 
    xa1_old=xa1;
    dco::derivative(a1s_x) = xa1;
    dco::ga1s<double>::global_tape->interpret_adjoint();
    dco::ga1s<double>::global_tape->zero_adjoints_to(i);
    xa1 = dco::derivative(a1s_x);
    cout << ".";
  }
  pa1 = dco::derivative(a1s_p);
  dco::ga1s<double>::tape_t::remove(dco::ga1s<double>::global_tape);
}
