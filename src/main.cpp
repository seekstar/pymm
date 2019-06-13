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
    in = "a=91\na--\na++";
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
