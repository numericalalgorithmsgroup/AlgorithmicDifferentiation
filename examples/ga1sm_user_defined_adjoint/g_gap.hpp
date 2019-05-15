#include "g.hpp"

// user-defined (symbolic) adjoint
template<typename AD_TYPE>
void a1s_g(
    AD_TYPE& a1s_p, 
    const AD_TYPE& x, 
    AD_TYPE& a1s_x
) {
  a1s_p=a1s_x/(2*x);
}

// adjoint gap 
template<typename AD_MODE>
void g_fill_gap(typename AD_MODE::external_adjoint_object_t* D) {
  typedef typename AD_MODE::value_t AD_VALUE_TYPE;
  const AD_VALUE_TYPE &x = D->template read_data<AD_VALUE_TYPE>();
  AD_VALUE_TYPE a1s_x,a1s_p;
  a1s_x=D->get_output_adjoint();
  a1s_g(a1s_p,x,a1s_x);
  D->increment_input_adjoint(a1s_p);
}


// augmented forward gap 
template<typename AD_MODE>
void g_make_gap(
    const typename AD_MODE::type& p, 
    typename AD_MODE::type& x
) {
  typedef typename AD_MODE::value_t AD_VALUE_TYPE;
  typedef typename AD_MODE::tape_t AD_TAPE_TYPE;
  typedef typename AD_MODE::external_adjoint_object_t AD_EFD_TYPE;
  AD_TAPE_TYPE* AD_TAPE_POINTER=dco::tape(p);
  AD_EFD_TYPE *efd=AD_TAPE_POINTER->
    template create_callback_object<AD_EFD_TYPE>();
  AD_VALUE_TYPE px=dco::value(x),pp;
  pp=efd->register_input(p);
  g(pp,px);
  x=efd->register_output(px);
  efd->write_data(px);
  AD_TAPE_POINTER->insert_callback(&g_fill_gap<AD_MODE>, efd);
}
