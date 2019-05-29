#include "MyError.h"

void ErrMsg(string& info, const char msg[], const int& sth) {
    static char tmp[20];
    MyItoa(tmp, sth);
    ((info += msg) += tmp) += '\n';
}
