#ifndef MYVALUE_H_INCLUDED
#define MYVALUE_H_INCLUDED

#include <cstdio>
#include <cmath>

#include "MyInteger.h"
#include "MyMatrix.h"
#include "MyDouble.h"
#include "fraction.h"

//fundamental type
enum VAL_TYPE{
    IS_INTEGER,
    IS_DOUBLE,
    IS_BOOL,
	IS_FRACTION
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
	~VALUE() {
		//del();
	}

	void del(void* v, VAL_TYPE t) {
		if (NULL == v) return;
		switch (t) {
		case IS_INTEGER:
			delete (IntType*)v;
			break;
		case IS_DOUBLE:
			delete (double*)v;
			break;
		case IS_BOOL:
			delete (bool*)v;
			break;
		case IS_FRACTION:
			delete (FRACTION*)v;
			break;
		}
	}
	void del() {
		if (NULL == val) return;
		del(val, type);
		val = NULL;
	}
	void ChangeType(VAL_TYPE t) {
		if (type == t) return;
		auto tmp = val;
		switch (t) {
		case IS_INTEGER:
			switch (type) {
			case IS_INTEGER:
				assert(1);		//type != t
				break;
			case IS_DOUBLE:
				val = new IntType(*(double*)tmp);
				break;
			case IS_BOOL:
				val = new IntType(*(bool*)tmp);
				break;
			case IS_FRACTION:
				val = new IntType(*(FRACTION*)tmp);
				break;
			}
			break;
		case IS_DOUBLE:
			switch (type) {
			case IS_INTEGER:
				val = new double(*(IntType*)tmp);
				break;
			case IS_DOUBLE:
				assert(1);		//type != t
				break;
			case IS_BOOL:
				val = new double(*(bool*)tmp);
				break;
			case IS_FRACTION:
				val = new double(*(FRACTION*)tmp);
				break;
			}
			break;
		case IS_BOOL:
			switch (type) {
			case IS_INTEGER:
				val = new bool(*(IntType*)tmp);
				break;
			case IS_DOUBLE:
				val = new bool(*(double*)tmp);
				break;
			case IS_BOOL:
				assert(1);		//type != t
				break;
			case IS_FRACTION:
				val = new bool(*(FRACTION*)tmp);
				break;
			}
			break;
		case IS_FRACTION:
			switch (type) {
			case IS_INTEGER:
				val = new FRACTION(*(IntType*)tmp);
				break;
			case IS_DOUBLE:
				val = new FRACTION((IntType)*(double*)tmp);
				break;
			case IS_BOOL:
				val = new FRACTION((IntType)(int)*(bool*)tmp);
				break;
			case IS_FRACTION:
				assert(1);		//type != t
				break;
			}
			break;
		}
		del(tmp, type);
		type = t;
	}
	explicit operator bool() {
		switch (type) {
		case IS_INTEGER:
			return (bool)*(IntType*)val;
		case IS_DOUBLE:
			return (bool)*(double*)val;
		case IS_BOOL:
			return *(bool*)val;
		case IS_FRACTION:
			return (bool)*(FRACTION*)val;
		}
		assert(1);
		return false;
	}
	explicit operator size_t() {
		switch (type) {
		case IS_INTEGER:
			return (size_t)(int)*(IntType*)val;
		case IS_DOUBLE:
			return (size_t)*(double*)val;
		case IS_BOOL:
			return (size_t)*(bool*)val;
		case IS_FRACTION:
			return (size_t)(double)*(FRACTION*)val;
		}
		assert(1);
		return -1;
	}
	VALUE& Copy(const VALUE& rhs) {
		type = rhs.type;
		switch (type) {
		case IS_INTEGER:
			val = new IntType(*(IntType*)rhs.val);
			break;
		case IS_DOUBLE:
			val = new double(*(double*)rhs.val);
			break;
		case IS_BOOL:
			val = new bool(*(bool*)rhs.val);
			break;
		case IS_FRACTION:
			val = new FRACTION(*(FRACTION*)rhs.val);
			break;
		}
		return *this;
	}
	void CleanFraction() {
		assert(type == IS_FRACTION);
		FRACTION& v = *(FRACTION*)val;
		if (v.denominator == 1) {
			IntType* tmp = new IntType(v.numerator);
			delete (FRACTION*)val;
			val = tmp;
			type = IS_INTEGER;
		}
	}
	void GetFractionThenClean(const FRACTION& v) {
		type = IS_FRACTION;
		val = new FRACTION(v);
		CleanFraction();
	}
	VALUE operator + (const VALUE& rhs) const {
		static VALUE ans;
		switch (type) {
        case IS_INTEGER:
            switch (rhs.type) {
            case IS_INTEGER:
				ans.type = IS_INTEGER;
				ans.val = new IntType(*(IntType*)val + *(IntType*)rhs.val);
                break;
            case IS_DOUBLE:
				ans.type = IS_DOUBLE;
				ans.val = new double((*(IntType*)val) + *(double*)rhs.val);
                break;
			case IS_BOOL:
				ans.type = IS_INTEGER;
				ans.val = new IntType(*(IntType*)val + (int)*(bool*)rhs.val);
				break;
			case IS_FRACTION:
				ans.GetFractionThenClean(*(IntType*)val + *(FRACTION*)rhs.val);
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
				ans.val = new double(*(double*)val + *(double*)rhs.val);
                break;
			case IS_BOOL:
				ans.type = IS_DOUBLE;
				ans.val = new double(*(double*)val + (double)*(bool*)rhs.val);
				break;
			case IS_FRACTION:
				ans.type = IS_DOUBLE;
				ans.val = new double(*(double*)val + (double)*(FRACTION*)rhs.val);
				break;
            }
			break;
		case IS_BOOL:
			switch (rhs.type) {
			case IS_INTEGER:
			case IS_DOUBLE:
				ans = rhs + *this;
				break;
			case IS_BOOL:
				ans.type = IS_BOOL;
				ans.val = new bool(*(bool*)val + *(bool*)rhs.val);
				break;
			case IS_FRACTION:
				ans.GetFractionThenClean((FRACTION)(IntType)(int)*(bool*)val + *(FRACTION*)rhs.val);
				break;
			}
			break;
		case IS_FRACTION:
			switch (rhs.type) {
			case IS_INTEGER:
			case IS_DOUBLE:
			case IS_BOOL:
				ans = rhs + *this;
				break;
			case IS_FRACTION:
				ans.GetFractionThenClean(*(FRACTION*)val + *(FRACTION*)rhs.val);
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
			case IS_BOOL:
				ans.type = IS_INTEGER;
				ans.val = new IntType;
				*(IntType*)ans.val = *(IntType*)val - (int)*(bool*)rhs.val;
				break;
			case IS_FRACTION:
				ans.GetFractionThenClean(*(IntType*)val - *(FRACTION*)rhs.val);
				break;
            }
            break;
        case IS_DOUBLE:
            switch (rhs.type) {
            case IS_INTEGER:
                ans.type = IS_DOUBLE;
				ans.val = new double;
				*(double*)ans.val = *(double*)val - (double)*(IntType*)rhs.val;
                break;
            case IS_DOUBLE:
                ans.type = IS_DOUBLE;
                ans.val = new double;
                *(double*)ans.val = *(double*)val - *(double*)rhs.val;
                break;
			case IS_BOOL:
				ans.type = IS_DOUBLE;
				ans.val = new double;
				*(double*)ans.val = *(double*)val - (double)*(bool*)rhs.val;
				break;
			case IS_FRACTION:
				ans.type = IS_DOUBLE;
				ans.val = new double;
				*(double*)ans.val = *(double*)val - (double)*(FRACTION*)rhs.val;
				break;
            }
			break;
		case IS_BOOL:
			switch (rhs.type) {
			case IS_INTEGER:
				ans.type = IS_INTEGER;
				ans.val = new IntType;
				*(IntType*)ans.val = (IntType)(int)*(bool*)val - *(IntType*)rhs.val;
				break;
			case IS_DOUBLE:
				ans.type = IS_DOUBLE;
				ans.val = new double;
				*(double*)ans.val = (double)*(bool*)val - *(double*)rhs.val;
				break;
			case IS_BOOL:
				ans.type = IS_BOOL;
				ans.val = new bool;
				*(bool*)ans.val = *(bool*)val - *(bool*)rhs.val;
				break;
			case IS_FRACTION:
				ans.GetFractionThenClean((FRACTION)(IntType)(int)*(bool*)val - *(FRACTION*)rhs.val);
				break;
			}
			break;
		case IS_FRACTION:
			switch (rhs.type) {
			case IS_INTEGER:
				ans.GetFractionThenClean(*(FRACTION*)val - *(FRACTION*)rhs.val);
				break;
			case IS_DOUBLE:
				ans.type = IS_DOUBLE;
				ans.val = new double;
				*(double*)ans.val = (double)*(FRACTION*)val - *(double*)rhs.val;
				break;
			case IS_BOOL:
				ans.GetFractionThenClean(*(FRACTION*)val - (IntType)(int)*(bool*)rhs.val);
				break;
			case IS_FRACTION:
				ans.GetFractionThenClean(*(FRACTION*)val - *(FRACTION*)rhs.val);
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
			case IS_BOOL:
				ans.type = IS_INTEGER;
				ans.val = new IntType;
				*(IntType*)ans.val = *(IntType*)val * (int)*(bool*)rhs.val;
				break;
			case IS_FRACTION:
				ans.GetFractionThenClean(*(IntType*)val * *(FRACTION*)rhs.val);
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
			case IS_BOOL:
				ans.type = IS_DOUBLE;
				ans.val = new double;
				*(double*)ans.val = *(double*)val * (double)*(bool*)rhs.val;
				break;
			case IS_FRACTION:
				ans.type = IS_DOUBLE;
				ans.val = new double;
				*(double*)ans.val = *(double*)val * (double)*(FRACTION*)rhs.val;
				break;
            }
			break;
		case IS_BOOL:
			switch (rhs.type) {
			case IS_INTEGER:
			case IS_DOUBLE:
				ans = rhs * *this;
				break;
			case IS_BOOL:
				ans.type = IS_BOOL;
				ans.val = new bool;
				*(bool*)ans.val = *(bool*)val && *(bool*)rhs.val;
				break;
			case IS_FRACTION:
				ans.GetFractionThenClean((IntType)(int)*(bool*)val * *(FRACTION*)rhs.val);
				break;
			}
			break;
		case IS_FRACTION:
			switch (rhs.type) {
			case IS_INTEGER:
			case IS_DOUBLE:
			case IS_BOOL:
				ans = rhs * *this;
				break;
			case IS_FRACTION:
				ans.GetFractionThenClean(*(FRACTION*)val * *(FRACTION*)rhs.val);
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
			case IS_BOOL:
				ans.type = IS_INTEGER;
				ans.val = new IntType;
				*(IntType*)ans.val = *(IntType*)val / (int)*(bool*)rhs.val;
				break;
			case IS_FRACTION:
				ans.GetFractionThenClean(*(IntType*)val / *(FRACTION*)rhs.val);
				break;
            }
            break;
        case IS_DOUBLE:
            switch (rhs.type) {
            case IS_INTEGER:
                ans.type = IS_DOUBLE;
				ans.val = new double;
				*(double*)ans.val = *(double*)val / (double)*(IntType*)rhs.val;
                break;
            case IS_DOUBLE:
                ans.type = IS_DOUBLE;
                ans.val = new double;
                *(double*)ans.val = *(double*)val / *(double*)rhs.val;
                break;
			case IS_BOOL:
				ans.type = IS_DOUBLE;
				ans.val = new double;
				*(double*)ans.val = *(double*)val / (double)*(bool*)rhs.val;
				break;
			case IS_FRACTION:
				ans.type = IS_DOUBLE;
				ans.val = new double;
				*(double*)ans.val = *(double*)val / (double)*(FRACTION*)rhs.val;
				break;
            }
			break;
		case IS_BOOL:
			switch (rhs.type) {
			case IS_INTEGER:
				ans.type = IS_INTEGER;
				ans.val = new IntType;
				*(IntType*)ans.val = (IntType)(int)*(bool*)val / *(IntType*)rhs.val;
				break;
			case IS_DOUBLE:
				ans.type = IS_DOUBLE;
				ans.val = new double;
				*(double*)ans.val = (double)*(bool*)val / *(double*)rhs.val;
				break;
			case IS_BOOL:
				ans.type = IS_BOOL;
				ans.val = new bool;
				*(bool*)ans.val = *(bool*)val / *(bool*)rhs.val;
				break;
			case IS_FRACTION:
				ans.GetFractionThenClean((FRACTION)(IntType)(int)*(bool*)val / *(FRACTION*)rhs.val);
				break;
			}
			break;
		case IS_FRACTION:
			switch (rhs.type) {
			case IS_INTEGER:
				ans.GetFractionThenClean(*(FRACTION*)val / *(FRACTION*)rhs.val);
				break;
			case IS_DOUBLE:
				ans.type = IS_DOUBLE;
				ans.val = new double;
				*(double*)ans.val = (double)*(FRACTION*)val / *(double*)rhs.val;
				break;
			case IS_BOOL:
				ans.GetFractionThenClean(*(FRACTION*)val / (IntType)(int)*(bool*)rhs.val);
				break;
			case IS_FRACTION:
				ans.GetFractionThenClean(*(FRACTION*)val / *(FRACTION*)rhs.val);
				break;
			}
			break;
        }
		return ans;
	}
	VALUE operator % (const VALUE& rhs) const {
		static VALUE ans;
		switch (type) {
        case IS_INTEGER:
            switch (rhs.type) {
            case IS_INTEGER:
                ans.type = IS_INTEGER;
                ans.val = new IntType;
                *(IntType*)ans.val = *(IntType*)val % *(IntType*)rhs.val;
                break;
            case IS_DOUBLE:
                ans.type = IS_DOUBLE;
                ans.val = new double;
                *(double*)ans.val = fmod((double)(*(IntType*)val), *(double*)rhs.val);
                break;
			case IS_BOOL:
				ans.type = IS_INTEGER;
				ans.val = new IntType;
				*(IntType*)ans.val = *(IntType*)val % (int)*(bool*)rhs.val;
				break;
			case IS_FRACTION:
				assert(1);
				break;
            }
            break;
        case IS_DOUBLE:
            switch (rhs.type) {
            case IS_INTEGER:
                ans = rhs % *this;
                break;
            case IS_DOUBLE:
                ans.type = IS_DOUBLE;
                ans.val = new double;
                *(double*)ans.val = fmod(*(double*)val, *(double*)rhs.val);
                break;
			case IS_BOOL:
				ans.type = IS_DOUBLE;
				ans.val = new double;
				*(double*)ans.val = fmod(*(double*)val, (double)*(bool*)rhs.val);
				break;
			case IS_FRACTION:
				ans.type = IS_DOUBLE;
				ans.val = new double;
				*(double*)ans.val = fmod(*(double*)val, (double)*(FRACTION*)rhs.val);
				break;
            }
			break;
		case IS_BOOL:
			switch (rhs.type) {
			case IS_INTEGER:
				ans.type = IS_INTEGER;
				ans.val = new IntType;
				*(IntType*)ans.val = (IntType)(int)*(bool*)val % *(IntType*)rhs.val;
				break;
			case IS_DOUBLE:
				ans.type = IS_DOUBLE;
				ans.val = new double;
				*(double*)ans.val = fmod((double)*(bool*)val, *(double*)rhs.val);
				break;
			case IS_BOOL:
				ans.type = IS_BOOL;
				ans.val = new bool;
				*(bool*)ans.val = *(bool*)val % *(bool*)rhs.val;
				break;
			case IS_FRACTION:
				assert(1);
				break;
			}
			break;
		case IS_FRACTION:
			assert(1);
			break;
        }
		return ans;
	}
	VALUE operator - (void) const {
		static VALUE ans;
		switch (type) {
		case IS_INTEGER:
			ans.type = IS_INTEGER;
			ans.val = new IntType;
			*(IntType*)ans.val = -*(IntType*)val;
			break;
		case IS_DOUBLE:
			ans.type = IS_DOUBLE;
			ans.val = new double;
			*(double*)ans.val = -*(double*)val;
			break;
		case IS_BOOL:
			ans.type = IS_BOOL;
			ans.val = new bool;
			*(bool*)ans.val = -*(bool*)val;
			break;
		case IS_FRACTION:
			ans.GetFractionThenClean(-*(FRACTION*)val);
			break;
		}
		return ans;
	}
	VALUE fra_div(const VALUE& rhs) const {
		if (type == IS_INTEGER && rhs.type == IS_INTEGER) {
			static VALUE ans;
			ans.GetFractionThenClean(FRACTION(*(IntType*)val, *(IntType*)rhs.val));
			return ans;
		} else {
			return *this / rhs;
		}
	}

