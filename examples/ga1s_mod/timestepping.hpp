#include <cmath>

template<typename T>
void f(const int n, T& x, const T& p) { 
  double dt=1./n, t=0;
  for (int i=0;i<n;i++,t+=dt) x+=dt*p*sin(x*t);
}
