#include "MyVariable.h"

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
    while(isdigit(*str) || isalpha(*str)){
        sth.push_back(*str++);
    }
}

void GetConst(VARIABLE& val, const char* str) {
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

string ToString(const VARIABLE& val)
{
    ostringstream ans;
    switch (val.type) {
    case IS_INTEGER:
        ans << (string)*(IntType*)val.val;
        break;
    case IS_DOUBLE:
        ans.precision(6);
        ans << *(double*)val.val;
        break;
    case IS_MATRIX:
        break;
    }
    return ans.str();
}
