#include "MyVariable.h"
#include "MyGlist.h"

using namespace std;

VARIABLE::VARIABLE() {
    val = NULL;
}
//Construct the variable using v.val
VARIABLE::VARIABLE(const VALUE& v) {
    type = IS_VALUE;
    val = new VALUE(v);
}
VARIABLE::~VARIABLE() {
    ;
}
void VARIABLE::del() {
    if (!val) return;
    switch (type) {
    case IS_VALUE:
        delete (VALUE*)val;
        break;
    case IS_MATRIX:
        delete (MATRIX*)val;
        break;
    case IS_GLIST:
        delete (GLIST*)val;
        break;
    }
    val = NULL;
}
VARIABLE::operator bool() {
    assert(IS_VALUE == type);
    return (bool)*(VALUE*)val;
}
VARIABLE::operator size_t() {
    assert(IS_VALUE == type);
    return (size_t)*(VALUE*)val;
}
/*VARIABLE& VARIABLE::CloneItSelf() {
    switch (type) {
        val = new VALUE;
        ((VALUE*)val)->Copy(*(VALUE*)val);
    }
}*/
//rhs may be the same as *this, so rhs mustn't be reference
VARIABLE& VARIABLE::CopyWithoutDel(VARIABLE rhs) {
    type = rhs.type;
    switch (type) {
    case IS_VALUE:
        val = new VALUE;
        ((VALUE*)val)->Copy(*(VALUE*)rhs.val);
        break;
    case IS_MATRIX:
        //val = new MATRIX;
        break;
    case IS_GLIST:
        val = new GLIST;
        *(GLIST*)val = *(GLIST*)rhs.val;
        break;
    }
    return *this;
}
VARIABLE& VARIABLE::Copy(const VARIABLE& rhs) {
    del();
    return CopyWithoutDel(rhs);
}
void VARIABLE::ToBool() {
    assert(IS_VALUE == type);
    ((VALUE*)val)->ChangeType(IS_BOOL);
}
VARIABLE VARIABLE::operator + (const VARIABLE& rhs) const {
    assert(type == IS_VALUE && rhs.type == IS_VALUE);
    return VARIABLE(*(const VALUE*)val + *(const VALUE*)rhs.val);
}
VARIABLE VARIABLE::operator - (const VARIABLE& rhs) const {
    assert(type == IS_VALUE && rhs.type == IS_VALUE);
    return VARIABLE(*(VALUE*)val - *(VALUE*)rhs.val);
}
VARIABLE VARIABLE::operator * (const VARIABLE& rhs) const {
    assert(type == IS_VALUE && rhs.type == IS_VALUE);
    return VARIABLE(*(VALUE*)val * *(VALUE*)rhs.val);
}
VARIABLE VARIABLE::operator / (const VARIABLE& rhs) const {
    assert(type == IS_VALUE && rhs.type == IS_VALUE);
    return VARIABLE(*(VALUE*)val / *(VALUE*)rhs.val);
}
VARIABLE VARIABLE::operator % (const VARIABLE& rhs) const {
    assert(type == IS_VALUE && rhs.type == IS_VALUE);
    return VARIABLE(*(VALUE*)val % *(VALUE*)rhs.val);
}
VARIABLE VARIABLE::operator - () const{
    assert(type == IS_VALUE);
    return VARIABLE(-*(VALUE*)val);
}
VARIABLE VARIABLE::fra_div(const VARIABLE& rhs) const {
    assert(type == IS_VALUE && rhs.type == IS_VALUE);
    return VARIABLE(((VALUE*)val)->fra_div(*(VALUE*)rhs.val));
}

