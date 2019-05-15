#include<vector>
using namespace std;

template<typename T>
void f(
    const vector<T>& x, // active inputs
    vector<T>& y        // active outputs
) {
  T v=tan(x[2]*x[3]);
  T w=x[1]-v;
  y[0]=x[0]*v/w;
  y[1]=y[0]*x[1];
}
