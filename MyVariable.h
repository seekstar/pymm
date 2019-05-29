#ifndef MYVARIABLE_H_INCLUDED
#define MYVARIABLE_H_INCLUDED

#include <string>
#include <assert.h>

#include "MyFlags.h"
#include "MyInteger.h"
#include "MyMatrix.h"

using namespace std;

//元数据类型
enum VAL_TYPE{
    IS_INTEGER,
    IS_DOUBLE,
    IS_MATRIX
};

struct VARIABLE{
    VAL_TYPE type;
    void* val;

    VARIABLE()
    {
        val = NULL;
    }
    ~VARIABLE() {
        ;
    }
    VARIABLE& Copy(const VARIABLE& rhs)
    {
        delete val;
        type = rhs.type;
        switch (type) {
        case IS_INTEGER:
            val = new IntType;
            *(IntType*)val = *(IntType*)rhs.val;
            break;
        case IS_DOUBLE:
            val = new double;
            *(double*)val = *(double*)rhs.val;
            break;
        case IS_MATRIX:
            //val = new MATRIX;
            break;
        }
        return *this;
    }
    VARIABLE operator + (const VARIABLE& rhs) const
    {
        static VARIABLE ans;
        switch (type) {
        case IS_INTEGER:
            switch (rhs.type) {
            case IS_INTEGER:
                ans.type = IS_INTEGER;
                ans.val = new IntType;
                *(IntType*)ans.val = *(IntType*)val + *(IntType*)rhs.val;
                break;
            case IS_DOUBLE:
                ans.type = IS_DOUBLE;
                ans.val = new double;
                *(double*)ans.val = (double)(*(IntType*)val) + *(double*)rhs.val;
                break;
            case IS_MATRIX:
                cerr << "Undefined operator '+' between integer and matrix!\n";
                break;
            }
            break;
        case IS_DOUBLE:
            switch (rhs.type) {
            case IS_INTEGER:
                ans = rhs + *this;
                break;
            case IS_DOUBLE:
                ans.type = IS_DOUBLE;
                ans.val = new double;
                *(double*)ans.val = *(double*)val + *(double*)rhs.val;
                break;
            case IS_MATRIX:
                ans.type = IS_DOUBLE;
                ans.val = new double;
                //*(double*)ans.val = *(double*)val + *(MATRIX*)rhs.val;
                cerr << "Undefined operator '+' between double and matrix!\n";
                break;
            }
        case IS_MATRIX:
            switch (rhs.type) {
            case IS_INTEGER:	//The same as IS_DOUBLE
            case IS_DOUBLE:
                ans = rhs + *this;
                break;
            case IS_MATRIX:
                cerr << "Undefined operator '+' between matrix and matrix!";
                break;
            }
        }
        return ans;
    }
    VARIABLE operator - (const VARIABLE& rhs) const
    {
        static VARIABLE ans;
        switch (type) {
        case IS_INTEGER:
            switch (rhs.type) {
            case IS_INTEGER:
                ans.type = IS_INTEGER;
                ans.val = new IntType;
                *(IntType*)ans.val = *(IntType*)val - *(IntType*)rhs.val;
                break;
            case IS_DOUBLE:
                ans.type = IS_DOUBLE;
                ans.val = new double;
                *(double*)ans.val = (double)(*(IntType*)val) - *(double*)rhs.val;
                break;
            case IS_MATRIX:
                cerr << "Undefined operator '-' between integer and matrix!\n";
                break;
            }
            break;
        case IS_DOUBLE:
            switch (rhs.type) {
            case IS_INTEGER:
                ans.type = IS_DOUBLE;
                ans.val = new double;
                *(double*)ans.val = *(double*)val - (double)(*(IntType*)val);
                break;
            case IS_DOUBLE:
                ans.type = IS_DOUBLE;
                ans.val = new double;
                *(double*)ans.val = *(double*)val + *(double*)rhs.val;
                break;
            case IS_MATRIX:
                //*(double*)ans.val = *(double*)val + *(MATRIX*)rhs.val;
                cerr << "Undefined operator '+' between double and matrix!\n";
                break;
            }
        case IS_MATRIX:
            switch (rhs.type) {
            case IS_INTEGER:
            	cerr << "Undefined operator '-' between matrix and integer!\n";
            case IS_DOUBLE:
                cerr << "Undefined operator '-' between matrix and double!\n";
                break;
            case IS_MATRIX:
                cerr << "Undefined operator '-' between matrix and matrix!";
                break;
            }
        }
        return ans;
    }
    VARIABLE operator * (const VARIABLE& rhs) const
    {
    	static VARIABLE ans;

    	switch (type) {
        case IS_INTEGER:
            switch (rhs.type) {
            case IS_INTEGER:
                ans.type = IS_INTEGER;
                ans.val = new IntType;
                *(IntType*)ans.val = *(IntType*)val * *(IntType*)rhs.val;
                break;
            case IS_DOUBLE:
                ans.type = IS_DOUBLE;
                ans.val = new double;
                *(double*)ans.val = (double)(*(IntType*)val) * *(double*)rhs.val;
                break;
            case IS_MATRIX:
                cerr << "Undefined operator '*' between integer and matrix!\n";
                break;
            }
            break;
        case IS_DOUBLE:
            switch (rhs.type) {
            case IS_INTEGER:
                ans.type = IS_DOUBLE;
                ans.val = new double;
                *(double*)ans.val = *(double*)val * (double)(*(IntType*)val);
            case IS_DOUBLE:
                ans.type = IS_DOUBLE;
                ans.val = new double;
                *(double*)ans.val = *(double*)val * *(double*)rhs.val;
                break;
            case IS_MATRIX:
                ans.type = IS_DOUBLE;
                ans.val = new double;
                //*(double*)ans.val = *(double*)val * *(MATRIX*)rhs.val;
                cerr << "Undefined operator '*' between double and matrix!\n";
                break;
            }
        case IS_MATRIX:
            switch (rhs.type) {
            case IS_INTEGER:
            	cerr << "Undefined operator '*' between matrix and integer!\n";
            case IS_DOUBLE:
                cerr << "Undefined operator '*' between matrix and double!\n";
                break;
            case IS_MATRIX:
                cerr << "Undefined operator '*' between matrix and matrix!";
                break;
            }
        }

    	return ans;
    }
    VARIABLE operator / (const VARIABLE& rhs) const
    {
    	static VARIABLE ans;

    	switch (type) {
        case IS_INTEGER:
            switch (rhs.type) {
            case IS_INTEGER:
                ans.type = IS_INTEGER;
                ans.val = new IntType;
                *(IntType*)ans.val = *(IntType*)val / *(IntType*)rhs.val;
                break;
            case IS_DOUBLE:
                ans.type = IS_DOUBLE;
                ans.val = new double;
                *(double*)ans.val = (double)(*(IntType*)val) / *(double*)rhs.val;
                break;
            case IS_MATRIX:
                cerr << "Undefined operator '/' between integer and matrix!\n";
                break;
            }
            break;
        case IS_DOUBLE:
            switch (rhs.type) {
            case IS_INTEGER:
                ans.type = IS_DOUBLE;
                ans.val = new double;
                *(double*)ans.val = *(double*)val / (double)(*(IntType*)val);
            case IS_DOUBLE:
                ans.type = IS_DOUBLE;
                ans.val = new double;
                *(double*)ans.val = *(double*)val / *(double*)rhs.val;
                break;
            case IS_MATRIX:
                ans.type = IS_DOUBLE;
                ans.val = new double;
                //*(double*)ans.val = *(double*)val / *(MATRIX*)rhs.val;
                cerr << "Undefined operator '/' between double and matrix!\n";
                break;
            }
        case IS_MATRIX:
            switch (rhs.type) {
            case IS_INTEGER:
            	cerr << "Undefined operator '/' between matrix and integer!\n";
            case IS_DOUBLE:
                cerr << "Undefined operator '/' between matrix and double!\n";
                break;
            case IS_MATRIX:
                cerr << "Undefined operator '/' between matrix and matrix!";
                break;
            }
        }

    	return ans;
    }
    VARIABLE operator += (const VARIABLE& rhs)
    {
       /* switch(type){
        case IS_INTEGER:
            switch(rhs.type){
            case IS_INTEGER:
                (*this).type = IS_INTEGER;

                break;
            case IS_DOUBLE:
                (*this).type = IS_DOUBLE;

                break;
            case IS_MATRIX:
                cerr << "Undefined operator '+' between integer and matrix!\n";
                break;
            }
            break;
        case IS_DOUBLE:
            switch (rhs.type) {
            case IS_INTEGER:
                (*this).type = IS_DOUBLE;

                break;
            case IS_DOUBLE:
                (*this).type = IS_DOUBLE;

                break;
            case IS_MATRIX:
                // *(double*)ans.val = *(double*)val + *(MATRIX*)rhs.val;
                cerr << "Undefined operator '+' between double and matrix!\n";
                break;
            }
        case IS_MATRIX:
            switch (rhs.type) {
            case IS_INTEGER:
            	cerr << "Undefined operator '+' between matrix and integer!\n";
            case IS_DOUBLE:
                cerr << "Undefined operator '+' between matrix and double!\n";
                break;
            case IS_MATRIX:
                cerr << "Undefined operator '+' between matrix and matrix!";
                break;
            }
        }*/
		return *this = *this + rhs;
    }

