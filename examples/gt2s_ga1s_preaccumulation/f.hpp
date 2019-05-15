#include "g_gap.hpp"

template<typename AD_TYPE>
void f(int n, AD_TYPE& x) {
  g(n/3,x);
  g(n/3,x);
  // g_make_gap(n/3,x);
  g(n-n/3*2,x);
}
