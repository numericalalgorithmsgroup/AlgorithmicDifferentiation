#include<cmath>
#include <vector>
using namespace std;

#include "../mrg32k3a.h"

template<typename ATYPE>
inline ATYPE mcpath(
    const ACTIVE_INPUTS<ATYPE> &X,
    const PASSIVE_INPUTS &XP) 
{
  const ATYPE mcdt=X.T/(XP.M-1);
  ATYPE logS=log(X.S0);
  ATYPE t=0;

  static std::vector<double> Z(XP.M);
  randNormal(XP.M, XP.rngseed, Z);

  for(int i=0;i<XP.M;i++) {
    t+=mcdt;
    ATYPE volS=sqrt(X.sigmaSq(logS,t));
    logS+=(X.r-0.5*volS*volS)*mcdt+volS*sqrt(mcdt)*Z[i];
  }
  ATYPE ST=exp(logS);
  return ( ST<X.K ? ATYPE(0) : exp(-X.r*X.T)*(ST-X.K) );
}

template<typename ATYPE>
void price(
    const ACTIVE_INPUTS<ATYPE> &X,
    const PASSIVE_INPUTS &XP,
    ACTIVE_OUTPUTS<ATYPE>& Y, 
    PASSIVE_OUTPUTS& YP
) {
    Y.V=0;
    ATYPE sumsq=0;
    for(int p=0; p<XP.N; p++) {
      ATYPE y=mcpath(X,XP);
      Y.V+=y;
      sumsq+=y*y;
    }
    Y.V=Y.V/XP.N;
    const ATYPE res(sqrt((sumsq/XP.N - Y.V*Y.V)/XP.N));
    YP.ci = dco::passive_value(res);
}



