template<class T>
void f(const vector<T> x, T& y) {
  y=0;
  for (size_t i=0;i<x.size();i++) y=y+x[i]*x[i]; 
  y=y*y;
}
