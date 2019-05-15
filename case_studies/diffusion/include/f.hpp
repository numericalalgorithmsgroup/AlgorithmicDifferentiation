#include "dco.hpp"
using namespace dco;

template <typename cTYPE, typename TTYPE>
inline void residual(const vector<cTYPE>& c, vector<TTYPE>& T) {
  size_t n=T.size();
  vector<TTYPE> T_new(n);
  for (size_t i=1;i<n-1;++i) 
    T_new[i]=c[i]*static_cast<double>(n-1)*static_cast<double>(n-1)*(T[i-1]-2*T[i]+T[i+1]);
  T[0]=0;
  for (size_t i=0;i<n;++i) T[i]=T_new[i];
  T[n-1]=0;
}

/*
template <typename TYPE>
inline void residual_jacobian(const vector<TYPE>& c, vector<TYPE>& J) {
  size_t n=c.size();
  vector<TYPE> t1_T(n);
  for (size_t i=0;i<n;++i) t1_T[i]=0;
  for (size_t i=0;i<n;++i) {
    t1_T[i]=1;
    residual(c,t1_T);
    for (size_t j=0;j<n;++j) {
      J[j*n+i]=t1_T[j];
      t1_T[j]=0;
    }
  }
}

template <typename TYPE>
inline void residual_jacobian(const vector<TYPE>& c, const vector<TYPE>& T, vector<TYPE>& J) {
  typedef typename dco::gt1s<TYPE>::type DCO_T1S_TYPE;
  size_t n=T.size();
  vector<DCO_T1S_TYPE> t1_T(n);
  for (size_t i=0;i<n;i++) t1_T[i]=T[i]; 
  for (size_t i=0;i<n;i++) {
    derivative(t1_T[i])=1;
    residual(c,t1_T);
    for (size_t j=0;j<n;++j) {
      J[j*n+i]=derivative(t1_T[j]);
      derivative(t1_T[j])=0;
    }
  }
}
*/

template <typename TYPE>
inline void residual_jacobian(const vector<TYPE>& c, const vector<TYPE>& T, vector<TYPE>& J) {
  typedef typename dco::gt1s<TYPE>::type DCO_T1S_TYPE;
  size_t n=T.size();
  vector<DCO_T1S_TYPE> t1T(n);
  const size_t bw=3;
  for (size_t i=0;i<n;i++) t1T[i]=T[i]; 
  for (size_t i=0;i<bw;i++) {
    for (size_t j=i;j<n;j+=bw) derivative(t1T[j])=1;
    residual(c,t1T);
    for (size_t j=i;j<n;j+=bw) {
      for (size_t k=(j<(bw-1)/2)? 0 : j-(bw-1)/2;k<= min(n-1,j+(bw-1)/2);k++)
        J[k*n+j]=derivative(t1T[k]);
      derivative(t1T[j])=0;
    }
    for (size_t j=0;j<n;j++) derivative(t1T[j])=0;
  }
}

template <class TYPE>
inline void LUDecomp(vector<TYPE>& A) {
  size_t n = static_cast<size_t>(sqrt(double(A.size())));
  for (size_t k=0;k<n;k++) {
    for (size_t i=k+1;i<n;i++) 
      A[i*n+k]=A[i*n+k]/A[k*n+k];
    for (size_t j=k+1;j<n;j++) 
      for (size_t i=k+1;i<n;i++) 
        A[i*n+j]=A[i*n+j]-A[i*n+k]*A[k*n+j];
  }
}

// L*y=b
template <class TYPE>
inline void FSubst(const vector<TYPE>& LU, vector<TYPE>& b) {
  size_t n=b.size();
  for (size_t i=0;i<n;i++) 
    for (size_t j=0;j<i;j++) 
      b[i]=b[i]-LU[i*n+j]*b[j];
}

// U*x=y
template <class TYPE>
inline void BSubst(const vector<TYPE>& LU, vector<TYPE>& y) {
  size_t n=y.size();
  for (size_t k=n,i=n-1;k>0;k--,i--) {
    for (size_t j=n-1;j>i;j--) 
      y[i]=y[i]-LU[i*n+j]*y[j];
    y[i]=y[i]/LU[i*n+i];
  }
}

template <class TYPE>
inline void Solve(const vector<TYPE>& LU, vector<TYPE>& b) {
  FSubst(LU,b);
  BSubst(LU,b);
}

template <typename TYPE>
inline void sim(const vector<TYPE>& c, const size_t m, vector<TYPE>& T) {
  size_t n=T.size();
  vector<TYPE> A(n*n,0);

  residual_jacobian(c,T,A);

  for (size_t i=0;i<n;++i) {
    for (size_t j=0;j<n;++j)
      A[i*n+j]=A[i*n+j]/static_cast<double>(m);
    A[i+i*n]=A[i+i*n]-1;
  }
  
  LUDecomp(A);

  for (size_t j=0;j<m;++j) {
    for (size_t i=0;i<n;++i) 
      T[i]=-T[i];
    Solve(A,T);
  }
}

template <typename TYPE, typename OTYPE>
inline void f(const vector<TYPE>& c, const size_t m, vector<TYPE>& T, const vector<OTYPE>& O, TYPE& v) {
  size_t n=T.size();
  sim(c,m,T);

  v=0;
  for (size_t i=0;i<n-1;++i)
    v=v+(T[i]-O[i])*(T[i]-O[i]);
  v=v/(static_cast<double>(n)-1);
}

