#include <iostream>
#include <cstdlib>
#include <cassert>
using namespace std;

#include "dco.hpp"
using namespace dco;

typedef ga1s<double> DCO_MODE;
typedef DCO_MODE::type DCO_TYPE;
typedef DCO_MODE::tape_t DCO_TAPE_TYPE;
typedef DCO_TAPE_TYPE::iterator_t DCO_TAPE_POSITION_TYPE;

#define STATISTICS
#define VERBOSE

#ifdef STATISTICS
dco::mem_long_t max_tape_size;
unsigned int max_checkpoint_size;
#endif 
#include "f.hpp"

void driver(const int n, const int stride, double& xv, double& xa1) {
#ifdef STATISTICS
  max_tape_size=0;
  max_checkpoint_size=0;
#endif
  DCO_TYPE x=xv;
  DCO_MODE::global_tape=DCO_TAPE_TYPE::create();
  DCO_MODE::global_tape->register_variable(x);
  DCO_TYPE x_in=x;

  f<DCO_MODE>(0,n,stride,x);

  DCO_MODE::global_tape->register_output_variable(x);
  derivative(x)=1;
  
#ifdef VERBOSE
  cout << "INTERPRET SECTION: 0 ... " << n-1 << endl;
#endif
  DCO_MODE::global_tape->write_to_dot("driver.dot");
  DCO_MODE::global_tape->interpret_adjoint();

  xv=value(x);
  xa1=derivative(x_in);
#ifdef STATISTICS
  cerr << "maximum tape size=" << max_tape_size*1024*1024 << "Byte" << endl;
  cerr << "maximum checkpoint size=" << max_checkpoint_size*8 << "Byte" << endl;
#endif
  DCO_TAPE_TYPE::remove(DCO_MODE::global_tape);
}

