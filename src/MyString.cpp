#include "MyString.h"

void SkipSpace(const char*& str)
{
    while(*str != '\0' && isspace(*str))
        ++str;
}

void SkipSpaceExceptEnter(const char*& str) {
	while (*str != '\0' && *str != '\n' && isspace(*str))
		++str;
}

int MyAtoi(const char* str, int len)
{
    int ans = 0;
    for(int i = 0; i < len; i++)
        ans = ans * 10 + str[i] - '0';
    return ans;
}

int MyAtoi(const char* s, const char* t) {
    int ans = 0;
    for (; s != t; ++s)
        (ans *= 10) += *s - '0';
    return ans;
}

void MyItoa(char* str, int x)
{
    if (x < 0) {
        *(str++) = '-';
        x = -x;
    }
    do {
        *(str++) = x % 10 + '0';
        x /= 10;
    }while(x);
    *str = '\0';
}

bool IsEmptyString(const char* str)
{
    while (*str && isspace(*str)) {
        ++str;
    }

    return '\0' == *str;
}

//Carry will be replaced by space
void AppendWithNoCarry(string& str, const char* s) {
    for (; *s; ++s) {
        str += (*s == '\n' ? ' ' : *s);
    }
}

istream& ReadNotSpace(istream& in, char& ch) {
    do {
        in >> ch;
    } while (isspace(ch));
    return in;
}
