#include "MyVariable.h"

using namespace std;

bool IsBeginningOfConst(char ch)
{
    return isdigit(ch);
}

bool IsPartOfConst(char ch)
{
    return IsBeginningOfConst(ch) || isalpha(ch) || '.' == ch;
}

void GetConst(string& sth, const char*& str)
{
    while(isdigit(*str) || isalpha(*str) || *str == '.'){
        sth.push_back(*str++);
    }
}

void GetConst(VARIABLE& val, const char* str) {
    SkipSpace(str);
    if ('[' == *str) {
        assert(1);
    } else if ('[' == *str){
        assert(1);
    } else if (IsPartOfConst(*str)) {
        val.type = IS_VALUE;
        val.val = new VALUE;
        GetConst(*(VALUE*)(val.val), str);
    } else {
        assert(1);
    }
}

void GetConst(VALUE& val, const char* str) {
    bool is_double = false;
    string tmp;

    while (IsPartOfConst(*str)) {
        if(*str == '.')
            is_double = true;
        tmp += *str++;
    }
    if (is_double) {
        val.type = IS_DOUBLE;
        val.val = new double;
        sscanf(tmp.c_str(), "%lf", (double*)val.val);
    } else {
        val.type = IS_INTEGER;
        val.val = new IntType(tmp.c_str());
    }
}

ostream& operator << (ostream& out, const VARIABLE& val) {
    switch (val.type) {
    case IS_VALUE:
        out << *(VALUE*)val.val;
        break;
    case IS_MATRIX:
        out << *(MATRIX*)val.val;
        break;
    case IS_ARRAY:
        out << *(ARRAY*)val.val;
        break;
    }
    return out;
}
