#ifndef __LOCALVOLPARAMS_INCLUDED_
#define __LOCALVOLPARAMS_INCLUDED_

#include<vector>
using namespace std;

template<typename ATYPE>
struct LocalVolSurface {
    int m, n;
    vector<ATYPE> a, b;
    explicit LocalVolSurface() : m(0), n(0) { }
    LocalVolSurface(istream &in) {
        in >> m >> n;
        a.resize(m+1);
        b.resize(n+1);
        for(int i=0; i<=m; i++) in >> a[i];
        for(int i=0; i<=n; i++) in >> b[i];
    }
    // squared volatilities; usually through interpolation
    // from measured market data
    ATYPE operator()(const ATYPE& x, const ATYPE& t) const { 
      // Horner
      ATYPE ax=a[m];
      for(int i=m-1; i>=0; i--) ax = a[i] + x*ax;
      ATYPE bx=b[n];
      for(int i=n-1;i>=0;i--) bx = b[i] + x*bx;
      return t*ax/bx;
    }
};

#endif
