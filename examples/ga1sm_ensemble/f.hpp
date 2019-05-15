#include "g_gap.hpp"

template<typename DCO_TYPE>
void f(int n, int m, const DCO_TYPE& x, DCO_TYPE& y) {
  double r;
  DCO_TYPE sum;
  for (int i=0;i<n;i++) {
    r=rand();
    g_make_gap(m,x,r,y);
    sum+=y;
  }
  y=sum/n;
}
