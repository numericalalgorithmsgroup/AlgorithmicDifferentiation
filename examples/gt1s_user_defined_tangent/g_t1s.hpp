template<>
void g<gt1s<double>::type>(
    const gt1s<double>::type& p, 
    gt1s<double>::type& x
) {
  double pv,xv,pt1,xt1;
  xv=value(x);
  pv=value(p);
  g(pv,xv);
  pt1=derivative(p);
  xt1=pt1/(2*xv);
  value(x)=xv;
  derivative(x)=xt1;
}
