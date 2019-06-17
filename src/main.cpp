#include <iostream>

#include "MyPyMinusMinus.h" 
 
using namespace std; 

int main()
{ 
    PYMM pymm;
    ostringstream info;
    string in;

    #if DEBUG
    //in = "a=4\n++a\n--a";
    //in = "a=6\n--a;\n--a";
    //in = "a=91\na--\na++";
    //in = "a = 9";
    //in = "a = 0;a(10) = 2;a";
    //in = "f = 0;f(1) = 1;f(1)(2) = 2";
    //in = "cnt=0;prime(cnt++)=2\nprime";
    //in = "cnt = 0;cnt++";
    //in = "cnt = 0;++cnt";
    in = "1/2/3";
    pymm.Input(in.c_str(), info);
    cout << "-------------\n" << info.str();

    #else
    while (getline(cin, in)) {
        pymm.Input(in.c_str(), info);
        cout << info.str();
        info.str("");
    }
    #endif // DEBUG

    return 0;
}
