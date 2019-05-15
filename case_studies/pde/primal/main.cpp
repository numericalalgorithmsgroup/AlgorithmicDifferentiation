#include <iostream>
#include <fstream>
#include <cassert>
using namespace std;

#include "../config.h"
#include "../ad_data_view.hpp"
#include "pdesolver.hpp"

int main(int argc, char* argv[]) {
    if(argc!=2) { cerr << "Please specify input scenario file, e.g. scenario_1.in\n"; exit(-1); }
    cout.precision(15);
    ifstream vols(argv[1]); 
    if(vols.fail()) { cerr << "Cannot open scenario file '" << argv[1] << "'\n"; exit(-1); }
    ACTIVE_INPUTS<double> X(S0,r,K,T,vols); vols.close();
    PASSIVE_INPUTS XP(N,M);
    ACTIVE_OUTPUTS<double> Y;
    price(X,XP,Y);
    cout << "Y=" << Y.V << endl;
    return 0;
}
