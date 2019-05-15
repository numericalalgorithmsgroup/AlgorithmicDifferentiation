#ifndef MRG32K3A_H_
#define MRG32K3A_H_
#include <math.h>

inline double nextU01(double *s)
{
    const double norm = 2.328306549295728e-10;
    const double m1 =  4294967087.0, m2=4294944443.0, a12=1403580.0, a13n=810728.0, a21=527612.0, a23n=1370589.0;
    const double m1inv = 1.0/m1, m2inv = 1.0/m2;
    long k;
    double p1, p2, u;;
    /* Component 1 */
    p1 = a12 * s[1] - a13n * s[0];
    k = long(p1 * m1inv);
    p1 -= k*m1;
    if (p1 < 0.0) p1 += m1;
    s[0] = s[1];
    s[1] = s[2];
    s[2] = p1;
    /* Component 2 */
    p2 = a21 * s[3+2] - a23n * s[3+0];
    k = long(p2 * m2inv);
    p2 -= k * m2;
    if (p2 < 0.0) p2 += m2;
    s[3+0] = s[3+1];
    s[3+1] = s[3+2];
    s[3+2] = p2;

    u = (  (p1 <= p2) ? (p1 - p2 + m1) * norm : (p1 - p2) * norm  );
    return u;
}


template<typename A>
void randNormal(int n, double *state, A& normal)
{
    const double pi = 3.14159265358979323846;
    double y1, y2, u;
    int i;
    for(i=0; i<=n-2; i+=2) {
        u = nextU01(state);
        double x2 = sqrt(-2.0*log(u));
        u = nextU01(state);
        double x = sin( 2.0*pi*u );

        y2 = cos( 2.0*pi*u );
        y2 *= x2;
        y1 = x*x2;
        normal[i] = y1;
        normal[i+1] = y2;
    }
    if(i<n) {
        u = nextU01(state);
        double x2 = sqrt(-2.0*log(u));
        u = nextU01(state);
        double x = sin( 2.0*pi*u );

        y2 = cos( 2.0*pi*u );
        y2 *= x2;
        y1 = x*x2;
        normal[i] = y1;
        i++;
        if(i<n) {
            normal[i] = y2;
        }
    }
}


template<typename A>
void randUniform(int n, double *state, A& P)
{
    for(int i=0; i<n; i++) {
        P[i] = nextU01(state);
    }
}


#endif

