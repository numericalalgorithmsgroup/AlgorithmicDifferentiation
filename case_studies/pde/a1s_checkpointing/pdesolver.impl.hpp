#include <cmath>
using namespace std;

#include "../lapack.hpp"

template<typename ATYPE>
void CrankNicholson<ATYPE>::setBoundaryConditions(int ts, ATYPE * V) {
    const ATYPE dx = (xmax-xmin)/(XP_p->N+1);
    const ATYPE dt = X_p->T/(XP_p->M+1);

    if(ts==XP_p->M+1) {
        for(int i=1; i<XP_p->N+1; i++) {
            const ATYPE xi = xmin + i*dx;
            const ATYPE Si = exp(xi);
            if(Si-X_p->K > 0.0)
                V[i] = Si-X_p->K;
            else
                V[i] = 0.0;
        }
    }
   V[0] = 0.0;
   const ATYPE Smax = exp(xmax);
   const ATYPE t_j = ts*dt;
   V[XP_p->N+1] = Smax - exp(-X_p->r*(X_p->T-t_j))*X_p->K;
}

template<typename ATYPE>
void CrankNicholson<ATYPE>::prepareLHS(const int j_time) {
    const int j = j_time;
    const ATYPE dt = (tmax-tmin)/(XP_p->M+1);
    const ATYPE t = tmin + j*dt;
    const ATYPE dx = (xmax-xmin)/(XP_p->N+1);
    const ATYPE alpha = dt/(dx*dx);
    const ATYPE z = 1.0 + X_p->r*dt;

    int row = 0;
    ATYPE x = xmin + (row+1)*dx;
    ATYPE u_ij, l_ij, c_ij;
    ATYPE vhat = X_p->sigmaSq(x,t);
    u_ij = 0.5*alpha*( vhat + dx*(X_p->r - 0.5*vhat) ); 
    c_ij = -alpha*vhat;                            
    LHSj_du[row] =   - 0.5*u_ij;
    LHSj_d[row]  = z - 0.5*c_ij;
    for(row=1; row<XP_p->N-1; row++) {
        x = xmin + (row+1)*dx;
        vhat = X_p->sigmaSq(x,t);
        u_ij = 0.5*alpha*( vhat + dx*(X_p->r - 0.5*vhat) ); 
        l_ij = 0.5*alpha*( vhat - dx*(X_p->r - 0.5*vhat) ); 
        c_ij = -alpha*vhat;                            
        LHSj_dl[row-1] =   - 0.5*l_ij;
        LHSj_d[row]    = z - 0.5*c_ij;
        LHSj_du[row]   =   - 0.5*u_ij;
    }
    row = XP_p->N-1;
    x = xmin + (row+1)*dx;
    vhat = X_p->sigmaSq(x,t);
    l_ij = 0.5*alpha*( vhat - dx*(X_p->r - 0.5*vhat) ); 
    c_ij = -alpha*vhat;                            
    LHSj_dl[row-1] =   - 0.5*l_ij;
    LHSj_d[row]    = z - 0.5*c_ij;
}

