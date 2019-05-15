#include <vector> 
using namespace std;

#include "dco.hpp" 
using namespace dco;

#include "f.hpp"

#ifdef DCO_CPP11
static const unsigned long VECTOR_SIZE = 8;
typedef gv<double,VECTOR_SIZE> DCO_BASE_MODE;
typedef DCO_BASE_MODE::type DCO_BASE_TYPE;
typedef ga1s<DCO_BASE_TYPE> DCO_MODE;
typedef DCO_MODE::type DCO_TYPE;
typedef DCO_MODE::tape_t DCO_TAPE_TYPE;

void driver(
            const vector<double>& xv, vector<double>& xa,     
            vector<double>& yv, vector<double>& ya      
) {
  DCO_MODE::global_tape=DCO_TAPE_TYPE::create();

  const size_t n=xv.size();
  DCO_TYPE vec_x, vec_y;
  for (auto range : dco::subranges<VECTOR_SIZE>(n)) {
    for (auto i : range) { 
      value(vec_x)[i.sub_index]=xv[i.global_index];
    }
    DCO_MODE::global_tape->register_variable(vec_x);
    f(vec_x,vec_y);
    DCO_MODE::global_tape->register_output_variable(vec_y);
    for (auto i : range) { 
      yv[i.global_index]=value(vec_y)[i.sub_index];
      derivative(vec_y)[i.sub_index]=ya[i.global_index];
      derivative(vec_x)[i.sub_index]=xa[i.global_index];
    }
    DCO_MODE::global_tape->interpret_adjoint();
    for (auto i : range) { 
      ya[i.global_index]=derivative(vec_y)[i.sub_index];
      xa[i.global_index]=derivative(vec_x)[i.sub_index];
    }
    DCO_MODE::global_tape->reset();
  }
  DCO_TAPE_TYPE::remove(DCO_MODE::global_tape);
}
#else
typedef double DCO_BASE_TYPE;
typedef ga1s<DCO_BASE_TYPE> DCO_MODE;
typedef DCO_MODE::type DCO_TYPE;
typedef DCO_MODE::tape_t DCO_TAPE_TYPE;

void driver(
            const vector<double>& xv, vector<double>& xa,     
            vector<double>& yv, vector<double>& ya      
) {
  DCO_MODE::global_tape=DCO_TAPE_TYPE::create();

  const size_t n=xv.size();
  DCO_TYPE x, y;
  for (size_t i=0;i<n;i++) {  
    value(x)=xv[i];
    DCO_MODE::global_tape->register_variable(x);
    f(x,y);
    DCO_MODE::global_tape->register_output_variable(y);
    yv[i]=value(y);
    derivative(y)=ya[i];
    derivative(x)=xa[i];
    DCO_MODE::global_tape->interpret_adjoint();
    ya[i]=derivative(y);
    xa[i]=derivative(x);
    DCO_MODE::global_tape->reset();
  }
  DCO_TAPE_TYPE::remove(DCO_MODE::global_tape);
}
#endif