VARIABLE& VARIABLE::operator += (const VARIABLE& rhs) {
    assert(type == IS_VALUE && rhs.type == IS_VALUE);
    *(VALUE*)val += *(const VALUE*)rhs.val;
    return *this;
}
VARIABLE& VARIABLE::operator -= (const VARIABLE& rhs) {
    assert(type == IS_VALUE && rhs.type == IS_VALUE);
    *(VALUE*)val -= *(const VALUE*)rhs.val;
    return *this;
}
VARIABLE& VARIABLE::operator *= (const VARIABLE& rhs) {
    assert(type == IS_VALUE && rhs.type == IS_VALUE);
    *(VALUE*)val *= *(const VALUE*)rhs.val;
    return *this;
}
VARIABLE& VARIABLE::operator /= (const VARIABLE& rhs) {
    assert(type == IS_VALUE && rhs.type == IS_VALUE);
    *(VALUE*)val /= *(const VALUE*)rhs.val;
    return *this;
}
VARIABLE& VARIABLE::operator %= (const VARIABLE& rhs) {
    assert(type == IS_VALUE && rhs.type == IS_VALUE);
    *(VALUE*)val %= *(const VALUE*)rhs.val;
    return *this;
}
VARIABLE& VARIABLE::operator ++ () {
    assert(type == IS_VALUE);
    ++*(VALUE*)val;
    return *this;
}
VARIABLE& VARIABLE::operator -- () {
    assert(type == IS_VALUE);
    --*(VALUE*)val;
    return *this;
}
VARIABLE& VARIABLE::fra_div_eq(const VARIABLE& rhs) {
    assert(type == IS_VALUE && rhs.type == IS_VALUE);
    ((VALUE*)val)->fra_div_eq(*(const VALUE*)rhs.val);
    return *this;
}

VARIABLE VARIABLE::operator < (const VARIABLE& rhs) const {
    assert(type == IS_VALUE && rhs.type == IS_VALUE);
    return VARIABLE(*(VALUE*)val < *(VALUE*)rhs.val);
}
VARIABLE VARIABLE::operator > (const VARIABLE& rhs) const {
    assert(type == IS_VALUE && rhs.type == IS_VALUE);
    return VARIABLE(*(VALUE*)val > *(VALUE*)rhs.val);
}
VARIABLE VARIABLE::operator <= (const VARIABLE& rhs) const {
    assert(type == IS_VALUE && rhs.type == IS_VALUE);
    return VARIABLE(*(VALUE*)val <= *(VALUE*)rhs.val);
}
VARIABLE VARIABLE::operator >= (const VARIABLE& rhs) const {
    assert(type == IS_VALUE && rhs.type == IS_VALUE);
    return VARIABLE(*(VALUE*)val >= *(VALUE*)rhs.val);
}
VARIABLE VARIABLE::operator == (const VARIABLE& rhs) const {
    assert(type == IS_VALUE && rhs.type == IS_VALUE);
    return VARIABLE(*(VALUE*)val == *(VALUE*)rhs.val);
}
VARIABLE VARIABLE::operator != (const VARIABLE& rhs) const {
    assert(type == IS_VALUE && rhs.type == IS_VALUE);
    return VARIABLE(*(VALUE*)val != *(VALUE*)rhs.val);
}

void VARIABLE::IfValueOrEmptyThenToArray() {
    if (NULL == val) {
        val = new GLIST(0);
        type = IS_GLIST;
    } else if (type == IS_VALUE) {
        GLIST* tmp = new GLIST(1);
        (*tmp)[0] = *this;
        val = tmp;
        type = IS_GLIST;
    }
}
bool VARIABLE::OutOfBound(const vector<size_t>& pos) const {
    assert(IS_GLIST == type);
    return ((GLIST*)val)->OutOfBound(pos[0]);
}
VARIABLE& VARIABLE::operator () (const vector<size_t>& pos) {
    IfValueOrEmptyThenToArray();
    return (*(GLIST*)val)(pos[0]);
}
void VARIABLE::Print(ostream& out) const {
    switch (type) {
    case IS_VALUE:
        out << *(const VALUE*)val;
        break;
    case IS_MATRIX:
        out << *(const MATRIX*)val;
        break;
    case IS_GLIST:
        out << *(const GLIST*)val;
        break;
    }
}



CONST_OR_VARIABLE::CONST_OR_VARIABLE() {
	val = NULL;
}
CONST_OR_VARIABLE::CONST_OR_VARIABLE(bool vari, bool lv) {
	Init(vari, lv);
}
/*~CONST_OR_VARIABLE()
{
	del();
}*/

