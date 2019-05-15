#include <stack>

#include "g.hpp"
using namespace std;

enum RUN_MODE { 
	CHECKPOINT_ARGUMENTS_AND_RUN_PASSIVELY, 
	GENERATE_TAPE 
};

template<typename DCO_MODE>
class my_external_adjoint_object_t : public DCO_MODE::external_adjoint_object_t{
  public:
    typedef typename DCO_MODE::value_t DCO_VALUE_TYPE;
    static stack<pair<int,DCO_VALUE_TYPE> > state;
    static int stride;
    my_external_adjoint_object_t(pair<int,int> p) : DCO_MODE::external_adjoint_object_t(p) {} 
};

template<typename DCO_MODE>
stack<pair<int,typename my_external_adjoint_object_t<DCO_MODE>::DCO_VALUE_TYPE> > my_external_adjoint_object_t<DCO_MODE>::state;
template<typename DCO_MODE>
int my_external_adjoint_object_t<DCO_MODE>::stride;

template<typename DCO_MODE>
void g_fill_gap(my_external_adjoint_object_t<DCO_MODE> *D);

template<typename DCO_MODE>
void g_make_gap(int from, int to, int stride,        
    typename DCO_MODE::type &x, RUN_MODE m=GENERATE_TAPE) {
  typedef typename DCO_MODE::value_t DCO_VALUE_TYPE;
  typedef my_external_adjoint_object_t<DCO_MODE> DCO_EAO_TYPE;

  if (m==CHECKPOINT_ARGUMENTS_AND_RUN_PASSIVELY) {
    cout << "STORE CHECKPOINT FOR SECTION " 
	 << from << " ... " << to-1 << endl;
    DCO_EAO_TYPE *D = DCO_MODE::global_tape->template create_callback_object<DCO_EAO_TYPE>(make_pair(1,1));
    DCO_VALUE_TYPE xv=D->register_input(x); 
    
    // write argument checkpoint (FIFO)
    D->write_data(from);
    D->write_data(to);
    if (D->state.empty()||from!=D->state.top().first) {
      cout << "PUSHING (" << from << ", " << xv << ")" << endl;
      D->state.push(make_pair(from,xv));
    }
    
    // call passive version of f
    cout << "RUN SECTION " << from << " ... " 
	 << to-1 << " PASSIVELY" << endl;
    g(from,to,stride,xv);

    // register output x with tape and store its
    // position for retrieval of incoming adjoint required
    // during interpretation
    x=D->register_output(xv);
    DCO_MODE::global_tape->insert_callback(g_fill_gap<DCO_MODE>,D);

  } else if (m==GENERATE_TAPE) {
    cout << "GENERATE TAPE FOR SECTION " 
	 << from << " ... " << to-1 << endl;
    my_external_adjoint_object_t<DCO_MODE>::stride=stride;
    // in taping mode, the interval is subdivided further if
    // its length exceeds the desired stride ...
    if (to-from>stride) {
      g_make_gap<DCO_MODE>(from,from+(to-from)/2,stride,x,
	       CHECKPOINT_ARGUMENTS_AND_RUN_PASSIVELY); 
      g_make_gap<DCO_MODE>(from+(to-from)/2,to,stride,x,
	       CHECKPOINT_ARGUMENTS_AND_RUN_PASSIVELY); 
    }
    else 
    // ... or the given number of iterations is performed
    // actively and the corresponding tape is written
        for (int i=from;i<to;i++) x=sin(x);
  }
}

template<typename DCO_MODE>
void g_fill_gap(
   my_external_adjoint_object_t<DCO_MODE> *D 	
) {
  typedef typename DCO_MODE::type DCO_TYPE;
  typedef typename DCO_MODE::tape_t DCO_TAPE_TYPE;
  typedef typename DCO_TAPE_TYPE::iterator_t DCO_TAPE_POSITION_TYPE;

  const int &from=D->template read_data<int>();
  const int &to=D->template read_data<int>();
  cout << "top=" << D->state.top().second << endl;
  cout << "RESTORE CHECKPOINT FOR SECTION " 
       << from << " ... " << to-1 << endl;

  DCO_TYPE x=D->state.top().second; 
  DCO_MODE::global_tape->register_variable(x); 
  DCO_TYPE x_in=x;
  DCO_TAPE_POSITION_TYPE p=DCO_MODE::global_tape->get_position();
  g_make_gap<DCO_MODE>(from,to,D->stride,x,GENERATE_TAPE);
  derivative(x)=D->get_output_adjoint();

  cout << "INTERPRET SECTION " 
       << from << " ... " << to-1 << endl;
  DCO_MODE::global_tape->interpret_adjoint_and_reset_to(p);
  D->increment_input_adjoint(derivative(x_in));
  if (to-from<=D->stride) {
    cout << "poping " << D->state.top().first << ", " << D->state.top().second << endl;
    D->state.pop();
  }
}
