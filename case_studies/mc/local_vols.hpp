#ifndef __LOCAL_VOL_SURFACE_INCLUDED_
#define __LOCAL_VOL_SURFACE_INCLUDED_

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
    typedef typename dco::mode<ATYPE>::value_t AD_VALUE_TYPE;
    LocalVolSurface<AD_VALUE_TYPE>
    get_value() const {
      LocalVolSurface<AD_VALUE_TYPE> S;
      S.m=m;
      S.n=n;
      typename vector<ATYPE>::const_iterator i=a.begin();
      for (;i!=a.end();i++) S.a.push_back(dco::value(*i));

      i=b.begin();
      for (;i!=b.end();i++) S.b.push_back(dco::value(*i));
      return S;
    }
};

#endif
