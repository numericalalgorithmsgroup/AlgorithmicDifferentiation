#include<iostream>
#include<cmath>
using namespace std;
#include <omp.h>

#include "dco.hpp"
typedef dco::ga1s<double> DCO_MODE;
typedef DCO_MODE::type DCO_TYPE;
typedef DCO_MODE::tape_t DCO_TAPE_TYPE;

#include "f.h"

void driver() {
  const int n=1000;
  double x0=1;
  vector<DCO_TYPE> p(n,1); 
  DCO_MODE::global_tape=DCO_TAPE_TYPE::create();
  for (int i=0;i<n;i++) 
    DCO_MODE::global_tape->register_variable(p[i]);
  DCO_TYPE x=x0; 
  euler(0,n,x,p);
  DCO_MODE::global_tape->register_output_variable(x);

  omp_set_num_threads(2);
  float adjoint_float;
  double adjoint_double;

  //** this is required, since the global_tape pointer is threadlocal;
  //** alternatively, use compile-time flag -DDCO_NO_THREADLOCAL and
  //** just use DCO_MODE::global_tape in both threads.
  DCO_MODE::tape_t* shared_global_tape = DCO_MODE::global_tape;
  
#pragma omp parallel
  {
    switch (omp_get_thread_num()) {
    case 0: {
      dco::adjoint_vector<DCO_TAPE_TYPE,float> 
        av_float(shared_global_tape);
      dco::derivative(x, av_float)=1;
      av_float.interpret_adjoint();
      adjoint_float = dco::derivative(p[n/2], av_float);
      break;
    }
    case 1: {
      dco::adjoint_vector<DCO_TAPE_TYPE,double> 
        av_double(shared_global_tape);
      dco::derivative(x, av_double)=1;
      av_double.interpret_adjoint();
      adjoint_double = dco::derivative(p[n/2], av_double);
    }
    default: {}
    }
  }

  cout << "float " << "dx/dp=" << adjoint_float << endl;
  cout << "double " << "dx/dp=" << adjoint_double << endl;

  DCO_TAPE_TYPE::remove(DCO_MODE::global_tape);
}
