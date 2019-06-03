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

/*
    in = "a=(1+\n";
    pymm.Input(in.c_str(), info);
    cout << "-------------\n" << info.str();
    info.str("");

    in = "2)\n";
    pymm.Input(in.c_str(), info);
    cout << "-------------\n" << info.str();
    info.str("");*/
/*
    //in = "if(0){a=1;}else{a=2;}\na";
    in = "a = 0;\nif(a){b=2}else{b=1\nc = b*3 * (1+b);}c";
    pymm.Input(in.c_str(), info);
    //in = "a";
    */
    //in = "if(1){\nb=2;\n}else{\nb=5;\n}";
    //in = "a=-9;while(a){a=a+1}";
    //in = "a=9;while(a){a=a-1}";
    //in = "a=-9;while(a){a=a+1;b=a*3}";

    //in = "for(i=10;i;i=i-1){i}";
    in = "i=10;\ndo{\ni=i-1\n}while(i)";

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
