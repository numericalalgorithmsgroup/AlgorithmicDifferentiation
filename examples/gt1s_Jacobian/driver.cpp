#include <vector> 
using namespace std;
#include "dco.hpp" 
using namespace dco;
#include "f.hpp" 

void driver(
    const vector<double>& x,   
    vector<double>& y, 	       
    vector<vector<double> >& J // F'
) {
  const size_t n=x.size(), m=y.size();
  vector<gt1s<double>::type> t1s_x(n), t1s_y(m);
  for (size_t i=0;i<n;i++){
	  dco::value(t1s_x[i]) = x[i];
	  dco::derivative(t1s_x[i]) = 1;
  }
  for (size_t i=0;i<n;i++) {
	  dco::derivative(t1s_x[i]) = 1;
    f(t1s_x,t1s_y);
	  dco::derivative(t1s_x[i]) = 0;
    for (size_t j=0;j<m;j++) 
    	J[j][i] = dco::derivative(t1s_y[j]);
  }
  for (size_t i=0;i<m;i++) 
	  dco::derivative(t1s_y[i]) = y[i];
}
