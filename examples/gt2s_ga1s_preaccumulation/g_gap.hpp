#include "g.hpp"

template<typename DCO_BASE_TYPE>
void gt1(int n, DCO_BASE_TYPE& x, DCO_BASE_TYPE& xt1) {
  for (int i=0;i<n;i++) { 
    xt1=cos(x)*xt1;
    x=sin(x);
  }
}

template<typename DCO_MODE>
void g_fill_gap(
   typename DCO_MODE::external_adjoint_object_t *D 	
) {
  typedef typename DCO_MODE::value_t DCO_VALUE_TYPE;

  const DCO_VALUE_TYPE &p=D->template read_data<DCO_VALUE_TYPE>();
  DCO_VALUE_TYPE r=D->get_output_adjoint(); 
  D->increment_input_adjoint(r*p);
}

template<typename DCO_TYPE>
void g_make_gap(int n, DCO_TYPE &x) {
    typedef typename dco::mode<DCO_TYPE> DCO_MODE;
    typedef typename DCO_MODE::value_t DCO_VALUE_TYPE;
    typedef typename DCO_MODE::external_adjoint_object_t DCO_EAO_TYPE;
    DCO_EAO_TYPE *D = DCO_MODE::global_tape->template create_callback_object<DCO_EAO_TYPE>();
    DCO_VALUE_TYPE xv=D->register_input(x); 
    DCO_VALUE_TYPE xt1=1.;
    gt1(n,xv,xt1);
    D->write_data(xt1);
    x=D->register_output(xv);
    DCO_MODE::global_tape->insert_callback(g_fill_gap<DCO_MODE>,D);
}
