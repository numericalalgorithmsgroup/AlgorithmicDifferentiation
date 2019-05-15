#include<cmath>
using namespace std;

template<typename ATYPE>
void g(
    int n,
    ATYPE& x 
) {
      for (int i=0;i<n;i++) x=sin(x);
}

