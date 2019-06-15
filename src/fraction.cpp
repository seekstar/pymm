#include "fraction.h"

FRACTION:: FRACTION(const IntType& numerator, const IntType& denominator) {
	this->numerator = numerator;
	this->denominator = denominator;
	fractionReduction();
}
FRACTION::FRACTION(const IntType& x) : FRACTION::FRACTION(x, IntType(1)) {}

FRACTION& FRACTION::fractionReduction() {
	if (denominator.is_minus) {
		denominator.is_minus = false;
		numerator.is_minus = !numerator.is_minus;
	}
	auto gcd = GCD(numerator.absVal, denominator.absVal);
	if (gcd != 1) {
		numerator.absVal /= gcd;
		denominator.absVal /= gcd;
	}
	return *this;
}


FRACTION FRACTION::operator + (const FRACTION& rhs) const {
	return FRACTION(numerator*rhs.denominator + rhs.numerator*denominator, denominator*rhs.denominator).fractionReduction();
}
FRACTION FRACTION::operator - (const FRACTION& rhs) const {
	return FRACTION(numerator*rhs.denominator - rhs.numerator*denominator, denominator*rhs.denominator).fractionReduction();
}
FRACTION FRACTION::operator*(const FRACTION& rhs) const {
	return FRACTION(numerator * rhs.numerator, denominator * rhs.denominator).fractionReduction();
}
FRACTION FRACTION::operator/(const FRACTION& rhs) const {
	return FRACTION(numerator * rhs.denominator, denominator * rhs.numerator).fractionReduction();
}
FRACTION FRACTION::operator - () const {
	return FRACTION(-numerator, denominator);
}

FRACTION FRACTION::operator + (const IntType& rhs) const {
	return *this + FRACTION(rhs);
}
FRACTION FRACTION::operator - (const IntType& rhs) const {
	return *this - FRACTION(rhs);
}
FRACTION FRACTION::operator * (const IntType& rhs) const {
	return *this * FRACTION(rhs);
}
FRACTION FRACTION::operator / (const IntType& rhs) const {
	return *this / FRACTION(rhs);
}

FRACTION operator+(const IntType& x, const FRACTION& rhs)
{
	return FRACTION(x) + rhs;
}
FRACTION operator-(const IntType& x, const FRACTION& rhs)
{
	return FRACTION(x) - rhs;
}
FRACTION operator*(const IntType& x, const FRACTION& rhs)
{
	return FRACTION(x) * rhs;
}
FRACTION operator/(const IntType& x, const FRACTION& rhs)
{
	return FRACTION(x) / rhs;
}

FRACTION& FRACTION::operator += (const FRACTION& rhs) {
	return *this = *this + rhs;
}
FRACTION& FRACTION::operator -= (const FRACTION& rhs) {
	return *this = *this - rhs;
}
FRACTION& FRACTION::operator *= (const FRACTION& rhs) {
	return *this = *this * rhs;
}
FRACTION& FRACTION::operator /= (const FRACTION& rhs) {
	return *this = *this / rhs;
}

FRACTION& FRACTION::operator += (const IntType& rhs) {
	return *this = *this + rhs;
}
FRACTION& FRACTION::operator -= (const IntType& rhs) {
	return *this = *this - rhs;
}
FRACTION& FRACTION::operator *= (const IntType& rhs) {
	return *this = *this * rhs;
}
FRACTION& FRACTION::operator /= (const IntType& rhs) {
	return *this = *this / rhs;
}

bool FRACTION::operator < (const FRACTION& rhs) const {
    return numerator*rhs.denominator < rhs.numerator*denominator;
}
bool FRACTION::operator > (const FRACTION& rhs) const {
    return numerator*rhs.denominator > rhs.numerator*denominator;
}
bool FRACTION::operator == (const FRACTION& rhs) const {
    return numerator*rhs.denominator == rhs.numerator*denominator;
}
bool FRACTION::operator <= (const FRACTION& rhs) const {
    return numerator*rhs.denominator <= rhs.numerator*denominator;
}
bool FRACTION::operator >= (const FRACTION& rhs) const {
    return numerator*rhs.denominator >= rhs.numerator*denominator;
}
bool FRACTION::operator != (const FRACTION& rhs) const {
    return numerator*rhs.denominator != rhs.numerator*denominator;
}

bool FRACTION::operator < (const IntType& rhs) const {
    return *this < (FRACTION)rhs;
}
bool FRACTION::operator > (const IntType& rhs) const {
    return *this > (FRACTION)rhs;
}
bool FRACTION::operator == (const IntType& rhs) const {
    return *this == (FRACTION)rhs;
}
bool FRACTION::operator <= (const IntType& rhs) const {
    return *this <= (FRACTION)rhs;
}
bool FRACTION::operator >= (const IntType& rhs) const {
    return *this >= (FRACTION)rhs;
}
bool FRACTION::operator != (const IntType& rhs) const {
    return *this != (FRACTION)rhs;
}

bool operator < (const IntType& lhs, const FRACTION& rhs) {
    return lhs * rhs.denominator < rhs.numerator;
}
bool operator > (const IntType& lhs, const FRACTION& rhs) {
    return lhs * rhs.denominator > rhs.numerator;
}
bool operator == (const IntType& lhs, const FRACTION& rhs) {
    return lhs * rhs.denominator == rhs.numerator;
}
bool operator <= (const IntType& lhs, const FRACTION& rhs) {
    return lhs * rhs.denominator <= rhs.numerator;
}
bool operator >= (const IntType& lhs, const FRACTION& rhs) {
    return lhs * rhs.denominator >= rhs.numerator;
}
bool operator != (const IntType& lhs, const FRACTION& rhs) {
    return lhs * rhs.denominator != rhs.numerator;
}


FRACTION::operator double() const
{
	return (double)numerator / (double)denominator;
}

FRACTION::operator IntType() const {
	return numerator / denominator;
}

FRACTION::operator bool() const {
	assert(!denominator.absVal.s.empty());
	return !numerator.absVal.s.empty();
}

istream &operator>>(istream &in,FRACTION &x)
{
    char ch;
    while(1)
    {
        in >> x.numerator;
		ReadNotSpace(in, ch);
		in >> x.denominator;
        if (x.denominator == 0)
            cerr << "Denominator shouldn't be 0!\n";
        else if(ch != '/')
            cerr << "Wrong char! Input '/' \n";
        else
            break;
    }
    return cin;
}


ostream& operator << (ostream &out, FRACTION x) {
    out << x.numerator << '/' << x.denominator;
    return out;
}

FRACTION::~FRACTION()
{
}
