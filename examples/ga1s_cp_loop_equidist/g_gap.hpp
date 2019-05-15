#include "g.hpp"

template<typename DCO_MODE>
void g_fill_gap(typename DCO_MODE::external_adjoint_object_t *D) {
  typedef typename DCO_MODE::type DCO_TYPE;
  typedef typename DCO_MODE::value_t DCO_VALUE_TYPE;
  typedef typename DCO_MODE::tape_t DCO_TAPE_TYPE;
  typedef typename DCO_TAPE_TYPE::iterator_t DCO_TAPE_POSITION_TYPE;

  DCO_TAPE_POSITION_TYPE p0=DCO_MODE::global_tape->get_position();
  const int &n=D->template read_data<int>();
  DCO_TYPE x=D->template read_data<DCO_VALUE_TYPE>();
  const int &c=D->template read_data<int>();
  DCO_MODE::global_tape->register_variable(x); 
  DCO_TYPE x_in=x;
  DCO_TAPE_POSITION_TYPE p1=DCO_MODE::global_tape->get_position();
  g(n,x);
  cerr << "ts" << c << "=" 
       << dco::size_of(DCO_MODE::global_tape) << "MB" << endl;
  derivative(x)=D->get_output_adjoint(); 
  DCO_MODE::global_tape->interpret_adjoint_and_reset_to(p1);
  D->increment_input_adjoint(derivative(x_in));
  DCO_MODE::global_tape->reset_to(p0);
}

template<typename DCO_TYPE>
void g_make_gap(int n, DCO_TYPE &x) {
  typedef dco::mode<DCO_TYPE> DCO_MODE;
  typedef typename DCO_MODE::value_t DCO_VALUE_TYPE;
  typedef typename DCO_MODE::external_adjoint_object_t DCO_EAO_TYPE;
  static int c=1;

  DCO_EAO_TYPE *D = DCO_MODE::global_tape->template create_callback_object<DCO_EAO_TYPE>();
  DCO_VALUE_TYPE xp=D->register_input(x); 
  D->write_data(n); D->write_data(xp); D->write_data(c++);
  g(n,xp);
  x=D->register_output(xp);
  DCO_MODE::global_tape->insert_callback(g_fill_gap<DCO_MODE>,D);
}

