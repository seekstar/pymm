#ifndef MYVALUE_H_INCLUDED
#define MYVALUE_H_INCLUDED

#include <cstdio>

#include "MyInteger.h"
#include "MyMatrix.h"

//fundamental type
enum VAL_TYPE{
    IS_INTEGER,
    IS_DOUBLE
};

struct VALUE {
	VAL_TYPE type;
	void* val;

	VALUE() {
		val = NULL;
	}
	VALUE(const VALUE& v) {
		type = v.type;
		val = v.val;
	}
	/*VALUE(VAL_TYPE t) {
		Init(t);
	}*/
	~VALUE() {
		//del();
	}

	/*void Init(VAL_TYPE t) {
		type = t;
		switch (type) {
		case IS_INTEGER:
			val = new IntType;
			break;
		case IS_DOBLE:
			val = new double;
			break;
		}
	}*/
	void del() {
		switch (type) {
		case IS_INTEGER:
			delete (IntType*)val;
			break;
		case IS_DOUBLE:
			delete (double*)val;
			break;
		}
		val = NULL;
	}
	explicit operator bool() {
		switch(type) {
		case IS_INTEGER:
			return (bool)*(IntType*)val;
		case IS_DOUBLE:
			return abs(*(double*)val) >= 1e-6;
		}
		assert(1);
		return false;
	}
	VALUE& Copy(const VALUE& rhs) {
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
		}
		return *this;
	}
	VALUE operator + (const VALUE& rhs) const {
		static VALUE ans;
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
            }
			break;
        }
		return ans;
	}
	VALUE operator - (const VALUE& rhs) const {
		static VALUE ans;
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
            }
            break;
        case IS_DOUBLE:
            switch (rhs.type) {
            case IS_INTEGER:
                ans = rhs - *this;
                break;
            case IS_DOUBLE:
                ans.type = IS_DOUBLE;
                ans.val = new double;
                *(double*)ans.val = *(double*)val - *(double*)rhs.val;
                break;
            }
			break;
        }
		return ans;
	}
	VALUE operator * (const VALUE& rhs) const {
		static VALUE ans;
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
            }
            break;
        case IS_DOUBLE:
            switch (rhs.type) {
            case IS_INTEGER:
                ans = rhs * *this;
                break;
            case IS_DOUBLE:
                ans.type = IS_DOUBLE;
                ans.val = new double;
                *(double*)ans.val = *(double*)val * *(double*)rhs.val;
                break;
            }
			break;
        }
		return ans;
	}
	VALUE operator / (const VALUE& rhs) const {
		static VALUE ans;
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
            }
            break;
        case IS_DOUBLE:
            switch (rhs.type) {
            case IS_INTEGER:
                ans = rhs / *this;
                break;
            case IS_DOUBLE:
                ans.type = IS_DOUBLE;
                ans.val = new double;
                *(double*)ans.val = *(double*)val / *(double*)rhs.val;
                break;
            }
			break;
        }
		return ans;
	}

	VALUE& operator += (const VALUE& rhs) {
		switch (type) {
		case IS_INTEGER:
			switch (type) {
			case IS_INTEGER:
				*(IntType*)val += *(IntType*)rhs.val;
				break;
			case IS_DOUBLE:
				delete (IntType*)val;
				type = IS_DOUBLE;
				val = new double;
				*(double*)val += *(double*)rhs.val;
				break;
			}
			break;
		case IS_DOUBLE:
			switch (type) {
			case IS_INTEGER:
				*(double*)val += (double)*(IntType*)rhs.val;
				break;
			case IS_DOUBLE:
				*(double*)val += *(double*)rhs.val;
				break;
			}
			break;
		}
		return *this;
	}
	VALUE& operator -= (const VALUE& rhs) {
		switch (type) {
		case IS_INTEGER:
			switch (type) {
			case IS_INTEGER:
				*(IntType*)val -= *(IntType*)rhs.val;
				break;
			case IS_DOUBLE:
				delete (IntType*)val;
				type = IS_DOUBLE;
				val = new double;
				*(double*)val -= *(double*)rhs.val;
				break;
			}
			break;
		case IS_DOUBLE:
			switch (type) {
			case IS_INTEGER:
				*(double*)val -= (double)*(IntType*)rhs.val;
				break;
			case IS_DOUBLE:
				*(double*)val -= *(double*)rhs.val;
				break;
			}
			break;
		}
		return *this;
	}
	VALUE& operator *= (const VALUE& rhs) {
		switch (type) {
		case IS_INTEGER:
			switch (type) {
			case IS_INTEGER:
				*(IntType*)val *= *(IntType*)rhs.val;
				break;
			case IS_DOUBLE:
				delete (IntType*)val;
				type = IS_DOUBLE;
				val = new double;
				*(double*)val *= *(double*)rhs.val;
				break;
			}
			break;
		case IS_DOUBLE:
			switch (type) {
			case IS_INTEGER:
				*(double*)val *= (double)*(IntType*)rhs.val;
				break;
			case IS_DOUBLE:
				*(double*)val *= *(double*)rhs.val;
				break;
			}
			break;
		}
		return *this;
	}
	VALUE& operator /= (const VALUE& rhs) {
		switch (type) {
		case IS_INTEGER:
			switch (type) {
			case IS_INTEGER:
				*(IntType*)val /= *(IntType*)rhs.val;
				break;
			case IS_DOUBLE:
				delete (IntType*)val;
				type = IS_DOUBLE;
				val = new double;
				*(double*)val /= *(double*)rhs.val;
				break;
			}
			break;
		case IS_DOUBLE:
			switch (type) {
			case IS_INTEGER:
				*(double*)val /= (double)*(IntType*)rhs.val;
				break;
			case IS_DOUBLE:
				*(double*)val /= *(double*)rhs.val;
				break;
			}
			break;
		}
		return *this;
	}
};

ostream& operator << (ostream& out, const VALUE& x);

#endif // MYVALUE_H_INCLUDED

