#include "g.hpp"

template<typename DCO_TYPE>
void f(DCO_TYPE p, DCO_TYPE& x) {
  p=exp(p);
  g(p,x);
  x=x*p;
}

