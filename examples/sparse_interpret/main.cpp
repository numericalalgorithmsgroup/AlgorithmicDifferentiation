#include "dco.hpp"

typedef dco::ga1s<double> DCO_MODE;
typedef DCO_MODE::type DCO_TYPE;
typedef DCO_MODE::tape_t DCO_TAPE_TYPE;

int main() {
  
  DCO_MODE::global_tape = DCO_TAPE_TYPE::create();
  DCO_TYPE x(0.0);

  DCO_MODE::global_tape->register_variable(x);
  
  DCO_TYPE t = sqrt(x*x); (void) t; // unused...
  DCO_TYPE y = 2*x;
  
  dco::derivative(y) = 1.0;
  DCO_MODE::global_tape->interpret_adjoint();

  std::cerr << "Adjoint of x without sparse interpretation: " << dco::derivative(x) << std::endl;
  
  DCO_MODE::global_tape->zero_adjoints();
  DCO_MODE::global_tape->sparse_interpret() = true;

  dco::derivative(y) = 1.0;
  DCO_MODE::global_tape->interpret_adjoint();

  std::cout << "Adjoint of x with sparse interpretation: " << dco::derivative(x) << std::endl;

  DCO_TAPE_TYPE::remove(DCO_MODE::global_tape);
}
