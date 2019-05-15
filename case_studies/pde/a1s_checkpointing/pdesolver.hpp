
#include "../ad_data_view.hpp"

template<typename ATYPE>
class CrankNicholson {
  public:
    static const ACTIVE_INPUTS<ATYPE>* X_p;
    static const PASSIVE_INPUTS* XP_p; 
    static ATYPE xmin, xmax, tmax; 
    static double tmin; 
    ATYPE *LHSj_dl,*LHSj_d,*LHSj_du; 
    ATYPE *RHSj; 
    ATYPE *Vprev, *Vcurr; 
    CrankNicholson() :
        LHSj_dl(new ATYPE[XP_p->N-1]),
        LHSj_d(new ATYPE[XP_p->N]),
        LHSj_du(new ATYPE[XP_p->N-1]),
        Vprev( new ATYPE[XP_p->N+2]),
        Vcurr( new ATYPE[XP_p->N+2]) {}
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
    CrankNicholson(const CrankNicholson& copy); 
    CrankNicholson operator=(const CrankNicholson& rhs);
  public:
  void setBoundaryConditions(int,ATYPE*);
  void prepareLHS(int); 
  void prepareRHS(int); 
  void solveTridiagonalSystem();
};

template<typename ATYPE>
const ACTIVE_INPUTS<ATYPE>* CrankNicholson<ATYPE>::X_p=0;
template<typename ATYPE>
const PASSIVE_INPUTS* CrankNicholson<ATYPE>::XP_p=0;
template<typename ATYPE>
ATYPE CrankNicholson<ATYPE>::xmin=0;
template<typename ATYPE>
ATYPE CrankNicholson<ATYPE>::xmax=0;
template<typename ATYPE>
double CrankNicholson<ATYPE>::tmin=0;
template<typename ATYPE>
ATYPE CrankNicholson<ATYPE>::tmax=0;

#include "pdesolver.impl.hpp"