CONST_OR_VARIABLE::operator bool() {
	return (bool)*val;
}
CONST_OR_VARIABLE::operator size_t() {
	return (size_t)*val;
}
void CONST_OR_VARIABLE::del() {
	if (!left_value && val) {
		val->del();
	}
	val = NULL;
}
void CONST_OR_VARIABLE::Init(bool _vari, bool lv) {
	val = NULL;
	vari = _vari;
	left_value = lv;
}
void CONST_OR_VARIABLE::Init_new(bool _vari, bool lv) {
	vari = _vari;
	left_value = lv;
	val = new VARIABLE;
}
void CONST_OR_VARIABLE::Copy(const CONST_OR_VARIABLE& rhs)
{
	val->Copy(*rhs.val);
}
void CONST_OR_VARIABLE::NewRightVal(const CONST_OR_VARIABLE& rhs) {
	Init_new(false, false);
	Copy(rhs);
}
void CONST_OR_VARIABLE::ToBool() {
    if (left_value) {
        val->CopyWithoutDel(*val);
    }
	left_value = vari = false;
	val->ToBool();
}
CONST_OR_VARIABLE CONST_OR_VARIABLE::operator + (const CONST_OR_VARIABLE& rhs) const {
	static CONST_OR_VARIABLE ans;
	ans.Init_new(false, false);
	*ans.val = *val + *rhs.val;
	return ans;
}
CONST_OR_VARIABLE CONST_OR_VARIABLE::operator - (const CONST_OR_VARIABLE& rhs) const {
	static CONST_OR_VARIABLE ans;
	ans.Init_new(false, false);
	*ans.val = *val - *rhs.val;
	return ans;
}
CONST_OR_VARIABLE CONST_OR_VARIABLE::operator * (const CONST_OR_VARIABLE& rhs) const {
	static CONST_OR_VARIABLE ans;
	ans.Init_new(false, false);
	*ans.val = *val * *rhs.val;
	return ans;
}
CONST_OR_VARIABLE CONST_OR_VARIABLE::operator / (const CONST_OR_VARIABLE& rhs) const {
	static CONST_OR_VARIABLE ans;
	ans.Init_new(false, false);
	*ans.val = *val / *rhs.val;
	return ans;
}
CONST_OR_VARIABLE CONST_OR_VARIABLE::operator % (const CONST_OR_VARIABLE& rhs) const {
	static CONST_OR_VARIABLE ans;
	ans.Init_new(false, false);
	*ans.val = *val % *rhs.val;
	return ans;
}
CONST_OR_VARIABLE CONST_OR_VARIABLE::operator - () const {
	static CONST_OR_VARIABLE ans;
	ans.Init_new(false, false);
	*ans.val = -*val;
	return ans;
}
CONST_OR_VARIABLE CONST_OR_VARIABLE::operator ++ (int) {
	assert(left_value && vari);
	static CONST_OR_VARIABLE ans;
	ans.NewRightVal(*this);
	++*this;
	return ans;
}
CONST_OR_VARIABLE CONST_OR_VARIABLE::operator -- (int) {
	assert(left_value && vari);
	static CONST_OR_VARIABLE ans;
	ans.NewRightVal(*this);
	--*this;
	return ans;
}
CONST_OR_VARIABLE CONST_OR_VARIABLE::fra_div(const CONST_OR_VARIABLE& rhs) const {
	static CONST_OR_VARIABLE ans;
	ans.Init_new(false, false);
	*ans.val = val->fra_div(*rhs.val);
	return ans;
}

CONST_OR_VARIABLE& CONST_OR_VARIABLE::operator += (const CONST_OR_VARIABLE& rhs) {
	assert(left_value && vari);
	*val += *rhs.val;
	return *this;
}
CONST_OR_VARIABLE& CONST_OR_VARIABLE::operator -= (const CONST_OR_VARIABLE& rhs) {
	assert(left_value && vari);
	*val -= *rhs.val;
	return *this;
}
CONST_OR_VARIABLE& CONST_OR_VARIABLE::operator *= (const CONST_OR_VARIABLE& rhs) {
	assert(left_value && vari);
	*val *= *rhs.val;
	return *this;
}
CONST_OR_VARIABLE& CONST_OR_VARIABLE::operator /= (const CONST_OR_VARIABLE& rhs) {
	assert(left_value && vari);
	*val /= *rhs.val;
	return *this;
}
CONST_OR_VARIABLE& CONST_OR_VARIABLE::operator %= (const CONST_OR_VARIABLE& rhs) {
	assert(left_value && vari);
	*val %= *rhs.val;
	return *this;
}
CONST_OR_VARIABLE& CONST_OR_VARIABLE::operator ++ () {
	assert(left_value && vari);
	++*val;
	return *this;
}
CONST_OR_VARIABLE& CONST_OR_VARIABLE::operator -- () {
	assert(left_value && vari);
	--*val;
	return *this;
}
CONST_OR_VARIABLE& CONST_OR_VARIABLE::fra_div_eq(const CONST_OR_VARIABLE& rhs) {
	assert(left_value && vari);
	val->fra_div_eq(*rhs.val);
	return *this;
}