    VARIABLE operator -= (const VARIABLE& rhs)
    {
       /* switch(type){
        case IS_INTEGER:
            switch(rhs.type){
            case IS_INTEGER:
                (*this).type = IS_INTEGER;

                break;
            case IS_DOUBLE:
                (*this).type = IS_DOUBLE;

                break;
            case IS_MATRIX:
                cerr << "Undefined operator '-' between integer and matrix!\n";
                break;
            }
            break;
        case IS_DOUBLE:
            switch (rhs.type) {
            case IS_INTEGER:
                (*this).type = IS_DOUBLE;

                break;
            case IS_DOUBLE:
                (*this).type = IS_DOUBLE;

                break;
            case IS_MATRIX:
                // *(double*)ans.val = *(double*)val - *(MATRIX*)rhs.val;
                cerr << "Undefined operator '-' between double and matrix!\n";
                break;
            }
        case IS_MATRIX:
            switch (rhs.type) {
            case IS_INTEGER:
            	cerr << "Undefined operator '-' between matrix and integer!\n";
            case IS_DOUBLE:
                cerr << "Undefined operator '-' between matrix and double!\n";
                break;
            case IS_MATRIX:
                cerr << "Undefined operator '-' between matrix and matrix!";
                break;
            }
        }*/
		return *this = *this - rhs;
    }

