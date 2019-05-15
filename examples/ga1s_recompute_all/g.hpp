template<typename AD_TYPE>
void g(
    int n,   
    AD_TYPE& x
) {
  for (int i=0;i<n;i++) x=sin(x);
}
