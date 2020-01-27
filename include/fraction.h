/*!
 * Version: 	2.0
 * Description:	fraction template
 */

#ifndef fraction_H_
#define fraction_H_

#include <iostream>

#include "MyMath.h"
#include "MyString.h"

using namespace std;

template <typename IntType>
class fraction{
public:
	IntType numerator;
	IntType denominator;
	
    fraction(){};
	explicit fraction(const IntType& x) : fraction::fraction(x, IntType(1)) {}
	explicit fraction(const IntType& numerator, const IntType& denominator) {
		this->numerator = numerator;
		this->denominator = denominator;
		fractionReduction();
	}

	fraction operator + (const fraction& rhs) const {
		return fraction(numerator*rhs.denominator + rhs.numerator*denominator, denominator*rhs.denominator).fractionReduction();
	}
	fraction operator - (const fraction& rhs) const {
		return fraction(numerator*rhs.denominator - rhs.numerator*denominator, denominator*rhs.denominator).fractionReduction();
	}
	fraction operator * (const fraction& rhs) const {
		return fraction(numerator * rhs.numerator, denominator * rhs.denominator).fractionReduction();
	}
	fraction operator / (const fraction& rhs) const {
		return fraction(numerator * rhs.denominator, denominator * rhs.numerator).fractionReduction();
	}
	fraction operator - () const {
		return fraction(-numerator, denominator);
	}

	fraction operator + (const IntType& rhs) const {
		return *this + fraction(rhs);
	}
	fraction operator - (const IntType& rhs) const {
		return *this - fraction(rhs);
	}
	fraction operator * (const IntType& rhs) const {
		return *this * fraction(rhs);
	}
	fraction operator / (const IntType& rhs) const {
		return *this / fraction(rhs);
	}

	template <typename T>
	friend fraction<T> operator + (const T& x, const fraction<T>& rhs);
	template <typename T>
	friend fraction<T> operator - (const T& x, const fraction<T>& rhs);
	template <typename T>
	friend fraction<T> operator * (const T& x, const fraction<T>& rhs);
	template <typename T>
	friend fraction<T> operator / (const T& x, const fraction<T>& rhs);

	fraction& operator += (const fraction& rhs) {
		return *this = *this + rhs;
	}
	fraction& operator -= (const fraction& rhs) {
		return *this = *this - rhs;
	}
	fraction& operator *= (const fraction& rhs) {
		return *this = *this * rhs;
	}
	fraction& operator /= (const fraction& rhs) {
		return *this = *this / rhs;
	}

	fraction& operator += (const IntType& rhs) {
		return *this = *this + rhs;
	}
	fraction& operator -= (const IntType& rhs) {
		return *this = *this - rhs;
	}
	fraction& operator *= (const IntType& rhs) {
		return *this = *this * rhs;
	}
	fraction& operator /= (const IntType& rhs) {
		return *this = *this / rhs;
	}

	bool operator < (const fraction& rhs) const {
		return numerator*rhs.denominator < rhs.numerator*denominator;
	}
	bool operator > (const fraction& rhs) const {
		return numerator*rhs.denominator > rhs.numerator*denominator;
	}
	bool operator == (const fraction& rhs) const {
		return numerator*rhs.denominator == rhs.numerator*denominator;
	}
	bool operator <= (const fraction& rhs) const {
		return numerator*rhs.denominator <= rhs.numerator*denominator;
	}
	bool operator >= (const fraction& rhs) const {
		return numerator*rhs.denominator >= rhs.numerator*denominator;
	}
	bool operator != (const fraction& rhs) const {
		return numerator*rhs.denominator != rhs.numerator*denominator;
	}

	bool operator < (const IntType& rhs) const {
		return numerator < denominator * rhs;
	}
	bool operator > (const IntType& rhs) const {
		return numerator > denominator * rhs;
	}
	bool operator <= (const IntType& rhs) const {
		return numerator <= denominator * rhs;
	}
	bool operator >= (const IntType& rhs) const {
		return numerator >= denominator * rhs;
	}
	bool operator == (const IntType& rhs) const {
		return numerator == denominator * rhs;
	}
	bool operator != (const IntType& rhs) const {
		return numerator != denominator * rhs;
	}

	template <typename T>
	friend bool operator < (const T& lhs, const fraction<T>& rhs);
	template <typename T>
	friend bool operator > (const T& lhs, const fraction<T>& rhs);
	template <typename T>
	friend bool operator == (const T& lhs, const fraction<T>& rhs);
	template <typename T>
	friend bool operator <= (const T& lhs, const fraction<T>& rhs);
	template <typename T>
	friend bool operator >= (const T& lhs, const fraction<T>& rhs);
	template <typename T>
	friend bool operator != (const T& lhs, const fraction<T>& rhs);

	operator double() const {
		return (double)numerator / (double)denominator;
	}

	operator IntType() const {
		return numerator / denominator;
	}

	operator bool() const {
		assert(!denominator.absVal.s.empty());
		return !numerator.absVal.s.empty();
	}

	fraction& fractionReduction() {
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

	template <typename T>
	friend istream &operator>>(istream &in,fraction<T> &x);

	template <typename T>
	friend ostream& operator << (ostream &out, fraction<T> x);
};

template <typename IntType>
fraction<IntType> operator+(const IntType& x, const fraction<IntType>& rhs)
{
	return fraction<IntType>(x) + rhs;
}
template <typename IntType>
fraction<IntType> operator-(const IntType& x, const fraction<IntType>& rhs)
{
	return fraction<IntType>(x) - rhs;
}
template <typename IntType>
fraction<IntType> operator*(const IntType& x, const fraction<IntType>& rhs)
{
	return fraction<IntType>(x) * rhs;
}
template <typename IntType>
fraction<IntType> operator/(const IntType& x, const fraction<IntType>& rhs)
{
	return fraction<IntType>(x) / rhs;
}

template <typename IntType>
bool operator < (const IntType& lhs, const fraction<IntType>& rhs) {
    return lhs * rhs.denominator < rhs.numerator;
}
template <typename IntType>
bool operator > (const IntType& lhs, const fraction<IntType>& rhs) {
    return lhs * rhs.denominator > rhs.numerator;
}
template <typename IntType>
bool operator == (const IntType& lhs, const fraction<IntType>& rhs) {
    return lhs * rhs.denominator == rhs.numerator;
}
template <typename IntType>
bool operator <= (const IntType& lhs, const fraction<IntType>& rhs) {
    return lhs * rhs.denominator <= rhs.numerator;
}
template <typename IntType>
bool operator >= (const IntType& lhs, const fraction<IntType>& rhs) {
    return lhs * rhs.denominator >= rhs.numerator;
}
template <typename IntType>
bool operator != (const IntType& lhs, const fraction<IntType>& rhs) {
    return lhs * rhs.denominator != rhs.numerator;
}

template <typename IntType>
istream &operator>>(istream &in,fraction<IntType> &x)
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

template <typename IntType>
ostream& operator << (ostream &out, fraction<IntType> x) {
    out << x.numerator << '/' << x.denominator;
    return out;
}

#endif
