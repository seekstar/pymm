#include "SignedBigInt.h"

using namespace std;

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

SignedBigInt sqrt(const SignedBigInt& x, int m) {
	assert(!x.is_minus);
	return SignedBigInt(sqrt(x.absVal, m));
}
