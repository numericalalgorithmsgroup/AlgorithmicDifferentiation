#include "g.hpp"

template<typename DCO_TYPE>
void a1s_g(DCO_TYPE& pa, const DCO_TYPE& xv, DCO_TYPE& xa) {
  pa=xa/(2*xv);
}

template<typename DCO_MODE>
void g_fill_gap(typename DCO_MODE::external_adjoint_object_t* D) {
  typedef typename DCO_MODE::value_t DCO_VALUE_TYPE;
  const DCO_VALUE_TYPE &xv = D->template read_data<DCO_VALUE_TYPE>();
  DCO_VALUE_TYPE xa,pa;
  xa=D->get_output_adjoint();
  a1s_g(pa,xv,xa);
  D->increment_input_adjoint(pa);
}

template<typename DCO_TYPE>
void g_make_gap(const DCO_TYPE& p, DCO_TYPE& x) {
  typedef mode<DCO_TYPE> DCO_MODE;
  typedef typename DCO_MODE::value_t DCO_VALUE_TYPE;
  typedef typename DCO_MODE::external_adjoint_object_t DCO_EAO_TYPE;
  DCO_EAO_TYPE *D = DCO_MODE::global_tape->template create_callback_object<DCO_EAO_TYPE>();
  DCO_VALUE_TYPE xv=value(x),pv;
  pv=D->register_input(p);
  g(pv,xv);
  x=D->register_output(xv);
  D->write_data(xv);
  DCO_MODE::global_tape->insert_callback(g_fill_gap<DCO_MODE>,D);
}
