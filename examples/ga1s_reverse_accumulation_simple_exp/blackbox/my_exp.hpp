/* convergence if 0 < p*exp(p*x) < 2, e.g. 
 * 
 */

template<class AD_TYPE>
void my_exp(
    const AD_TYPE& p,
    AD_TYPE& x
) {
  const AD_TYPE eps=1e-15;
  AD_TYPE xp=x+1;
  int i=0;
  while (fabs(x-xp)>eps) {
    i++;
    xp=x;
    x=x-exp(x*p)+1;
  }
  cout << i << " fixed-point iterations" << endl;
}
