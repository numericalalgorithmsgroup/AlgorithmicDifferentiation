#include<vector>
using namespace std;

#include "dco.hpp" 
using namespace dco;

typedef gt1s<double> DCO_BASE_MODE;
typedef DCO_BASE_MODE::type DCO_BASE_TYPE;
typedef ga1s<DCO_BASE_TYPE> DCO_MODE;
typedef DCO_MODE::type DCO_TYPE;
typedef DCO_MODE::tape_t DCO_TAPE_TYPE;
typedef DCO_TAPE_TYPE::iterator_t DCO_TAPE_POSITION_TYPE;

#include "../ga1s_external_manual/f.hpp" 

void driver(
    const vector<double>& xv,   
    const vector<double>& xt2, 
    vector<double>& xa1,       
    vector<double>& xa1t2,     
    double& yv, 	               
    double& yt2,               
    double& ya1,               
    double& ya1t2              
) {
  ga1s<DCO_BASE_TYPE>::global_tape=ga1s<DCO_BASE_TYPE>::tape_t::create();
  const size_t n=xv.size();
  vector<DCO_TYPE> x(n), x_in(n); DCO_TYPE y;
  for (size_t i=0;i<n;i++) {
    ga1s<DCO_BASE_TYPE>::global_tape->register_variable(x[i]);
    value(value(x[i]))=xv[i];
    derivative(value(x[i]))=xt2[i];
    x_in[i]=x[i];
  }
  DCO_TAPE_POSITION_TYPE p=DCO_MODE::global_tape->get_position();
  f(x,y);
  cerr << "ts=" << dco::size_of(DCO_MODE::global_tape) << "B" << endl;
  for (size_t i=0;i<n;i++) {
    value(derivative(x_in[i]))=xa1[i];
    derivative(derivative(x_in[i]))=xa1t2[i];
  }
  yv=value(value(y));
  yt2=derivative(value(y));
  ga1s<DCO_BASE_TYPE>::global_tape->register_output_variable(y);
  value(derivative(y))=ya1;
  derivative(derivative(y))=ya1t2;
  ga1s<DCO_BASE_TYPE>::global_tape->interpret_adjoint_and_reset_to(p);
  for (size_t i=0;i<n;i++) {
    xa1[i]=value(derivative(x_in[i]));
    xa1t2[i]=derivative(derivative(x_in[i]));
  }
  ga1s<DCO_BASE_TYPE>::tape_t::remove(ga1s<DCO_BASE_TYPE>::global_tape);
}
