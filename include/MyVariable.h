#ifndef MYVARIABLE_H_INCLUDED
#define MYVARIABLE_H_INCLUDED

#include <assert.h>

#include "MyFlags.h"
#include "MyValue.h"

using namespace std;

enum VARIABLE_TYPE {
    IS_VALUE,
    IS_MATRIX,
    IS_GLIST    //广义表
};

class VARIABLE {
public:
    VARIABLE_TYPE type;
    void* val;

    VARIABLE();
    VARIABLE(const VALUE& v);
    ~VARIABLE();

    explicit operator bool();
    explicit operator size_t();

	void del();
	VARIABLE& CopyWithoutDel(VARIABLE rhs);
    VARIABLE& Copy(const VARIABLE& rhs);
	void ToBool();

	VARIABLE operator + (const VARIABLE& rhs) const;
	VARIABLE operator - (const VARIABLE& rhs) const;
	VARIABLE operator * (const VARIABLE& rhs) const;
	VARIABLE operator / (const VARIABLE& rhs) const;
	VARIABLE operator % (const VARIABLE& rhs) const;
	VARIABLE operator - () const;
	VARIABLE fra_div(const VARIABLE& rhs) const;

	VARIABLE& operator += (const VARIABLE& rhs);
	VARIABLE& operator -= (const VARIABLE& rhs);
	VARIABLE& operator *= (const VARIABLE& rhs);
	VARIABLE& operator /= (const VARIABLE& rhs);
	VARIABLE& operator %= (const VARIABLE& rhs);
	VARIABLE& operator ++ ();
	VARIABLE& operator -- ();
	VARIABLE& fra_div_eq(const VARIABLE& rhs);

	VARIABLE operator < (const VARIABLE& rhs) const;
	VARIABLE operator > (const VARIABLE& rhs) const;
	VARIABLE operator <= (const VARIABLE& rhs) const;
	VARIABLE operator >= (const VARIABLE& rhs) const;
	VARIABLE operator == (const VARIABLE& rhs) const;
	VARIABLE operator != (const VARIABLE& rhs) const;
	
	void IfValueOrEmptyThenToArray();
	VARIABLE& operator () (const vector<size_t>& pos);
	bool OutOfBound(const vector<size_t>& pos) const;

	void Print(ostream& out) const;
};

class CONST_OR_VARIABLE{
public:
    bool left_value;
    bool vari;
    VARIABLE* val;

	CONST_OR_VARIABLE();
	CONST_OR_VARIABLE(bool vari, bool lv);

	operator bool();
	operator size_t();

	void del();
	void Init(bool _vari, bool lv);
	void Init_new(bool _vari, bool lv);
	void Copy(const CONST_OR_VARIABLE& rhs);
	void NewRightVal(const CONST_OR_VARIABLE& rhs);
	void ToBool();

	CONST_OR_VARIABLE operator + (const CONST_OR_VARIABLE& rhs) const;
	CONST_OR_VARIABLE operator - (const CONST_OR_VARIABLE& rhs) const;
	CONST_OR_VARIABLE operator * (const CONST_OR_VARIABLE& rhs) const;
	CONST_OR_VARIABLE operator / (const CONST_OR_VARIABLE& rhs) const;
	CONST_OR_VARIABLE operator % (const CONST_OR_VARIABLE& rhs) const;
	CONST_OR_VARIABLE operator - () const;
	CONST_OR_VARIABLE operator ++ (int);
	CONST_OR_VARIABLE operator -- (int);
	CONST_OR_VARIABLE fra_div(const CONST_OR_VARIABLE& rhs) const;

	CONST_OR_VARIABLE& operator += (const CONST_OR_VARIABLE& rhs);
	CONST_OR_VARIABLE& operator -= (const CONST_OR_VARIABLE& rhs);
	CONST_OR_VARIABLE& operator *= (const CONST_OR_VARIABLE& rhs);
	CONST_OR_VARIABLE& operator /= (const CONST_OR_VARIABLE& rhs);
	CONST_OR_VARIABLE& operator %= (const CONST_OR_VARIABLE& rhs);
	CONST_OR_VARIABLE& operator ++ ();
	CONST_OR_VARIABLE& operator -- ();
	CONST_OR_VARIABLE& fra_div_eq(const CONST_OR_VARIABLE& rhs);

	CONST_OR_VARIABLE operator < (const CONST_OR_VARIABLE& rhs) const;
	CONST_OR_VARIABLE operator <= (const CONST_OR_VARIABLE& rhs) const;
	CONST_OR_VARIABLE operator > (const CONST_OR_VARIABLE& rhs) const;
	CONST_OR_VARIABLE operator >= (const CONST_OR_VARIABLE& rhs) const;
	CONST_OR_VARIABLE operator == (const CONST_OR_VARIABLE& rhs) const;
	CONST_OR_VARIABLE operator != (const CONST_OR_VARIABLE& rhs) const;

	void Print(ostream& out) const;
};

bool IsBeginningOfConst(char ch);
bool IsPartOfConst(char ch);

void GetConst(string& sth, const char*& str);
void GetConst(VARIABLE& val, const char* str);
void GetConst(VALUE& val, const char* str);
ostream& operator << (ostream& out, const VARIABLE& val);

#endif // MYVARIABLE_H_INCLUDED
