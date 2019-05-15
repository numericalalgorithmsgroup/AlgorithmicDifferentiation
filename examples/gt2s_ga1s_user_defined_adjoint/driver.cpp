#include<iostream>
using namespace std;

#include "dco.hpp"
using namespace dco;

typedef gt1s<double> DCO_BASE_MODE;
typedef DCO_BASE_MODE::type DCO_BASE_TYPE;
typedef ga1s<DCO_BASE_TYPE> DCO_MODE;
typedef DCO_MODE::type DCO_TYPE;
typedef DCO_MODE::tape_t DCO_TAPE_TYPE;

#include "f.hpp"

void driver(const double& pv, const double& pt2, double& pa1, double& pa1t2,
	    double &xv, double& xt2, const double& xa1, const double& xa1t2) {
  DCO_TYPE p,x;
  passive_value(p)=pv;
  derivative(value(p))=pt2;
  passive_value(x)=xv;
  DCO_MODE::global_tape=DCO_TAPE_TYPE::create();
  DCO_MODE::global_tape->register_variable(p);
  f(p,x);
  cerr << "ts=" << dco::size_of(DCO_MODE::global_tape) << "B" << endl;
  xv=passive_value(x);
  xt2=derivative(value(x));
  DCO_MODE::global_tape->register_output_variable(x);
  value(derivative(x))=xa1;
  derivative(derivative(x))=xa1t2;
  value(derivative(p))=pa1;
  derivative(derivative(p))=pa1t2;
  DCO_MODE::global_tape->interpret_adjoint();
  pa1=value(derivative(p));
  pa1t2=derivative(derivative(p));
  DCO_TAPE_TYPE::remove(DCO_MODE::global_tape); 
}
