#ifndef MYVALUE_H_INCLUDED
#define MYVALUE_H_INCLUDED

#include <cstdio>
#include <cmath>

#include "MyInteger.h"
#include "MyMatrix.h"
#include "MyDouble.h"

//fundamental type
enum VAL_TYPE{
    IS_INTEGER,
    IS_DOUBLE,
    IS_BOOL
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

	void del() {
		if (NULL == val) return;
		switch (type) {
		case IS_INTEGER:
			delete (IntType*)val;
			break;
		case IS_DOUBLE:
			delete (double*)val;
			break;
		case IS_BOOL:
			delete (bool*)val;
			break;
		}
		val = NULL;
	}
	explicit operator bool() {
		switch (type) {
		case IS_INTEGER:
			return (bool)*(IntType*)val;
		case IS_DOUBLE:
			return abs(*(double*)val) >= 1e-6;
		case IS_BOOL:
			return *(bool*)val;
		}
		assert(1);
		return false;
	}
	explicit operator size_t() {
		switch (type) {
		case IS_INTEGER:
			return (size_t)(int)*(IntType*)val;
		case IS_DOUBLE:
			return (int)*(double*)val;
		case IS_BOOL:
			return (int)*(bool*)val;
		}
		assert(1);
		return -1;
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
		case IS_BOOL:
			val = new bool;
			*(bool*)val = *(bool*)rhs.val;
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
			case IS_BOOL:
				ans.type = IS_INTEGER;
				ans.val = new IntType;
				*(IntType*)ans.val = *(IntType*)val + (IntType)(int)*(bool*)rhs.val;
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
			case IS_BOOL:
				ans.type = IS_DOUBLE;
				ans.val = new double;
				*(double*)ans.val = *(double*)val + (double)*(bool*)rhs.val;
				break;
            }
			break;
		case IS_BOOL:
			ans = rhs + *this;
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
				*(IntType*)ans.val = *(IntType*)val - (IntType)(int)*(bool*)rhs.val;
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
			case IS_BOOL:
				assert(1);
				break;
            }
			break;
		case IS_BOOL:
			assert(1);
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
				assert(1);
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
				assert(1);
				break;
            }
			break;
		case IS_BOOL:
			assert(1);
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
				assert(1);
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
			case IS_BOOL:
				assert(1);
				break;
            }
			break;
		case IS_BOOL:
			assert(1);
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
				assert(1);
				break;
            }
			break;
		case IS_BOOL:
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
		}
		return ans;
	}

	VALUE& operator += (const VALUE& rhs) {
		switch (type) {
		case IS_INTEGER:
			switch (rhs.type) {
			case IS_INTEGER:
				*(IntType*)val += *(IntType*)rhs.val;
				break;
			case IS_DOUBLE:
				delete (IntType*)val;
				type = IS_DOUBLE;
				val = new double;
				*(double*)val += *(double*)rhs.val;
				break;
			case IS_BOOL:
				assert(1);
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
				assert(1);
				break;
			}
			break;
		case IS_BOOL:
			assert(1);
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
				delete (IntType*)val;
				type = IS_DOUBLE;
				val = new double;
				*(double*)val -= *(double*)rhs.val;
				break;
			case IS_BOOL:
				assert(1);
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
				assert(1);
				break;
			}
			break;
		case IS_BOOL:
			assert(1);
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
				delete (IntType*)val;
				type = IS_DOUBLE;
				val = new double;
				*(double*)val *= *(double*)rhs.val;
				break;
			case IS_BOOL:
				assert(1);
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
				assert(1);
				break;
			}
			break;
		case IS_BOOL:
			assert(1);
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
				delete (IntType*)val;
				type = IS_DOUBLE;
				val = new double;
				*(double*)val /= *(double*)rhs.val;
				break;
			case IS_BOOL:
				assert(1);
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
				assert(1);
				break;
			}
			break;
		case IS_BOOL:
			assert(1);
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
				delete (IntType*)val;
				type = IS_DOUBLE;
				val = new double;
				*(double*)val = fmod(*(double*)val, *(double*)rhs.val);
				break;
			case IS_BOOL:
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
				assert(1);
				break;
			}
			break;
		case IS_BOOL:
			assert(1);
			break;
		}
		return *this;
	}

	VALUE operator < (const VALUE& rhs) {
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
			}
			break;
		case IS_BOOL:
			assert(1);
			break;
		}
		return ans;
	}
	VALUE operator <= (const VALUE& rhs) {
		static VALUE ans;
		ans.type = IS_BOOL;
		ans.val = new bool;
		switch (type) {
		case IS_INTEGER:
			switch (rhs.type) {
			case IS_INTEGER:
				*(bool*)ans.val = *(IntType*)val <= *(IntType*)rhs.val;
				break;
			case IS_DOUBLE:
				*(bool*)ans.val = (double)*(IntType*)val <= *(double*)rhs.val;
				break;
			case IS_BOOL:
				assert(1);
				break;
			}
			break;
		case IS_DOUBLE:
			switch (rhs.type) {
			case IS_INTEGER:
				*(bool*)ans.val = *(double*)val <= (double)*(IntType*)rhs.val;
				break;
			case IS_DOUBLE:
				*(bool*)ans.val = *(double*)val <= *(double*)rhs.val;
				break;
			case IS_BOOL:
				assert(1);
				break;
			}
			break;
		case IS_BOOL:
			assert(1);
			break;
		}
		return ans;
	}
	VALUE operator > (const VALUE& rhs) {
		static VALUE ans;
		ans.type = IS_BOOL;
		ans.val = new bool;
		switch (type) {
		case IS_INTEGER:
			switch (rhs.type) {
			case IS_INTEGER:
				*(bool*)ans.val = *(IntType*)val > *(IntType*)rhs.val;
				break;
			case IS_DOUBLE:
				*(bool*)ans.val = (double)*(IntType*)val > *(double*)rhs.val;
				break;
			case IS_BOOL:
				assert(1);
				break;
			}
			break;
		case IS_DOUBLE:
			switch (rhs.type) {
			case IS_INTEGER:
				*(bool*)ans.val = *(double*)val > (double)*(IntType*)rhs.val;
				break;
			case IS_DOUBLE:
				*(bool*)ans.val = *(double*)val > *(double*)rhs.val;
				break;
			case IS_BOOL:
				assert(1);
				break;
			}
			break;
		case IS_BOOL:
			assert(1);
			break;
		}
		return ans;
	}
	VALUE operator >= (const VALUE& rhs) {
		static VALUE ans;
		ans.type = IS_BOOL;
		ans.val = new bool;
		switch (type) {
		case IS_INTEGER:
			switch (rhs.type) {
			case IS_INTEGER:
				*(bool*)ans.val = *(IntType*)val >= *(IntType*)rhs.val;
				break;
			case IS_DOUBLE:
				*(bool*)ans.val = (double)*(IntType*)val >= *(double*)rhs.val;
				break;
			case IS_BOOL:
				assert(1);
				break;
			}
			break;
		case IS_DOUBLE:
			switch (rhs.type) {
			case IS_INTEGER:
				*(bool*)ans.val = *(double*)val >= (double)*(IntType*)rhs.val;
				break;
			case IS_DOUBLE:
				*(bool*)ans.val = *(double*)val >= *(double*)rhs.val;
				break;
			case IS_BOOL:
				assert(1);
				break;
			}
			break;
		case IS_BOOL:
			assert(1);
			break;
		}
		return ans;
	}
	VALUE operator == (const VALUE& rhs) {
		static VALUE ans;
		ans.type = IS_BOOL;
		ans.val = new bool;
		switch (type) {
		case IS_INTEGER:
			switch (rhs.type) {
			case IS_INTEGER:
				*(bool*)ans.val = *(IntType*)val == *(IntType*)rhs.val;
				break;
			case IS_DOUBLE:
				*(bool*)ans.val = Equal((double)*(IntType*)val, *(double*)rhs.val);
				break;
			case IS_BOOL:
				*(bool*)ans.val = *(IntType*)val == (IntType)(int)*(bool*)rhs.val;
				break;
			}
			break;
		case IS_DOUBLE:
			switch (rhs.type) {
			case IS_INTEGER:
				*(bool*)ans.val = Equal(*(double*)val, (double)*(IntType*)rhs.val);
				break;
			case IS_DOUBLE:
				*(bool*)ans.val = Equal(*(double*)val, *(double*)rhs.val);
				break;
			case IS_BOOL:
				*(bool*)ans.val = Equal(*(double*)val, (double)(int)*(bool*)rhs.val);
				break;
			}
			break;
		case IS_BOOL:
			switch (rhs.type) {
            case IS_INTEGER:
                *(bool*)ans.val = *(bool*)val == (bool)*(IntType*)rhs.val;
                break;
            case IS_DOUBLE:
                *(bool*)ans.val = *(bool*)val == (bool)*(double*)rhs.val;
                break;
            case IS_BOOL:
                *(bool*)ans.val = *(bool*)val == *(bool*)rhs.val;
                break;
			}
			break;
		}
		return ans;
	}
	VALUE operator != (const VALUE& rhs) {
		static VALUE ans;
		ans.type = IS_BOOL;
		ans.val = new bool;
		switch (type) {
		case IS_INTEGER:
			switch (rhs.type) {
			case IS_INTEGER:
				*(bool*)ans.val = *(IntType*)val != *(IntType*)rhs.val;
				break;
			case IS_DOUBLE:
				*(bool*)ans.val = NotEqual((double)*(IntType*)val, *(double*)rhs.val);
				break;
			case IS_BOOL:
				assert(1);
				break;
			}
			break;
		case IS_DOUBLE:
			switch (rhs.type) {
			case IS_INTEGER:
				*(bool*)ans.val = NotEqual(*(double*)val, (double)*(IntType*)rhs.val);
				break;
			case IS_DOUBLE:
				*(bool*)ans.val = NotEqual(*(double*)val, *(double*)rhs.val);
				break;
			case IS_BOOL:
				assert(1);
				break;
			}
			break;
		case IS_BOOL:
			assert(1);
			break;
		}
		return ans;
	}
	VALUE operator && (const VALUE& rhs) {
		static VALUE ans;
		ans.type = IS_BOOL;
		ans.val = new bool;
		switch (type) {
		case IS_INTEGER:
			switch (rhs.type) {
			case IS_INTEGER:
				*(bool*)ans.val = (bool)*(IntType*)val && (bool)*(IntType*)rhs.val;
				break;
			case IS_DOUBLE:
				*(bool*)ans.val = (bool)*(IntType*)val && *(bool*)rhs.val;
				break;
			case IS_BOOL:
				*(bool*)ans.val = (bool)*(IntType*)val && *(bool*)rhs.val;
				break;
			}
			break;
		case IS_DOUBLE:
			switch (rhs.type) {
			case IS_INTEGER:
				*(bool*)ans.val = NotZero(*(double*)val) && (bool)*(IntType*)rhs.val;
				break;
			case IS_DOUBLE:
				*(bool*)ans.val = NotZero(*(double*)val) && NotZero(*(double*)rhs.val);
				break;
			case IS_BOOL:
				*(bool*)ans.val = (bool)*(double*)val && *(bool*)rhs.val;
				break;
			}
			break;
		case IS_BOOL:
			switch (rhs.type) {
            case IS_INTEGER:
                *(bool*)ans.val = *(bool*)val && (bool)*(IntType*)rhs.val;
                break;
            case IS_DOUBLE:
                *(bool*)ans.val = *(bool*)val && NotZero(*(double*)rhs.val);
                break;
            case IS_BOOL:
                *(bool*)ans.val = *(bool*)val && *(bool*)rhs.val;
                break;
			}
			break;
		}
		return ans;
	}
	VALUE operator || (const VALUE& rhs) {
		static VALUE ans;
		ans.type = IS_BOOL;
		ans.val = new bool;
		switch (type) {
		case IS_INTEGER:
			switch (rhs.type) {
			case IS_INTEGER:
				*(bool*)ans.val = *(IntType*)val || *(IntType*)rhs.val;
				break;
			case IS_DOUBLE:
				*(bool*)ans.val = (double)*(IntType*)val || *(double*)rhs.val;
				break;
			case IS_BOOL:
				*(bool*)ans.val = (bool)*(IntType*)val || *(bool*)rhs.val;
				break;
			}
			break;
		case IS_DOUBLE:
			switch (rhs.type) {
			case IS_INTEGER:
				*(bool*)ans.val = *(double*)val || (double)*(IntType*)rhs.val;
				break;
			case IS_DOUBLE:
				*(bool*)ans.val = *(double*)val || *(double*)rhs.val;
				break;
			case IS_BOOL:
				*(bool*)ans.val = NotZero(*(double*)val) || *(bool*)rhs.val;
				break;
			}
			break;
		case IS_BOOL:
			switch (rhs.type) {
            case IS_INTEGER:
                *(bool*)ans.val = (bool)*(IntType*)val || *(bool*)rhs.val;
                break;
            case IS_DOUBLE:
                *(bool*)ans.val = *(bool*)val || NotZero(*(double*)rhs.val);
                break;
            case IS_BOOL:
                *(bool*)ans.val = *(bool*)val || *(bool*)rhs.val;
                break;
			}
			break;
		}
		return ans;
	}
};

ostream& operator << (ostream& out, const VALUE& x);

#endif // MYVALUE_H_INCLUDED

