#include "g_gap.hpp"

template<typename DCO_TYPE>
void f(int n, DCO_TYPE& x) {
  g(n/3,x);
  g_make_gap(n/3,x);
  g(n-n/3*2,x);
}
