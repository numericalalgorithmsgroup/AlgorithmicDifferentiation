#include "g.hpp"

template<typename DCO_BASE_TYPE>
void gt1(int n, DCO_BASE_TYPE& x, DCO_BASE_TYPE& xt1) {
  for (int i=0;i<n;i++) { 
    xt1=cos(x)*xt1;
    x=sin(x);
  }
}

template<typename DCO_TYPE>
void g_make_gap(int n, DCO_TYPE &x) {
    typedef typename dco::mode<DCO_TYPE> DCO_MODE;
    typedef typename DCO_MODE::value_t DCO_VALUE_TYPE;
    typedef typename DCO_MODE::local_gradient_t local_gradient_t;

    DCO_TYPE xc = x; // copy required because output=input
    local_gradient_t y1o(x);
    // new tape index for output x

    DCO_VALUE_TYPE xt1=1.;
    gt1(n,value(x),xt1); // value of x changed

    y1o.put(xc, xt1); // add edge from new output to input
}