template<typename ATYPE>
void CrankNicholson<ATYPE>::prepareRHS(const int j_time) {
    const int j = j_time;
    const ATYPE dt = (tmax-tmin)/(XP_p->M+1);
    const ATYPE t = tmin + j*dt;
    const ATYPE dx = (xmax-xmin)/(XP_p->N+1);
    const ATYPE alpha = dt/(dx*dx);

    ATYPE* RHSj_d   = new ATYPE[XP_p->N];
    ATYPE* RHSj_du  = new ATYPE[XP_p->N-1];
    ATYPE* RHSj_dl  = new ATYPE[XP_p->N-1];

    int row = 0;
    ATYPE c_ij, u_ij, l_ij;
    ATYPE x = xmin + (row+1)*dx;
    ATYPE vhat = X_p->sigmaSq(x,t);
    u_ij = 0.5*alpha*( vhat + dx*(X_p->r - 0.5*vhat) ); 
    c_ij = -alpha*vhat;                            
    RHSj_du[row] = 0.5*u_ij;
    RHSj_d[row]  = 0.5*c_ij + 1.0;
    for(row=1; row<XP_p->N-1; row++) {
        x = xmin + (row+1)*dx;
        vhat = X_p->sigmaSq(x,t);
        u_ij = 0.5*alpha*( vhat + dx*(X_p->r - 0.5*vhat) ); 
        l_ij = 0.5*alpha*( vhat - dx*(X_p->r - 0.5*vhat) ); 
        c_ij = -alpha*vhat;                            
        RHSj_dl[row-1] = 0.5*l_ij;
        RHSj_d[row]    = 0.5*c_ij + 1.0;
        RHSj_du[row]   = 0.5*u_ij;
    }
    row = XP_p->N-1;
    x = xmin + (row+1)*dx;
    vhat = X_p->sigmaSq(x,t);
    l_ij = 0.5*alpha*( vhat - dx*(X_p->r - 0.5*vhat) ); 
    c_ij = -alpha*vhat;                            
    RHSj_dl[row-1] = 0.5*l_ij;
    RHSj_d[row]    = 0.5*c_ij + 1.0; 

    row = 0;
    RHSj[row] = RHSj_d[row]*Vprev[1] + RHSj_du[row]*Vprev[2];
    x = xmin + (row+1)*dx;
    vhat = X_p->sigmaSq(x,t);
    l_ij = 0.5*alpha*( vhat - dx*(X_p->r - 0.5*vhat) ); 
    RHSj[row] += l_ij*0.5*( Vcurr[0] + Vprev[0] );
    for(row=1; row<XP_p->N-1; row++) 
        RHSj[row] = RHSj_dl[row-1]*Vprev[row] + RHSj_d[row]*Vprev[row+1] + RHSj_du[row]*Vprev[row+2];

    row = XP_p->N-1;
    x = xmin + (row+1)*dx;
    RHSj[row] = RHSj_dl[row-1]*Vprev[row] + RHSj_d[row]*Vprev[row+1];
    vhat = X_p->sigmaSq(x,t);
    u_ij = 0.5*alpha*( vhat + dx*(X_p->r - 0.5*vhat) ); 
    RHSj[row] += u_ij*0.5*( Vcurr[XP_p->N+1] + Vprev[XP_p->N+1] );

    delete[] RHSj_d;
    delete[] RHSj_dl;
    delete[] RHSj_du;
}

template<typename ATYPE>
void
CrankNicholson<ATYPE>::solveTridiagonalSystem () {
    int * LHSj_ipiv = new int[XP_p->N];
    ATYPE * LHSj_du2 = new ATYPE[XP_p->N-2];

    int info = 0;
    dgttrf(XP_p->N, LHSj_dl, LHSj_d, LHSj_du, LHSj_du2, LHSj_ipiv, &info);
    dgttrs("N", XP_p->N, 1, LHSj_dl, LHSj_d, LHSj_du, LHSj_du2, LHSj_ipiv, RHSj, XP_p->N, &info);
    delete[] LHSj_ipiv;
    delete[] LHSj_du2;
}

template<typename ATYPE> 
void several_time_steps(int from, int to, CrankNicholson<ATYPE> &CN) {
  for(int j=from; j>=to; j--) {
    CN.setBoundaryConditions(j, CN.Vcurr);
    CN.prepareLHS(j);
    CN.RHSj=&CN.Vcurr[1];
    CN.prepareRHS(j);
    CN.solveTridiagonalSystem();
    CN.swapVs();
  }
}

template<typename DCO_MODE>
inline void several_time_steps_fill_gap(
  typename DCO_MODE::external_adjoint_object_t* D) {
  typedef typename DCO_MODE::type DCO_TYPE;
  typedef typename DCO_MODE::value_t DCO_VALUE_TYPE;
  typedef typename DCO_MODE::tape_t DCO_TAPE_TYPE;
  DCO_TAPE_TYPE* DCO_TAPE_POINTER=DCO_MODE::global_tape;
  typedef typename DCO_TAPE_TYPE::iterator_t DCO_TAPE_POSITION_TYPE;

  DCO_TAPE_POSITION_TYPE gap_begin=DCO_TAPE_POINTER->get_position();
  const int& from=D->template read_data<int>();
  const int& to=D->template read_data<int>();
  CrankNicholson<DCO_TYPE> CN;
  DCO_TYPE* indep=new DCO_TYPE[CN.XP_p->N+2];
  for (int i=0;i<CN.XP_p->N+2;i++) {
    DCO_TAPE_POINTER->register_variable(CN.Vprev[i]);
    indep[i]=CN.Vprev[i];
    const DCO_VALUE_TYPE& v=D->template read_data<DCO_VALUE_TYPE>();
    dco::value(CN.Vprev[i])=v;
  }
  DCO_TAPE_POSITION_TYPE local_computation_begin = DCO_TAPE_POINTER->get_position();
  several_time_steps(from,to,CN);
  for (int i=0;i<CN.XP_p->N+2;i++) 
    DCO_TAPE_POINTER->register_output_variable(CN.Vprev[i]);

#ifndef TIMING
  cerr << "Tape size (after taping " << from-to+1 << " time steps: " << dco::size_of(DCO_TAPE_POINTER) << "B" << endl << endl;
#endif

  for (int i=0;i<CN.XP_p->N+2;i++) 
     dco::derivative(CN.Vprev[i])=D->get_output_adjoint();

  DCO_TAPE_POINTER->interpret_adjoint_and_reset_to(local_computation_begin);

#ifndef TIMING
  cerr << "Tape size (after interpreting " << from-to+1 << " time steps: " << dco::size_of(DCO_TAPE_POINTER) << "B" << endl << endl;
#endif

  for (int i=0;i<CN.XP_p->N+2;i++) 
    D->increment_input_adjoint(dco::derivative(indep[i]));
  DCO_TAPE_POINTER->reset_to(gap_begin);
  delete [] indep;
}

