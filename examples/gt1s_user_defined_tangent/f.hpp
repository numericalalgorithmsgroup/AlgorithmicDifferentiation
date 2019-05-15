#include "g.hpp"

template<class T>
void f(T p, T& x) {
  p=exp(p);
  g(p,x);
  x=x*p;
}

