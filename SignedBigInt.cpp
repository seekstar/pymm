#include "SignedBigInt.h"

ostream& operator << (ostream& out, const SignedBigInt& a)
{
	return out << string(a);
}

istream& operator >> (istream& in, SignedBigInt& a)
{
	string str;
	if (in >> str)
		a = str;
	return in;
}