template<typename DCO_TYPE>
void several_time_steps_make_gap(
	int from, int to, CrankNicholson<DCO_TYPE> &CN) {
  typedef dco::mode<DCO_TYPE> DCO_MODE;
  typedef typename dco::mode<DCO_TYPE>::value_t DCO_VALUE_TYPE;
  typedef typename DCO_MODE::tape_t DCO_TAPE_TYPE;
  DCO_TAPE_TYPE* DCO_TAPE_POINTER=DCO_MODE::global_tape;
  typedef typename DCO_MODE::external_adjoint_object_t DCO_EAO_TYPE;

  DCO_EAO_TYPE *D = DCO_TAPE_POINTER->template create_callback_object<DCO_EAO_TYPE>();

  D->write_data(from);
  D->write_data(to);
  for (int i=0;i<CN.XP_p->N+2;i++) {
    DCO_VALUE_TYPE v=D->register_input(CN.Vprev[i]);
    D->write_data(v);
  }
  
  DCO_TAPE_POINTER->switch_to_passive();
  for(int j=from; j>=to; j--) {
    CN.setBoundaryConditions(j, CN.Vcurr);
    CN.prepareLHS(j);
    CN.RHSj=&CN.Vcurr[1];
    CN.prepareRHS(j);
    CN.solveTridiagonalSystem();
    CN.swapVs();
  }
  DCO_TAPE_POINTER->switch_to_active();

  for (int i=0;i<CN.XP_p->N+2;i++) 
    CN.Vprev[i]=D->register_output(dco::value(CN.Vprev[i]),DCO_TAPE_POINTER);
  DCO_TAPE_POINTER->insert_callback(&several_time_steps_fill_gap<DCO_MODE>,D);
}

template<typename ATYPE>
void price(
  const ACTIVE_INPUTS<ATYPE>& X,
  const PASSIVE_INPUTS& XP,
  ACTIVE_OUTPUTS<ATYPE>& Y) {
  //typedef typename dco::mode<ATYPE> DCO_MODE;
  CrankNicholson<ATYPE>::X_p=&X;
  CrankNicholson<ATYPE>::XP_p=&XP;
  CrankNicholson<ATYPE>::tmin=0.0;
  CrankNicholson<ATYPE>::tmax=X.T;
  CrankNicholson<ATYPE> CN;
  const ATYPE logS0 = log(X.S0);
  const ATYPE atmvol = sqrt( X.T*X.sigmaSq(logS0,X.T));
  const int C=10;
  const ATYPE dx = 2*C*atmvol/(XP.N+1);
  const ATYPE xmin = logS0 - XP.N/2*dx; 
  CrankNicholson<ATYPE>::xmin=xmin;
  const ATYPE xmax = xmin + (XP.N+1)*dx; CN.xmax=xmax;
  CrankNicholson<ATYPE>::xmax=xmax;

  CN.setBoundaryConditions(XP.M+1, CN.Vprev);
  for (int j=XP.M;j>=0;j-=checkpoint_distance) {
    int to=max(j-checkpoint_distance+1,0);
    several_time_steps_make_gap<ATYPE>(j,to,CN);
  }
  Y.V=CN.Vprev[XP.N/2];
}
