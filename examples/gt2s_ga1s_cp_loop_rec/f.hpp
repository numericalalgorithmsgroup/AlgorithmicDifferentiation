#include "g_gap.hpp"

template<typename AD_MODE>
void f(
    int from,   
    int to,     
    int stride, // max number of consecutive tapings
    typename AD_MODE::type& x
) {
  //g(from,to,stride,x); // for split reversal
  g_make_gap<AD_MODE>(from,to,stride,x);
}

