#include <vector> 
using namespace std;

#include "dco.hpp" 
using namespace dco;

#include "f.hpp"

#ifdef DCO_CPP11
typedef double DCO_BASE_TYPE;
static const unsigned long VECTOR_SIZE = 8;
typedef gv<DCO_BASE_TYPE,VECTOR_SIZE> DCO_MODE;
typedef DCO_MODE::type DCO_TYPE;

void driver(
            const vector<double>& x,
            vector<double>& y
) {
  const size_t n=x.size();
  DCO_TYPE vec_x, vec_y;
  for (auto range : dco::subranges<VECTOR_SIZE>(n)) {
    for (auto i : range) { vec_x[i.sub_index]=x[i.global_index]; }
    f(vec_x,vec_y); 
    for (auto i : range) { y[i.global_index]=vec_y[i.sub_index]; }
  }
}
#else
void driver(
            const vector<double>& x,
            vector<double>& y
) {
  const size_t n=x.size();
  for (size_t i=0;i<n;i++) { f(x[i],y[i]); }
}
#endif
