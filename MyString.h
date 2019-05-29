#ifndef MYSTRING_H_INCLUDED
#define MYSTRING_H_INCLUDED

#include <ctype.h>

void SkipSpace(const char*& str);

int MyAtoi(const char* str, int len);
void MyItoa(char* str, int x);

bool IsEmptyString(const char* str);

#endif // MYSTRING_H_INCLUDED
