#ifndef FRACTION_H_
#define FRACTION_H_

#include "SignedBigInt.h"
#include "MyMath.h"
#include "MyString.h"

using namespace std;

typedef SignedBigInt INT;

class FRACTION{

private:
	INT numerator;
	INT denominator;
	
public:
    FRACTION(){};
	explicit FRACTION(const INT& x);
	explicit FRACTION(const INT& numerator, const INT& denominator);
	friend istream& operator>>(istream &in,FRACTION &x);
    friend ostream& operator<<(ostream &out,FRACTION x);

	FRACTION operator + (const FRACTION& rhs) const;
	FRACTION operator - (const FRACTION& rhs) const;
	FRACTION operator * (const FRACTION& rhs) const;
	FRACTION operator / (const FRACTION& rhs) const;
	FRACTION operator - () const;

	FRACTION operator + (const INT& rhs) const;
	FRACTION operator - (const INT& rhs) const;
	FRACTION operator * (const INT& rhs) const;
	FRACTION operator / (const INT& rhs) const;

	friend FRACTION operator + (const INT& x, const FRACTION& rhs);
	friend FRACTION operator - (const INT& x, const FRACTION& rhs);
	friend FRACTION operator * (const INT& x, const FRACTION& rhs);
	friend FRACTION operator / (const INT& x, const FRACTION& rhs);

	FRACTION& operator += (const FRACTION& rhs);
	FRACTION& operator -= (const FRACTION& rhs);
	FRACTION& operator *= (const FRACTION& rhs);
	FRACTION& operator /= (const FRACTION& rhs);

	FRACTION& operator += (const INT& rhs);
	FRACTION& operator -= (const INT& rhs);
	FRACTION& operator *= (const INT& rhs);
	FRACTION& operator /= (const INT& rhs);
	
	explicit operator double() const;
	explicit operator INT() const;
	explicit operator bool() const;

	bool operator>(const FRACTION& rhs) const;
	bool operator>=(const FRACTION& rhs) const;
    bool operator<(const FRACTION& rhs) const;
    bool operator<=(const FRACTION& rhs) const;
    bool operator==(const FRACTION& rhs) const;
    bool operator!=(const FRACTION& rhs) const;

	bool operator>(const INT& rhs) const;
	bool operator>=(const INT& rhs) const;
    bool operator<(const INT& rhs) const;
    bool operator<=(const INT& rhs) const;
    bool operator==(const INT& rhs) const;
    bool operator!=(const INT& rhs) const;

	friend bool operator < (const INT& lhs, const FRACTION& rhs);
	friend bool operator > (const INT& lhs, const FRACTION& rhs);
	friend bool operator == (const INT& lhs, const FRACTION& rhs);
	friend bool operator <= (const INT& lhs, const FRACTION& rhs);
	friend bool operator >= (const INT& lhs, const FRACTION& rhs);
	friend bool operator != (const INT& lhs, const FRACTION& rhs);
	

	FRACTION& fractionReduction();                      //Լ��
	~FRACTION();
};

#endif
