#include "g_gap.hpp"

template<typename AD_MODE>
void f(
    int n,     
    int stride,     
    typename AD_MODE::type& x
) {
  // g(n,x); // for split reversal
  g_make_gap<AD_MODE>(n,stride,x);
}

