#ifndef FRACTION_H_
#define FRACTION_H_

#include "SignedBigInt.h"
#include "MyMath.h"
#include "MyString.h"

using namespace std;

typedef SignedBigInt IntType;

class FRACTION{
	
public:
	IntType numerator;
	IntType denominator;
	
    FRACTION(){};
	explicit FRACTION(const IntType& x);
	explicit FRACTION(const IntType& numerator, const IntType& denominator);
	friend istream& operator>>(istream &in,FRACTION &x);
    friend ostream& operator<<(ostream &out,FRACTION x);

	FRACTION operator + (const FRACTION& rhs) const;
	FRACTION operator - (const FRACTION& rhs) const;
	FRACTION operator * (const FRACTION& rhs) const;
	FRACTION operator / (const FRACTION& rhs) const;
	FRACTION operator - () const;

	FRACTION operator + (const IntType& rhs) const;
	FRACTION operator - (const IntType& rhs) const;
	FRACTION operator * (const IntType& rhs) const;
	FRACTION operator / (const IntType& rhs) const;

	friend FRACTION operator + (const IntType& x, const FRACTION& rhs);
	friend FRACTION operator - (const IntType& x, const FRACTION& rhs);
	friend FRACTION operator * (const IntType& x, const FRACTION& rhs);
	friend FRACTION operator / (const IntType& x, const FRACTION& rhs);

	FRACTION& operator += (const FRACTION& rhs);
	FRACTION& operator -= (const FRACTION& rhs);
	FRACTION& operator *= (const FRACTION& rhs);
	FRACTION& operator /= (const FRACTION& rhs);

	FRACTION& operator += (const IntType& rhs);
	FRACTION& operator -= (const IntType& rhs);
	FRACTION& operator *= (const IntType& rhs);
	FRACTION& operator /= (const IntType& rhs);
	
	explicit operator double() const;
	explicit operator IntType() const;
	explicit operator bool() const;

	bool operator>(const FRACTION& rhs) const;
	bool operator>=(const FRACTION& rhs) const;
    bool operator<(const FRACTION& rhs) const;
    bool operator<=(const FRACTION& rhs) const;
    bool operator==(const FRACTION& rhs) const;
    bool operator!=(const FRACTION& rhs) const;

	bool operator>(const IntType& rhs) const;
	bool operator>=(const IntType& rhs) const;
    bool operator<(const IntType& rhs) const;
    bool operator<=(const IntType& rhs) const;
    bool operator==(const IntType& rhs) const;
    bool operator!=(const IntType& rhs) const;

	friend bool operator < (const IntType& lhs, const FRACTION& rhs);
	friend bool operator > (const IntType& lhs, const FRACTION& rhs);
	friend bool operator == (const IntType& lhs, const FRACTION& rhs);
	friend bool operator <= (const IntType& lhs, const FRACTION& rhs);
	friend bool operator >= (const IntType& lhs, const FRACTION& rhs);
	friend bool operator != (const IntType& lhs, const FRACTION& rhs);
	

	FRACTION& fractionReduction();                      //Լ��
	~FRACTION();
};

#endif
