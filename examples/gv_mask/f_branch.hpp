template<typename T>
void f(const T& x, T& y) {
  T v=sin(x*x);
  T w=-cos(v); 
  y=v*w;
  if (y < -0.5) y += sin(exp(x));
}
