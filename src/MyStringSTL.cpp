#include "MyStringSTL.h"

ostream& operator << (ostream& out, const MyString& rhs) {
	return out << rhs.c_str();
}
