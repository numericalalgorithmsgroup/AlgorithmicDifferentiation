#include<vector>

#include "g.hpp"
#include "g_a1s.hpp"

template<typename DCO_MODE>
void g_fill_gap(typename DCO_MODE::external_adjoint_object_t *D) {
  typedef typename DCO_MODE::value_t DCO_VALUE_TYPE;
  const int &n=D->template read_data<int>();
  vector<DCO_VALUE_TYPE> xa1(n);
  DCO_VALUE_TYPE ya1=D->get_output_adjoint(); 
  g_a1s<DCO_VALUE_TYPE>(xa1,ya1);
  for (int i=0;i<n;i++) D->increment_input_adjoint(xa1[i]);
}

template<typename DCO_TYPE>
void g_make_gap(std::vector<DCO_TYPE>& x, DCO_TYPE &y) {
    typedef dco::mode<DCO_TYPE> DCO_MODE;
    typedef typename DCO_MODE::value_t DCO_VALUE_TYPE;
    typedef typename DCO_MODE::external_adjoint_object_t DCO_EAO_TYPE;
    DCO_EAO_TYPE *D = DCO_MODE::global_tape->template create_callback_object<DCO_EAO_TYPE>();

    size_t n=x.size();
    vector<DCO_VALUE_TYPE> xv(n);
    for (size_t i=0;i<n;i++) xv[i]=D->register_input(x[i]); 
    D->write_data(n);
    DCO_VALUE_TYPE yv;
    g<DCO_VALUE_TYPE>(xv,yv);
    y=D->register_output(yv);
    DCO_MODE::global_tape->insert_callback(g_fill_gap<DCO_MODE>,D);
}