    VARIABLE operator *= (const VARIABLE& rhs)
    {
    	/*switch (type) {
        case IS_INTEGER:
            switch(rhs.type){
            case IS_INTEGER:
                (*this).type = IS_INTEGER;

                break;
            case IS_DOUBLE:
                (*this).type = IS_DOUBLE;

                break;
            case IS_MATRIX:
                cerr << "Undefined operator '*' between integer and matrix!\n";
                break;
            }
            break;
         case IS_DOUBLE:
            switch (rhs.type) {
            case IS_INTEGER:
                (*this).type = IS_DOUBLE;

                break;
            case IS_DOUBLE:
                (*this).type = IS_DOUBLE;

                break;
            case IS_MATRIX:
                // *(double*)ans.val = *(double*)val * *(MATRIX*)rhs.val;
                cerr << "Undefined operator '*' between double and matrix!\n";
                break;
            }
        case IS_MATRIX:
            switch (rhs.type) {
            case IS_INTEGER:
            	cerr << "Undefined operator '*' between matrix and integer!\n";
            case IS_DOUBLE:
                cerr << "Undefined operator '*' between matrix and double!\n";
                break;
            case IS_MATRIX:
                cerr << "Undefined operator '*' between matrix and matrix!";
                break;
            }
        }*/
		return *this = *this * rhs;
    }

