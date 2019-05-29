#include "MyInteger.h"

double operator + (const IntType& lhs, double rhs)
{
	return double(lhs) + rhs;
}
double operator + (double lhs, const IntType& rhs)
{
	return rhs + lhs;	//call the operator '+' defined previously.
}

double operator - (const IntType& lhs, double rhs)
{
	return (double)lhs - rhs;
}
double operator - (double lhs, const IntType& rhs)
{
	return lhs - (double)rhs;
}

double operator * (const IntType& lhs, double rhs)
{
	return (double)lhs * rhs;
}
double operator * (double lhs, const IntType& rhs)
{
	return rhs * lhs;	//Call the operator '*' defined previously.
}

double operator / (const IntType& lhs, double rhs)
{
	return (double)lhs / rhs;
}
double operator / (double lhs, const IntType& rhs)
{
	return lhs / (double)rhs;
}

double& operator += (double& lhs, const IntType& rhs)
{
	return lhs += (double)rhs;
}
IntType& operator += (IntType& lhs, double rhs)
{
	cerr << "Not supported yet\n";
	return lhs += rhs;
}
double& operator -= (double& lhs, const IntType& rhs)
{
	return lhs -= (double)rhs;
}
IntType& operator -= (IntType& lhs, double rhs)
{
	cerr << "Not supported yet\n";
	return lhs -= rhs;
}
double& operator *= (double& lhs, const IntType& rhs)
{
	return lhs *= double(rhs);
}
IntType& operator *= (IntType& lhs, double rhs)
{
	cerr << "Not supported yet\n";
	return lhs *= rhs;
}
double& operator /= (double& lhs, const IntType& rhs)
{
	return lhs /= (double)rhs;
}
IntType& operator /= (IntType& lhs, double rhs)
{
	cerr << "Not supported yet\n";
	return lhs /= rhs;
}
