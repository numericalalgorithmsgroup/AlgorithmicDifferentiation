#include<vector>
using namespace std;

#include "dco.hpp"
using namespace dco;

#include "f.hpp" 

void t2s_a1s_Hessian(
                     const vector<double>& xv,   
                     double& yv, 	      
                     vector<vector<double> >& hessian     
) {
  typedef gt1s<double> DCO_BASE_MODE;
  typedef DCO_BASE_MODE::type DCO_BASE_TYPE;
  typedef ga1s<DCO_BASE_TYPE> DCO_MODE;
  typedef DCO_MODE::type DCO_TYPE;
  typedef DCO_MODE::tape_t DCO_TAPE_TYPE;

  DCO_MODE::global_tape=DCO_TAPE_TYPE::create();

  const size_t n=xv.size();

  vector<DCO_TYPE> x(n); DCO_TYPE y;
  for (size_t i=0;i<n;i++) x[i]=xv[i];

  for (size_t i=0;i<n;i++) {

    for (size_t j=0;j<n;j++)
      DCO_MODE::global_tape->register_variable(x[j]);

    derivative(value(x[i])) = 1.0;

    f(x,y);

    DCO_MODE::global_tape->register_output_variable(y);
    derivative(y) = 1.0;
      
    DCO_MODE::global_tape->interpret_adjoint();
    
    for (size_t j = 0; j <= i; ++j)
      hessian[i][j] = derivative( derivative(x[j]) );
    
    derivative(value(x[i])) = 0.0;
    DCO_MODE::global_tape->reset();
  }

  DCO_TAPE_TYPE::remove(DCO_MODE::global_tape);
  yv = passive_value(y);
}

//--- reverse-over-reverse with ga1s<ga1s<double>::type>::type data
//--- type. see reverse-over-reverse section in Uwe's book
//--- p. 108. here are a bunch of things hidden one could talk about.
void a2s_a1s_Hessian(
    const vector<double>& xv,   
    double& yv, 	      
    vector<vector<double> >& hessian     
) {

  ga1s<double>::global_tape = ga1s<double>::tape_t::create();
  ga1s<ga1s<double>::type>::global_tape = ga1s<ga1s<double>::type>::tape_t::create();

  const size_t n=xv.size();

  vector<ga1s<ga1s<double>::type>::type> x(n); ga1s<ga1s<double>::type>::type y;
  for (size_t i=0;i<n;i++) x[i]=xv[i];

  for (size_t j=0;j<n;j++) {
    ga1s<double>::global_tape->register_variable(value(x[j]));
    ga1s<ga1s<double>::type>::global_tape->register_variable(x[j]);
  }  

  f(x,y); // important thing: just one recording step.

  ga1s<ga1s<double>::type>::global_tape->register_output_variable(y);
  derivative(y) = 1.0;
      
  ga1s<ga1s<double>::type>::global_tape->interpret_adjoint();
  
  for (size_t i=0;i<n;i++) {
    derivative(derivative(x[i])) = 1.0;
    ga1s<double>::global_tape->interpret_adjoint();
    
    for (size_t j = 0; j <= i; ++j)
      hessian[i][j] = derivative( value(x[j]) );
    
    ga1s<double>::global_tape->zero_adjoints();
  }

  ga1s<double>::tape_t::remove(ga1s<double>::global_tape);
  ga1s<ga1s<double>::type>::tape_t::remove(ga1s<ga1s<double>::type>::global_tape);
  yv = passive_value(y);
}
