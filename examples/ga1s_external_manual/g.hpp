#include<vector>

template<typename DCO_TYPE>
void g(std::vector<DCO_TYPE> x, DCO_TYPE& y) {
  y=0;
  for (unsigned i=0;i<x.size();i++) y+=x[i]; 
}
