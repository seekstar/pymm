#ifndef MYSTRING_H_INCLUDED
#define MYSTRING_H_INCLUDED

#include <ctype.h>
#include <string>

using namespace std;

void SkipSpace(const char*& str);
void SkipSpaceExceptEnter(const char*& str);

int MyAtoi(const char* str, int len);
void MyItoa(char* str, int x);

bool IsEmptyString(const char* str);
void AppendWithNoCarry(string& str, const char* s);

#endif // MYSTRING_H_INCLUDED
