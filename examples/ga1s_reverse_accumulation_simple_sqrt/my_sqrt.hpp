template<class AD_TYPE>
void my_sqrt(
    const AD_TYPE& p,
    AD_TYPE& x
) {
  const AD_TYPE eps=1e-12;
  AD_TYPE xp=x+1;
  int i=0;
  while (fabs(x-xp)>eps) {
    i++;
    xp=x;
    x=.5*(p/x+x);
  }
  cout << i << " Newton iterations yield " << x << endl;
}
