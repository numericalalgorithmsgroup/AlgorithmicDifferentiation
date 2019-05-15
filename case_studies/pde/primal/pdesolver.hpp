#include "../ad_data_view.hpp"

template<typename ATYPE>
class CrankNicholson {
  public:
    const ACTIVE_INPUTS<ATYPE>& X;
    const PASSIVE_INPUTS& XP;
    ATYPE *LHSj_dl,*LHSj_d,*LHSj_du,*RHSj;
    ATYPE xmin, xmax, tmax, *Vprev, *Vcurr;
    double tmin;
    CrankNicholson(const ACTIVE_INPUTS<ATYPE>& X,
		   const PASSIVE_INPUTS& XP) :
	X(X), XP(XP), 
        LHSj_dl(new ATYPE[XP.N-1]),
        LHSj_d(new ATYPE[XP.N]),
        LHSj_du(new ATYPE[XP.N-1]),
        Vprev( new ATYPE[XP.N+2]), 
        Vcurr( new ATYPE[XP.N+2]) {}
    ~CrankNicholson() {
      delete [] LHSj_dl;
      delete [] LHSj_d;
      delete [] LHSj_du;
      delete [] Vcurr;
      delete [] Vprev;
    }
    void swapVs() {
      ATYPE * tmp = Vcurr;
      Vcurr = Vprev;
      Vprev = tmp;
    }
  private:
    CrankNicholson();
    CrankNicholson(const CrankNicholson&);
    CrankNicholson operator=(const CrankNicholson&);
  public:
  void setBoundaryConditions(int ts, ATYPE *V);
  void prepareLHS(int ts); 
  void prepareRHS(int); 
  void solveTridiagonalSystem();
};

#include "pdesolver.impl.hpp"
