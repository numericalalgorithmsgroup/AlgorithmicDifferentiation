#include<vector>
#include<iostream>
using namespace std;
#include "dco.hpp"
using namespace dco;
#include "../x22.hpp"

template<typename T>
void driver(const vector<T>& xv, T& yv, vector<T>& g, vector<vector<T> >&  H) {
  typedef typename gt1s<T>::type DCO_BASE_TYPE;
  typedef ga1s<DCO_BASE_TYPE> DCO_MODE;
  typedef typename DCO_MODE::type DCO_TYPE;
  typedef typename DCO_MODE::tape_t DCO_TAPE_TYPE;
  size_t n=xv.size();
  vector<DCO_TYPE> x(n); DCO_TYPE y;

  DCO_MODE::global_tape=DCO_TAPE_TYPE::create();
  for (size_t i=0;i<n;i++) {
    for (size_t j=0;j<n;j++) {
      DCO_MODE::global_tape->register_variable(x[j]);
      passive_value(x[j])=xv[j]; 
      derivative(value(x[j]))=0; 
    }
    derivative(value(x[i]))=1; 
    f(x,y);
    DCO_MODE::global_tape->register_output_variable(y);
    yv=passive_value(y);
    g[i]=derivative(value(y));
    value(derivative(y))=1;
    DCO_MODE::global_tape->interpret_adjoint();
    for (size_t j=0;j<n;j++) H[i][j]=derivative(derivative(x[j]));
    DCO_MODE::global_tape->reset();
  }
  DCO_TAPE_TYPE::remove(DCO_MODE::global_tape);
}

int main(int c, char* v[]) {
  assert(c==2); (void)c;
  cout.precision(15);
  size_t n=atoi(v[1]);
  vector<vector<double> > H(n, vector<double>(n)); 
  vector<double> x(n), g(n); double y;
  for (size_t i=0;i<n;i++) x[i]=cos(double(i));
  driver(x,y,g,H);
  cout << y << endl;
  for (size_t i=0;i<n;i++)
    cout << g[i] << endl;
  for (size_t i=0;i<n;i++)
    for (size_t j=0;j<n;j++)
      cout << H[i][j] << endl;
  return 0;
}
