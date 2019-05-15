// joint reversal

#include<iostream>
#include<vector>
#include<stack>
using namespace std;

#include "dco.hpp"
typedef dco::ga1s<double> DCO_M;
typedef DCO_M::type DCO_T;
typedef dco::ACM::baseclass<DCO_M::tape_t,DCO_T> ACMBase;

template<typename AT, typename PT>
struct MyACM : ACMBase {

  // passive context
  PT& dt; // UWE: why const?
  // argument checkpoint
  AT acp;

  MyACM(ACMBase::tape_t *tape, PT& dt) : ACMBase(tape), dt(dt) {}

  template<typename T>
  inline void g(T& x) { x+=dt*sin(x); }

  void evaluate_primal() {
    AT x=input_value(0);
    g(x);
    output_value(0)=x;
  }

  void evaluate_augmented_primal() {
    acp=input_value(0);
    evaluate_primal();
  }

  void evaluate_adjoint() {
    DCO_M::tape_t::iterator_t tpos0=DCO_M::global_tape->get_position();
    DCO_T x=acp;
    DCO_M::global_tape->register_variable(x);
    DCO_T x_in=x;
    DCO_M::tape_t::iterator_t tpos1=DCO_M::global_tape->get_position();
    g(x);
    DCO_M::global_tape->register_output_variable(x);
    dco::derivative(x)=output_adjoint(0);
    DCO_M::global_tape->interpret_adjoint_and_reset_to(tpos1);
    input_adjoint(0)=dco::derivative(x_in);
    cout << input_adjoint(0) << endl;
    DCO_M::global_tape->reset_to(tpos0);
  }

};

int main() {
    cout.precision(15);
    DCO_M::global_tape = DCO_M::tape_t::create();
    DCO_T x=1.0,y=0;
    double dt=1.0/3;
    DCO_M::global_tape->register_variable(x);
    DCO_T x_in=x;
    DCO_M::tape_t::iterator_t tpos=DCO_M::global_tape->get_position();
    // overloading on 1st third
    x+=dt*sin(x);
    
    MyACM<double,double> *e=new MyACM<double,double>(DCO_M::global_tape, dt);
    e->register_input(x);
    e->register_output(y);
    DCO_M::global_tape->insert_ACM_object(e);
    e->evaluate_augmented_primal();
    // overloading on 3rd third
    y+=dt*sin(y);
    DCO_M::global_tape->register_output_variable(y);
    cout << "y=" <<  dco::value(y) << endl;
    dco::derivative(y)=1;
    DCO_M::global_tape->interpret_adjoint_and_reset_to(tpos);
    cout << "xa=" << dco::derivative(x_in) << endl;
    DCO_M::tape_t::remove(DCO_M::global_tape);
    return 0;
}

