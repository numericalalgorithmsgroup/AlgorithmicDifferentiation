#include <cmath>
using namespace std;

template<typename DCO_TYPE>
void g(int n, DCO_TYPE& x) {
      for (int i=0;i<n;i++) x=sin(x);
}

