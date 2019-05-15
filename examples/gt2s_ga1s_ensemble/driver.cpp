#include "dco.hpp"
using namespace dco;

typedef gt1s<double> DCO_BASE_MODE;
typedef DCO_BASE_MODE::type DCO_BASE_TYPE;
typedef ga1s<DCO_BASE_TYPE> DCO_MODE;
typedef DCO_MODE::type DCO_TYPE;
typedef DCO_MODE::tape_t DCO_TAPE_TYPE;
typedef DCO_TAPE_TYPE::iterator_t DCO_TAPE_POSITION_TYPE;

#include "f.hpp"

void driver(const int n, const int m, 
            const double& xv, const double& xt2, double& xa1, double& xa1t2,
	    double &yv, double& yt2, const double& ya1, const double& ya1t2) {
  DCO_TYPE x=xv,y;
  derivative(value(x))=xt2;
  DCO_MODE::global_tape=DCO_TAPE_TYPE::create();
  DCO_MODE::global_tape->register_variable(x);
  DCO_TAPE_POSITION_TYPE p=DCO_MODE::global_tape->get_position();
  f(n,m,x,y);
  cerr << "ts0=" << dco::size_of(DCO_MODE::global_tape) << "B" << endl;
  yv=passive_value(y);
  yt2=derivative(value(y));
  DCO_MODE::global_tape->register_output_variable(y);
  value(derivative(y))=ya1;
  derivative(derivative(y))=ya1t2;
  value(derivative(x))=xa1;
  derivative(derivative(x))=xa1t2;
  DCO_MODE::global_tape->interpret_adjoint_and_reset_to(p);
  xa1=value(derivative(x));
  xa1t2=derivative(derivative(x));
  DCO_TAPE_TYPE::remove(DCO_MODE::global_tape); 
}