	VALUE& operator += (const VALUE& rhs) {
		switch (type) {
		case IS_INTEGER:
			switch (rhs.type) {
			case IS_INTEGER:
				*(IntType*)val += *(IntType*)rhs.val;
				break;
			case IS_DOUBLE:
				ChangeType(IS_DOUBLE);
				*(double*)val += *(double*)rhs.val;
				break;
			case IS_BOOL:
				*(IntType*)val += (int)*(bool*)rhs.val;
				break;
			case IS_FRACTION:
				ChangeType(IS_FRACTION);
				*(FRACTION*)val += *(FRACTION*)rhs.val;
				CleanFraction();
				break;
			}
			break;
		case IS_DOUBLE:
			switch (rhs.type) {
			case IS_INTEGER:
				*(double*)val += (double)*(IntType*)rhs.val;
				break;
			case IS_DOUBLE:
				*(double*)val += *(double*)rhs.val;
				break;
			case IS_BOOL:
				*(double*)val += *(bool*)rhs.val;
				break;
			case IS_FRACTION:
				*(double*)val += (double)*(FRACTION*)rhs.val;
				break;
			}
			break;
		case IS_BOOL:
			assert(1);
			break;
		case IS_FRACTION:
			switch (rhs.type) {
			case IS_INTEGER:
				*(FRACTION*)val += *(FRACTION*)rhs.val;
				CleanFraction();
				break;
			case IS_DOUBLE:
				ChangeType(IS_DOUBLE);
				*(double*)val += *(double*)rhs.val;
				break;
			case IS_BOOL:
				*(FRACTION*)val += (IntType)(int)*(bool*)rhs.val;
				CleanFraction();
				break;
			case IS_FRACTION:
				*(FRACTION*)val += *(FRACTION*)rhs.val;
				CleanFraction();
				break;
			}
			break;
		}
		return *this;
	}
	VALUE& operator -= (const VALUE& rhs) {
		switch (type) {
		case IS_INTEGER:
			switch (rhs.type) {
			case IS_INTEGER:
				*(IntType*)val -= *(IntType*)rhs.val;
				break;
			case IS_DOUBLE:
				ChangeType(IS_DOUBLE);
				*(double*)val -= *(double*)rhs.val;
				break;
			case IS_BOOL:
				assert(1);
				break;
			case IS_FRACTION:
				ChangeType(IS_FRACTION);
				*(FRACTION*)val -= *(FRACTION*)rhs.val;
				CleanFraction();
				break;
			}
			break;
		case IS_DOUBLE:
			switch (rhs.type) {
			case IS_INTEGER:
				*(double*)val -= (double)*(IntType*)rhs.val;
				break;
			case IS_DOUBLE:
				*(double*)val -= *(double*)rhs.val;
				break;
			case IS_BOOL:
				*(double*)val -= *(bool*)rhs.val;
				break;
			case IS_FRACTION:
				*(double*)val -= (double)*(FRACTION*)rhs.val;
				break;
			}
			break;
		case IS_BOOL:
			assert(1);
			break;
		case IS_FRACTION:
			switch (rhs.type) {
			case IS_INTEGER:
				*(FRACTION*)val -= *(FRACTION*)rhs.val;
				CleanFraction();
				break;
			case IS_DOUBLE:
				ChangeType(IS_DOUBLE);
				*(double*)val -= *(double*)rhs.val;
				break;
			case IS_BOOL:
				*(FRACTION*)val -= (IntType)(int)*(bool*)rhs.val;
				CleanFraction();
				break;
			case IS_FRACTION:
				*(FRACTION*)val -= *(FRACTION*)rhs.val;
				CleanFraction();
				break;
			}
			break;
		}
		return *this;
	}
	VALUE& operator *= (const VALUE& rhs) {
		switch (type) {
		case IS_INTEGER:
			switch (rhs.type) {
			case IS_INTEGER:
				*(IntType*)val *= *(IntType*)rhs.val;
				break;
			case IS_DOUBLE:
				ChangeType(IS_DOUBLE);
				*(double*)val *= *(double*)rhs.val;
				break;
			case IS_BOOL:
				*(IntType*)val *= (int)*(bool*)rhs.val;
				break;
			case IS_FRACTION:
				ChangeType(IS_FRACTION);
				*(FRACTION*)val *= *(FRACTION*)rhs.val;
				CleanFraction();
				break;
			}
			break;
		case IS_DOUBLE:
			switch (rhs.type) {
			case IS_INTEGER:
				*(double*)val *= (double)*(IntType*)rhs.val;
				break;
			case IS_DOUBLE:
				*(double*)val *= *(double*)rhs.val;
				break;
			case IS_BOOL:
				*(double*)val *= *(bool*)rhs.val;
				break;
			case IS_FRACTION:
				*(double*)val *= (double)*(FRACTION*)rhs.val;
				break;
			}
			break;
		case IS_BOOL:
			assert(1);
			break;
		case IS_FRACTION:
			switch (rhs.type) {
			case IS_INTEGER:
				*(FRACTION*)val *= *(FRACTION*)rhs.val;
				CleanFraction();
				break;
			case IS_DOUBLE:
				ChangeType(IS_DOUBLE);
				*(double*)val *= *(double*)rhs.val;
				break;
			case IS_BOOL:
				*(FRACTION*)val *= (IntType)(int)*(bool*)rhs.val;
				CleanFraction();
				break;
			case IS_FRACTION:
				*(FRACTION*)val *= *(FRACTION*)rhs.val;
				CleanFraction();
				break;
			}
			break;
		}
		return *this;
	}
	VALUE& operator /= (const VALUE& rhs) {
		switch (type) {
		case IS_INTEGER:
			switch (rhs.type) {
			case IS_INTEGER:
				*(IntType*)val /= *(IntType*)rhs.val;
				break;
			case IS_DOUBLE:
				ChangeType(IS_DOUBLE);
				*(double*)val /= *(double*)rhs.val;
				break;
			case IS_BOOL:
				*(IntType*)val /= (int)*(bool*)rhs.val;
				break;
			case IS_FRACTION:
				ChangeType(IS_FRACTION);
				*(FRACTION*)val /= *(FRACTION*)rhs.val;
				CleanFraction();
				break;
			}
			break;
		case IS_DOUBLE:
			switch (rhs.type) {
			case IS_INTEGER:
				*(double*)val /= (double)*(IntType*)rhs.val;
				break;
			case IS_DOUBLE:
				*(double*)val /= *(double*)rhs.val;
				break;
			case IS_BOOL:
				*(double*)val /= *(bool*)rhs.val;
				break;
			case IS_FRACTION:
				*(double*)val /= (double)*(FRACTION*)rhs.val;
				break;
			}
			break;
		case IS_BOOL:
			assert(1);
			break;
		case IS_FRACTION:
			switch (rhs.type) {
			case IS_INTEGER:
				*(FRACTION*)val /= *(FRACTION*)rhs.val;
				CleanFraction();
				break;
			case IS_DOUBLE:
				ChangeType(IS_DOUBLE);
				*(double*)val /= *(double*)rhs.val;
				break;
			case IS_BOOL:
				*(FRACTION*)val /= (IntType)(int)*(bool*)rhs.val;
				CleanFraction();
				break;
			case IS_FRACTION:
				*(FRACTION*)val /= *(FRACTION*)rhs.val;
				CleanFraction();
				break;
			}
			break;
		}
		return *this;
	}
	VALUE& operator %= (const VALUE& rhs) {
		switch (type) {
		case IS_INTEGER:
			switch (rhs.type) {
			case IS_INTEGER:
				*(IntType*)val %= *(IntType*)rhs.val;
				break;
			case IS_DOUBLE:
				ChangeType(IS_DOUBLE);
				*(double*)val = fmod(*(double*)val, *(double*)rhs.val);
				break;
			case IS_BOOL:
				*(IntType*)val %= (int)*(bool*)rhs.val;
				break;
			case IS_FRACTION:
				assert(1);
				break;
			}
			break;
		case IS_DOUBLE:
			switch (rhs.type) {
			case IS_INTEGER:
				*(double*)val = fmod(*(double*)val, (double)*(IntType*)rhs.val);
				break;
			case IS_DOUBLE:
				*(double*)val = fmod(*(double*)val, *(double*)rhs.val);
				break;
			case IS_BOOL:
			case IS_FRACTION:
				assert(1);
				break;
			}
			break;
		case IS_BOOL:
			assert(1);
			break;
		case IS_FRACTION:
			assert(1);
			break;
		}
		return *this;
	}
	VALUE& operator ++ () {
		switch (type) {
		case IS_INTEGER:
			++*(IntType*)val;
			break;
		case IS_DOUBLE:
			++*(double*)val;
			break;
		case IS_BOOL:
			//++*(bool*)val;
			assert(1);	//use of an operand of type ‘bool’ in ‘operator++’ is forbidden in C++1z
			break;
		case IS_FRACTION:
			*(FRACTION*)val += (FRACTION)(IntType)1;
			CleanFraction();
			break;
		}
		return *this;
	}
	VALUE& operator -- () {
		switch (type) {
		case IS_INTEGER:
			--*(IntType*)val;
			break;
		case IS_DOUBLE:
			--*(double*)val;
			break;
		case IS_BOOL:
			//--*(bool*)val;
			assert(1);	//use of an operand of type ‘bool’ in ‘operator--’ is forbidden in C++1z
			break;
		case IS_FRACTION:
			*(FRACTION*)val -= (FRACTION)(IntType)1;
			CleanFraction();
			break;
		}
		return *this;
	}
	VALUE& fra_div_eq(const VALUE& rhs) {
		if (type == IS_INTEGER && rhs.type == IS_INTEGER) {
			FRACTION* tmp = new FRACTION(*(IntType*)val, *(IntType*)rhs.val);
			del();
			type = IS_FRACTION;
			val = tmp;
			return *this;
		} else {
			return *this /= rhs;
		}
	}

