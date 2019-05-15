template<typename T>
void euler(const int from, const int to, T& x, const vector<T>& p) { 
  double dt=1./p.size();
  for (int i=from;i<to;i++) {
    T x_prev=x;
    T f=-dt*p[i]*sin(x*i*dt);
    while (abs(f)>1e-7) {
      x=x-f/(1-dt*p[i]*i*dt*cos(x*i*dt));
      f=x-x_prev-dt*p[i]*sin(x*i*dt);
    }
  }
}
