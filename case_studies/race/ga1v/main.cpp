#include<vector>
#include<iostream>
using namespace std;
#include "dco.hpp"
using namespace dco;
#include "../x22.hpp"

template<typename T>
void ga1v_driver(const vector<T>& xv, T& yv, vector<T>& g) {
  typedef ga1v<T,1> DCO_MODE;
  typedef typename DCO_MODE::type DCO_TYPE;
  typedef typename DCO_MODE::tape_t DCO_TAPE_TYPE;
  size_t n=xv.size();
  vector<DCO_TYPE> x(n); DCO_TYPE y;

  DCO_MODE::global_tape=DCO_TAPE_TYPE::create();
  for (size_t j=0;j<n;j++) {
    DCO_MODE::global_tape->register_variable(x[j]);
    value(x[j])=xv[j];
  }
  f(x,y);
  DCO_MODE::global_tape->register_output_variable(y);
  yv=value(y);
  derivative(y)[0]=1;
  DCO_MODE::global_tape->interpret_adjoint();
  for (size_t j=0;j<n;j++) g[j]=derivative(x[j])[0];
  DCO_TAPE_TYPE::remove(DCO_MODE::global_tape);
}

int main(int c, char* v[]) {
  assert(c==2); (void)c;
  cout.precision(15);
  size_t n=atoi(v[1]); 
  vector<double> x(n), g(n); double y; 
  for (size_t i=0;i<n;i++) x[i]=cos(double(i)); 
  ga1v_driver(x,y,g); 
  cout << y << endl;
  for (size_t i=0;i<n;i++) 
    cout << g[i] << endl; 
  return 0;
}
