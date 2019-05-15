#include "dco.hpp"
using namespace dco;

typedef dco::ga1s<double> DCO_MODE;
typedef DCO_MODE::type DCO_TYPE;
typedef DCO_MODE::tape_t DCO_TAPE_TYPE;
typedef DCO_TAPE_TYPE::iterator_t DCO_TAPE_POSITION_TYPE;

#include "f.hpp"

void driver(const int n, const int m, 
            const double& xv, double& xa, 
	    double &yv, const double& ya) {
  DCO_TYPE x=xv,y;
  DCO_MODE::global_tape=DCO_TAPE_TYPE::create();
  DCO_MODE::global_tape->register_variable(x);
  DCO_TAPE_POSITION_TYPE p=DCO_MODE::global_tape->get_position();
  f(n,m,x,y);
  cerr << "ts0=" << dco::size_of(DCO_MODE::global_tape) << "B" << endl;
  yv=value(y); 
  DCO_MODE::global_tape->register_output_variable(y);
  derivative(y)=ya; derivative(x)=xa;
  DCO_MODE::global_tape->interpret_adjoint_and_reset_to(p);
  //DCO_MODE::global_tape->interpret_adjoint();
  xa=derivative(x);
  DCO_TAPE_TYPE::remove(DCO_MODE::global_tape); 
}
