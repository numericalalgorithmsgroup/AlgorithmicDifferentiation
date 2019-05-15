#include<vector>
using namespace std;

template<typename T>
void f(
    const vector<T>& x, // active inputs
    T& y        // active outputs
) {
  T v = tan(x[0]*x[3]);
  T w = x[1]-v;
  y = x[2] * v/w;
}
