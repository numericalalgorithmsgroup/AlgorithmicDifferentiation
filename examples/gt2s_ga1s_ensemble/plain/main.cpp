#include<cstdlib>
#include<cmath>
#include<iostream>
using namespace std;

#include "dco.hpp"
using namespace dco;

template<typename ATYPE, typename BTYPE>
void f(const int m, const ATYPE& x, const BTYPE& r, ATYPE& y) {
  y=0;
  for (int i=0;i<m;i++) y+=sin(x+r);
}

int main() {
  int n=10; int m=10; 
  ga1s<gt1s<double>::type>::global_tape=ga1s<gt1s<double>::type>::tape_t::create();

  gt1s<double>::type v=2.1;
  derivative(v) = 1;
  ga1s<gt1s<double>::type>::type x=v;
  ga1s<gt1s<double>::type>::type y=0,sum=0;
  ga1s<gt1s<double>::type>::global_tape->register_variable(x);

  double r; 
  for (int i=0;i<n;i++) {
    r=rand();
    f(m,x,r,y);
    sum+=y;
  }
  y=sum/n;
  double max_tape_size = static_cast<double>(dco::size_of(dco::ga1s<dco::gt1s<double>::type>::global_tape));

  v = value(y);
  cout << "value=" << v << endl;
  v=1;
  derivative(y) = v;
  ga1s<gt1s<double>::type>::global_tape->interpret_adjoint();
  v = derivative(x);
  cout << "adjoint=" << v << endl;
  r = derivative(v);
  cout << "second-order adjoint=" << r << endl;
  cerr << "tape size=" << max_tape_size / 1024. / 1024. << " mb" << endl;
  return 0;
}