    VARIABLE operator /= (const VARIABLE& rhs)
    {
    	/*switch (type) {
       case IS_INTEGER:
            switch(rhs.type){
            case IS_INTEGER:
                (*this).type = IS_INTEGER;

                break;
            case IS_DOUBLE:
                (*this).type = IS_DOUBLE;

                break;
            case IS_MATRIX:
                cerr << "Undefined operator '/' between integer and matrix!\n";
                break;
            }
            break;
        case IS_DOUBLE:
            switch (rhs.type) {
            case IS_INTEGER:
                (*this).type = IS_DOUBLE;

                break;
            case IS_DOUBLE:
                (*this).type = IS_DOUBLE;

                break;
            case IS_MATRIX:
                // *(double*)ans.val = *(double*)val / *(MATRIX*)rhs.val;
                cerr << "Undefined operator '/' between double and matrix!\n";
                break;
            }
        case IS_MATRIX:
            switch (rhs.type) {
            case IS_INTEGER:
            	cerr << "Undefined operator '/' between matrix and integer!\n";
            case IS_DOUBLE:
                cerr << "Undefined operator '/' between matrix and double!\n";
                break;
            case IS_MATRIX:
                cerr << "Undefined operator '/' between matrix and matrix!";
                break;
            }
        }*/
		return *this = *this / rhs;
    }

    #if DEBUG
    void Print(ostream& out)
    {
        switch (type) {
        case IS_INTEGER:
            out << *(IntType*)val;
            break;
        case IS_DOUBLE:
            out << *(double*)val;
            break;
        case IS_MATRIX:
            out << *(MATRIX*)val;
            break;
        }
    }
    #endif // DEBUG
};

struct CONST_OR_VARIABLE{
    bool left_value;
    bool vari;
    VARIABLE* val;

    CONST_OR_VARIABLE() {
        val = NULL;
    }
    CONST_OR_VARIABLE(bool _vari, bool lv) {
        val = NULL;
        vari = _vari;
        left_value = lv;
    }
    /*~CONST_OR_VARIABLE()
    {
        del();
    }*/
    void del() {
        if (!left_value && val) {
            delete val->val;
        }
    }
    bool Copy(const CONST_OR_VARIABLE& rhs, string& information)
    {
        if(left_value && vari) {
            val->Copy(*rhs.val);
            return SUCCEED;
        } else {
            information += "Error: Assign to a right value or a constant value\n";
            return FAIL;
        }
    }
    CONST_OR_VARIABLE operator + (const CONST_OR_VARIABLE& rhs) const {
        static CONST_OR_VARIABLE ans;
        ans.left_value = false;
        ans.vari = false;
        ans.val = new VARIABLE;
        *ans.val = *val + *rhs.val;
        return ans;
    }
    CONST_OR_VARIABLE operator - (const CONST_OR_VARIABLE& rhs) const {
        static CONST_OR_VARIABLE ans;
        ans.left_value = false;
        ans.vari = false;
        ans.val = new VARIABLE;
        *ans.val = *val - *rhs.val;
        return ans;
    }
    CONST_OR_VARIABLE operator * (const CONST_OR_VARIABLE& rhs) const {
        static CONST_OR_VARIABLE ans;
        ans.left_value = false;
        ans.vari = false;
        ans.val = new VARIABLE;
        *ans.val = *val * *rhs.val;
        return ans;
    }
    CONST_OR_VARIABLE operator / (const CONST_OR_VARIABLE& rhs) const {
        static CONST_OR_VARIABLE ans;
        ans.left_value = false;
        ans.vari = false;
        ans.val = new VARIABLE;
        *ans.val = *val / *rhs.val;
        return ans;
    }
    CONST_OR_VARIABLE& operator += (const CONST_OR_VARIABLE& rhs) {
        assert(left_value && vari);
        *val += *rhs.val;
        return *this;
    }
    CONST_OR_VARIABLE& operator -= (const CONST_OR_VARIABLE& rhs) {
        assert(left_value && vari);
        *val -= *rhs.val;
        return *this;
    }
    CONST_OR_VARIABLE& operator *= (const CONST_OR_VARIABLE& rhs) {
        assert(left_value && vari);
        *val *= *rhs.val;
        return *this;
    }
    CONST_OR_VARIABLE& operator /= (const CONST_OR_VARIABLE& rhs) {
        assert(left_value && vari);
        *val /= *rhs.val;
        return *this;
    }

    #if DEBUG
    void Print(ostream& out)
    {
        val->Print(out);
    }
    #endif // DEBUG
};

bool IsBeginningOfConst(char ch);
bool IsPartOfConst(char ch);

void GetConst(string& sth, const char*& str);
void GetConst(VARIABLE& val, const char* str);
string ToString(const VARIABLE& val);

#endif // MYVARIABLE_H_INCLUDED
