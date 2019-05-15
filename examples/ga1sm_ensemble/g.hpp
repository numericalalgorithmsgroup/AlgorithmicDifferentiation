template<typename ATYPE>
void g(int m, const ATYPE& x, const double& r, ATYPE& y) {
  y=0;
  for (int i=0;i<m;i++) y+=sin(x+r);
}