	VALUE operator < (const VALUE& rhs) const {
		static VALUE ans;
		ans.type = IS_BOOL;
		ans.val = new bool;
		switch (type) {
		case IS_INTEGER:
			switch (rhs.type) {
			case IS_INTEGER:
				*(bool*)ans.val = *(IntType*)val < *(IntType*)rhs.val;
				break;
			case IS_DOUBLE:
				*(bool*)ans.val = (double)*(IntType*)val < *(double*)rhs.val;
				break;
			case IS_BOOL:
				assert(1);
				break;
			case IS_FRACTION:
				*(bool*)ans.val = *(IntType*)val < *(FRACTION*)rhs.val;
				break;
			}
			break;
		case IS_DOUBLE:
			switch (rhs.type) {
			case IS_INTEGER:
				*(bool*)ans.val = *(double*)val < (double)*(IntType*)rhs.val;
				break;
			case IS_DOUBLE:
				*(bool*)ans.val = *(double*)val < *(double*)rhs.val;
				break;
			case IS_BOOL:
				assert(1);
				break;
			case IS_FRACTION:
				*(bool*)ans.val = *(double*)val < (double)*(FRACTION*)rhs.val;
				break;
			}
			break;
		case IS_BOOL:
			assert(1);
			break;
		case IS_FRACTION:
			switch (rhs.type) {
			case IS_INTEGER:
				*(bool*)ans.val = *(FRACTION*)val < *(IntType*)rhs.val;
				break;
			case IS_DOUBLE:
				*(bool*)ans.val = (double)*(FRACTION*)val < *(double*)rhs.val;
				break;
			case IS_BOOL:
				*(bool*)ans.val = *(FRACTION*)val < (IntType)(int)*(bool*)rhs.val;
				break;
			case IS_FRACTION:
				*(bool*)ans.val = *(FRACTION*)val < *(FRACTION*)rhs.val;
				break;
			}
			break;
		}
		return ans;
	}
	VALUE operator > (const VALUE& rhs) const {
		return rhs < *this;
	}
	VALUE operator <= (const VALUE& rhs) const {
		VALUE ans(*this > rhs);
		*(bool*)ans.val = !*(bool*)ans.val;
		return ans;
	}
	VALUE operator >= (const VALUE& rhs) const {
		return rhs <= *this;
	}
	VALUE operator == (const VALUE& rhs) const {
		VALUE ans(*this < rhs);
		VALUE ans1(*this > rhs);
		*(bool*)ans.val = !*(bool*)ans.val && !*(bool*)ans1.val;
		ans1.del();
		return ans;
	}
	VALUE operator != (const VALUE& rhs) const {
		VALUE ans(*this == rhs);
		*(bool*)ans.val = !*(bool*)ans.val;
		return ans;
	}
};

ostream& operator << (ostream& out, const VALUE& x);

#endif // MYVALUE_H_INCLUDED

