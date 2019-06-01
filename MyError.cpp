#include "MyError.h"

void ErrMsg(ostream& info, const char msg[], const int& sth) {
    static char tmp[20];
    MyItoa(tmp, sth);
    info << msg << tmp << '\n';
}
