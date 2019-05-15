#include <vector> 
using namespace std;

#include "dco.hpp" 
using namespace dco;

typedef double DCO_BASE_TYPE;
typedef gt1s<DCO_BASE_TYPE> DCO_MODE;
typedef DCO_MODE::type DCO_TYPE;

#include "f.hpp"

void driver(
    const vector<double>& xv, const vector<double>& xt, 
    vector<double>& yv, vector<double>& yt        
) {
  const size_t n=xv.size(), m=yv.size();
  vector<DCO_TYPE> x(n), y(m); 
  for (size_t i=0;i<n;i++) { value(x[i])=xv[i]; derivative(x[i])=xt[i]; }
  f(x,y); 
  for (size_t i=0;i<m;i++) { yv[i]=value(y[i]); yt[i]=derivative(y[i]); } 
}
