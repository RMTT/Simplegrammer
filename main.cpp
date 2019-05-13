#include <iostream>
#include <fstream>
#include "gammer.h"
using namespace std;


int main()
{
    std::ifstream fin("../test.txt");
    grammer::initiation(fin.rdbuf());
    grammer::grammer g;
    status_t t = g.E();
    if(t == STATUS_SUCCEED)
        cout << "successful parse\n";
    return 0;
}
