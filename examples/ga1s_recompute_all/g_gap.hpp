#include <stack>

#include "g.hpp"
using namespace std;

template<typename DCO_MODE>
void g_fill_gap(typename DCO_MODE::external_adjoint_object_t *D);

template<typename DCO_MODE>
void g_make_gap(int n,typename DCO_MODE::type &x) {
  typedef typename DCO_MODE::value_t DCO_VALUE_TYPE;
  typedef typename DCO_MODE::external_adjoint_object_t DCO_EAO_TYPE;

  DCO_EAO_TYPE *D = DCO_MODE::global_tape->template create_callback_object<DCO_EAO_TYPE>();
  DCO_VALUE_TYPE xv=D->register_input(x); 
  D->write_data(n);
  D->write_data(xv);
  g(n,xv);
  x=D->register_output(xv);
  DCO_MODE::global_tape->insert_callback(g_fill_gap<DCO_MODE>,D);
}

template<typename DCO_MODE>
void g_fill_gap(
   typename DCO_MODE::external_adjoint_object_t *D 	
) {
  typedef typename DCO_MODE::type DCO_TYPE;
  typedef typename DCO_MODE::tape_t DCO_TAPE_TYPE;
  typedef typename DCO_MODE::value_t DCO_VALUE_TYPE;
  typedef typename DCO_TAPE_TYPE::iterator_t DCO_TAPE_POSITION_TYPE;

  const int &n=D->template read_data<int>();
  const DCO_VALUE_TYPE &xvro=D->template read_data<DCO_VALUE_TYPE>(); // read-only

  DCO_VALUE_TYPE xa=0;
  for (int i=0;i<n;i++) {
    DCO_VALUE_TYPE xv=xvro;
    g(n-i-1,xv);
    DCO_TYPE x=xv;
    DCO_TAPE_POSITION_TYPE p0=DCO_MODE::global_tape->get_position();
    DCO_MODE::global_tape->register_variable(x); 
    DCO_TYPE x_in=x;
    DCO_TAPE_POSITION_TYPE p1=DCO_MODE::global_tape->get_position();
    g(1,x);
    DCO_MODE::global_tape->register_output_variable(x); 
    if (i==0) xa=D->get_output_adjoint();
    derivative(x)=xa;
    DCO_MODE::global_tape->interpret_adjoint_to(p1);
    xa=derivative(x_in);
    DCO_MODE::global_tape->reset_to(p0);
    if (i==n-1) D->increment_input_adjoint(xa);
  }
}
