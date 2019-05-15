#include "g_gap.hpp"

template<typename AD_MODE, class ATYPE>
void f(ATYPE p, ATYPE& x) {
  p=exp(p);
  g_make_gap<AD_MODE>(p,x);
  x=x*p;
}

