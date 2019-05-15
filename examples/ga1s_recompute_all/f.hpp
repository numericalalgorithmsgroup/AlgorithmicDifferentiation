#include "g_gap.hpp"

template<typename AD_MODE>
void f(
    int n,     
    typename AD_MODE::type& x
) {
  x=sin(x);
  // g(n-2,x); // for split reversal
  g_make_gap<AD_MODE>(n-2,x);
  x=sin(x);
}

