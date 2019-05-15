#include "dco.hpp"
using namespace dco;
typedef ga1sm<double> DCO_MODE;
typedef DCO_MODE::type DCO_TYPE;
typedef DCO_MODE::tape_t DCO_TAPE_TYPE;
typedef DCO_TAPE_TYPE::iterator_t DCO_TAPE_POSITION_TYPE;

#include "f.hpp"

void driver(const int n, const int m, 
            const double& xv, double& xa1, 
	    double &yv, const double& ya1) {
  DCO_TYPE x=xv,y;
  DCO_TAPE_TYPE* tape_p=DCO_TAPE_TYPE::create();
  tape_p->register_variable(x);
  f(n,m,x,y);
  cerr << "tape size=" << dco::size_of(tape_p) << "B" << endl;
  yv=value(y);
  tape_p->register_output_variable(y);
  derivative(y)=ya1; derivative(x)=xa1;
  tape_p->interpret_adjoint();
  xa1=derivative(x);
  DCO_TAPE_TYPE::remove(tape_p); 
}
