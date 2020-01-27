/*!
 * Version: 1.0
 * Description: ACM style signed big integer.
 */

#include "SignedBigInt.h"

using namespace std;

bool operator < (double lhs, const SignedBigInt& rhs) {
    return lhs < (double)rhs;
}
bool operator <= (double lhs, const SignedBigInt& rhs) {
    return lhs <= (double)rhs;
}
bool operator > (double lhs, const SignedBigInt& rhs) {
    return lhs > (double)rhs;
}
bool operator >= (double lhs, const SignedBigInt& rhs) {
    return lhs >= (double)rhs;
}
bool operator == (double lhs, const SignedBigInt& rhs) {
    return lhs == (double)rhs;
}
bool operator != (double lhs, const SignedBigInt& rhs) {
    return lhs != (double)rhs;
}

double operator + (double lhs, const SignedBigInt& rhs) {
    return lhs + (double)rhs;
}
double operator - (double lhs, const SignedBigInt& rhs) {
    return lhs - (double)rhs;
}
double operator * (double lhs, const SignedBigInt& rhs) {
    return lhs * (double)rhs;
}
double operator / (double lhs, const SignedBigInt& rhs) {
    return lhs / (double)rhs;
}

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

double& operator += (double& lhs, const SignedBigInt& rhs)
{
	return lhs += (double)rhs;
}
double& operator -= (double& lhs, const SignedBigInt& rhs)
{
	return lhs -= (double)rhs;
}
double& operator *= (double& lhs, const SignedBigInt& rhs)
{
	return lhs *= double(rhs);
}
double& operator /= (double& lhs, const SignedBigInt& rhs)
{
	return lhs /= (double)rhs;
}
