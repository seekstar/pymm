#include <iostream>

#include "MyPyMinusMinus.h"

using namespace std;

int main()
{
    PYMM pymm;
    ostringstream info;
    string in;

    #if DEBUG
    //in = "1+";
    //in = "1+2\n\n";
    //in = "1+6*9";
    //in = "(6+1)*9";
    //in = "2 + (1 * 6 + (9+6) ) * 9";
    //in = "a = 1+2+(6*9)*(6+9)/3+(5*9)\n";
    //in = "a = 9;\na\n";
    //in = "a = (b=4)*5;\na";
    //in = "a=2\nb=4\na*b\n";

    //in += "a*=9";
    //pymm.Input(in.c_str(), info);

    in = "a=(1+\n";
    pymm.Input(in.c_str(), info);
    cout << "-------------\n" << info.str();
    info.str("");

    in = "2)\n";
    pymm.Input(in.c_str(), info);
    cout << "-------------\n" << info.str();
    info.str("");

    #else
    while (getline(cin, in)) {
        pymm.Input(in.c_str(), info);
        cout << info.str();
        info.str("");
    }
    #endif // DEBUG

    return 0;
}
