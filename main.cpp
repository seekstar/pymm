#include <iostream>

#include "MyPyMinusMinus.h"

using namespace std;

int main()
{
    PYMM pymm;
    ostringstream info;
    string in;

    #if DEBUG
    //in = "1+2";
    //in = "1+6*9";
    //in = "(6+1)*9";
    //in = "2 + (1 * 6 + (9+6) ) * 9";
    in = "a = 9";
    //in += "a*=9";
    pymm.Input(in.c_str(), info);
    cout << info.str() << endl;
    #else
    while (cin >> in) {
        pymm.Input(in.c_str(), info);
        cout << info.str() << endl;
        info.str("");
    }
    #endif // DEBUG

    return 0;
}
