#include "g.hpp"

template<class T>
void f(T& x) {
  x=sin(x);
  g(x);
  x=sin(x);
}

