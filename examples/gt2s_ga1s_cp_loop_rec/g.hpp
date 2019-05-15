#include<vector>
using namespace std;


template<typename AD_TYPE>
void g(
    int from,   
    int to,     
    int stride, // max number of consecutive tapings
    AD_TYPE& x
) {
  if (to-from>stride) {
    g(from,from+(to-from)/2,stride,x);
    g(from+(to-from)/2,to,stride,x);
  }
  else 
    for (int i=from;i<to;i++) x=sin(x);
}

