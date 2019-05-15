
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

template<typename DCO_MODE>
void mcpath_fill_gap( 
    typename DCO_MODE::external_adjoint_object_t* D) 
{
  typedef typename DCO_MODE::type DCO_TYPE;
  typedef typename DCO_MODE::value_t DCO_VALUE_TYPE;
  typedef typename DCO_MODE::tape_t DCO_TAPE_TYPE;
  DCO_TAPE_TYPE* DCO_TAPE_POINTER=DCO_MODE::global_tape;
  typedef typename DCO_TAPE_TYPE::iterator_t DCO_TAPE_POSITION_TYPE;

  // recover local checkpoint
  const ACTIVE_INPUTS<DCO_TYPE>* const &Xp=D->template read_data<const ACTIVE_INPUTS<DCO_TYPE>*>();
  PASSIVE_INPUTS * const &XPp=D->template read_data<PASSIVE_INPUTS*>();
  for (int i=0;i<6;i++)
    XPp->rngseed[i]=D->template read_data<double>();

  DCO_TAPE_POSITION_TYPE mc_path_begin = DCO_TAPE_POINTER->get_position();

  DCO_TYPE V=mcpath(*Xp,*XPp);

  DCO_TAPE_POINTER->register_output_variable(V);
  static int c=0;
  if(!c++) cerr << "Tape size (gap filled): " << dco::size_of(DCO_TAPE_POINTER)/1.e6 << "MB" << endl << endl;
  DCO_VALUE_TYPE V_v=D->get_output_adjoint();
  dco::derivative(V)=V_v;
  DCO_TAPE_POINTER->interpret_adjoint_and_reset_to(mc_path_begin);
}

template<typename DCO_TYPE>
DCO_TYPE mcpath_make_gap(
  const ACTIVE_INPUTS<DCO_TYPE> &X,
  const PASSIVE_INPUTS &XP) 
{
  typedef dco::mode<DCO_TYPE> DCO_MODE;
  typedef typename DCO_MODE::value_t DCO_VALUE_TYPE;
  typedef typename DCO_MODE::tape_t DCO_TAPE_TYPE;
  DCO_TAPE_TYPE* DCO_TAPE_POINTER=DCO_MODE::global_tape;
  typedef typename DCO_MODE::external_adjoint_object_t DCO_EAO_TYPE;

  DCO_EAO_TYPE *D = DCO_TAPE_POINTER->template create_callback_object<DCO_EAO_TYPE>();
// need values of active inputs exactly once
// as they remain same for all paths
  static ACTIVE_INPUTS<DCO_VALUE_TYPE> X_v(X.get_value());
// write local checkpoint
//
// checkpointing active inputs ensures
// correct propagation of adjoints 
// when filling the gap by tape interpretation
//
// neither active nor passive inputs are overwritten
// by remainder program (except XP.rngseed)
  D->write_data(&X);
  D->write_data(&XP);
// seed for rng is overwritten repeatedly, i.e. needs to be checkpointed
  for (int i=0;i<6;i++)
    D->write_data(XP.rngseed[i]);

  // passive Monte Carlo simulation
  DCO_VALUE_TYPE V_v=mcpath(X_v,XP);
  DCO_TYPE V=D->register_output(V_v,DCO_TAPE_POINTER);
  DCO_TAPE_POINTER->insert_callback(&mcpath_fill_gap<DCO_MODE>,D);
  return V;
}

template<typename ATYPE>
void price(
    const ACTIVE_INPUTS<ATYPE> &X,
    const PASSIVE_INPUTS &XP,
    ACTIVE_OUTPUTS<ATYPE>& Y, 
    PASSIVE_OUTPUTS& YP
) {
  typedef typename dco::mode<ATYPE>::type DCO_TYPE;
    Y.V=0;
    ATYPE sumsq=0;
    for(int p=0; p<XP.N; p++) {
      ATYPE y=mcpath_make_gap<DCO_TYPE>(X,XP);
      Y.V+=y;
      sumsq+=y*y;
    }
    Y.V=Y.V/XP.N;
    YP.ci = dco::passive_value((ATYPE)(sqrt((sumsq/XP.N - Y.V*Y.V)/XP.N)));
}


