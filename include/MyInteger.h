#ifndef MYINTEGER_H_INCLUDED
#define MYINTEGER_H_INCLUDED

#include "SignedBigInt.h"
#include "MyFlags.h"

typedef SignedBigInt IntType;

void PrintInt(ostream& out, const IntType& val);

using namespace std;

#endif // MYINTEGER_H_INCLUDED
