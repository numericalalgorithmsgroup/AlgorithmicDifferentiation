template<class T>
void g(
    const T& p, 
    T& x
) {
  const T eps=1e-12;
  T xp=x+1;
  while (fabs(x-xp)>eps) {
    xp=x;
    x=xp-(xp*xp-p)/(2*xp);
  }
}
