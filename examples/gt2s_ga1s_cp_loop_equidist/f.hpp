#include "g_gap.hpp"

template<typename DCO_TYPE>
void f(int n, int m, DCO_TYPE& x) {
  for (int i=0;i<n;i+=m)
    g_make_gap(std::min(m,n-i),x);
}

