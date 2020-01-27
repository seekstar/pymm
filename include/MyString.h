#ifndef MYSTRING_H_INCLUDED
#define MYSTRING_H_INCLUDED

#include <ctype.h>
#include <string>
#include <istream>

using namespace std;

void SkipSpace(const char*& str);
void SkipSpaceExceptEnter(const char*& str);

int MyAtoi(const char* str, int len);
int MyAtoi(const char* s, const char* t);
void MyItoa(char* str, int x);

bool IsEmptyString(const char* str);
void AppendWithNoCarry(string& str, const char* s);

istream& ReadNotSpace(istream& in, char& ch);

#endif // MYSTRING_H_INCLUDED
