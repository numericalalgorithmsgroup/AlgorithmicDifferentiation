#include<iostream>
using namespace std;
#include "g.hpp"

template<typename DCO_MODE>
void g_fill_gap(
    typename DCO_MODE::tape_t &tape,
    typename DCO_MODE::external_adjoint_object_t*D) {
  typedef typename DCO_MODE::type DCO_TYPE;
  typedef typename DCO_MODE::tape_t DCO_TAPE_TYPE;
  typedef typename DCO_TAPE_TYPE::iterator_t DCO_TAPE_POSITION_TYPE;
  
  const int &m=D->template read_data<int>();
  const DCO_TYPE* const &x_p=
    D->template read_data<const DCO_TYPE*>();
  const double &r=D->template read_data<const double>();
  DCO_TAPE_POSITION_TYPE p=tape.get_position();
  DCO_TYPE y;
  g(m,*x_p,r,y);
  derivative(y)=D->get_output_adjoint(); 
  tape.interpret_adjoint_and_reset_to(p);
}

template<typename DCO_TYPE>
void g_make_gap(int m, const DCO_TYPE& x, const double& r, DCO_TYPE& y) {
  typedef dco::mode<DCO_TYPE> DCO_MODE;
  typedef typename DCO_MODE::value_t DCO_VALUE_TYPE;
  typedef typename DCO_MODE::external_adjoint_object_t DCO_EAO_TYPE;

  typename DCO_MODE::tape_t* tape_p=dco::tape(x);
  DCO_EAO_TYPE *D=tape_p->
    template create_callback_object<DCO_EAO_TYPE>();
  D->write_data(m); D->write_data(&x); D->write_data(r);
  DCO_VALUE_TYPE yp;
  g(m,value(x),r,yp);
  y=D->register_output(yp,tape_p);
  cerr << "tape size=" << dco::size_of(tape_p) << "MB" << endl;
  tape_p->insert_callback(g_fill_gap<DCO_MODE>,D);
}