CONST_OR_VARIABLE CONST_OR_VARIABLE::operator < (const CONST_OR_VARIABLE& rhs) const {
	static CONST_OR_VARIABLE ans;
	ans.Init_new(false, false);
	*ans.val = *val < *rhs.val;
	return ans;
}
CONST_OR_VARIABLE CONST_OR_VARIABLE::operator <= (const CONST_OR_VARIABLE& rhs) const {
	static CONST_OR_VARIABLE ans;
	ans.Init_new(false, false);
	*ans.val = *val <= *rhs.val;
	return ans;
}
CONST_OR_VARIABLE CONST_OR_VARIABLE::operator > (const CONST_OR_VARIABLE& rhs) const {
	static CONST_OR_VARIABLE ans;
	ans.Init_new(false, false);
	*ans.val = *val > *rhs.val;
	return ans;
}
CONST_OR_VARIABLE CONST_OR_VARIABLE::operator >= (const CONST_OR_VARIABLE& rhs) const {
	static CONST_OR_VARIABLE ans;
	ans.Init_new(false, false);
	*ans.val = *val >= *rhs.val;
	return ans;
}
CONST_OR_VARIABLE CONST_OR_VARIABLE::operator == (const CONST_OR_VARIABLE& rhs) const {
	static CONST_OR_VARIABLE ans;
	ans.Init_new(false, false);
	*ans.val = *val == *rhs.val;
	return ans;
}
CONST_OR_VARIABLE CONST_OR_VARIABLE::operator != (const CONST_OR_VARIABLE& rhs) const {
	static CONST_OR_VARIABLE ans;
	ans.Init_new(false, false);
	*ans.val = *val == *rhs.val;
	return ans;
}

void CONST_OR_VARIABLE::Print(ostream& out) const {
	val->Print(out);
}

bool IsBeginningOfConst(char ch)
{
    return isdigit(ch);
}

bool IsPartOfConst(char ch)
{
    return IsBeginningOfConst(ch) || isalpha(ch) || '.' == ch;
}

void GetConst(string& sth, const char*& str)
{
    while(isdigit(*str) || isalpha(*str) || *str == '.'){
        sth.push_back(*str++);
    }
}

void GetConst(VARIABLE& val, const char* str) {
    SkipSpace(str);
    if ('[' == *str) {
        assert(1);
    } else if ('[' == *str){
        assert(1);
    } else if (IsPartOfConst(*str)) {
        val.type = IS_VALUE;
        val.val = new VALUE;
        GetConst(*(VALUE*)(val.val), str);
    } else {
        assert(1);
    }
}

void GetConst(VALUE& val, const char* str) {
    bool is_double = false;
    string tmp;

    while (IsPartOfConst(*str)) {
        if(*str == '.')
            is_double = true;
        tmp += *str++;
    }
    if (is_double) {
        val.type = IS_DOUBLE;
        val.val = new double;
        sscanf(tmp.c_str(), "%lf", (double*)val.val);
    } else {
        val.type = IS_INTEGER;
        val.val = new IntType(tmp.c_str());
    }
}

ostream& operator << (ostream& out, const VARIABLE& val) {
    if (!val.val) {
        out << "NULL";
    } else {
        switch (val.type) {
        case IS_VALUE:
            out << *(VALUE*)val.val;
            break;
        case IS_MATRIX:
            out << *(MATRIX*)val.val;
            break;
        case IS_GLIST:
            out << *(GLIST*)val.val;
            break;
        }
    }
    
    return out;
}
