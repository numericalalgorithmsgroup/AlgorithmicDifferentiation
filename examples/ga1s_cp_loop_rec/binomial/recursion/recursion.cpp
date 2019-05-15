#include<cassert>
#include<cstdlib>
#include<cmath>
#include<climits>
#include<iostream>
#include<algorithm>
using namespace std;

unsigned long f(int n) {
	if (n==0) return 1;
	return n*f(n-1);
}

void split(int c, int r, int from, int to, int stride) {
        static int j=0;
	if (c>1&&r>=0&&to-from>stride) {
	  int l=f(c+r)/(f(c)*f(r));
	    cout << j++ << ": c=" << c << "; "
	       << "r=" << r << "; "
	       << "from=" << from << "; "
	       << "l=" << l << "; " 
	       << "to=" << min(to,from+l) << "; " 
	       << endl;
	    split(c,r-1,from,min(to,from+l),stride); 
	    split(c-1,r,min(to,from+l),to,stride);
            j--;
	}
}

void f(double & x, int c, int r, int from, int to, int stride) {
  static int j=0;
	cout  << "from=" << from << "; to=" << to << endl;
	if ((c>1&&r>=0)&&(to-from>stride)) {
	  int l=f(c+r)/(f(c)*f(r));
	    cout << j++ << ": c=" << c << "; "
	       << "r=" << r << "; "
	       << "from=" << from << "; "
	       << "l=" << l << "; " 
	       << "to=" << min(to,from+l) << "; " 
	       << endl;
	    f(x,c-1,r,min(to,from+l),to,stride);
	    f(x,c,r-1,from,min(to,from+l),stride);
            j--;
	}
  else {
    cout << "taping " << from << " ... " << to-1 << endl;
    for (int i=from;i<to;i++) x=sin(x);
  }
}

int get_r(int c, unsigned long l) {
  int r;
  for (r=0;r<INT_MAX;r++)
    if (l<=f(c+r)/(f(c)*f(r))) break;
  return r;
}

int main() {
        cout.precision(15);
	int c=5;
	unsigned long l=20;
	int stride=3;
	int r=get_r(c,l);
	//split(c,r-1,0,l,stride);
        double x=2.1;
        f(x,c,r-1,0,l,stride);
        cout << x << endl;
	return 0;
}
