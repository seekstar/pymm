#include "MyValue.h"

ostream& operator << (ostream& out, const VALUE& x) {
	switch (x.type) {
	case IS_INTEGER:
		out << *(IntType*)x.val;
		break;
	case IS_DOUBLE:
		out << *(double*)x.val;
		break;
	case IS_BOOL:
		out << *(bool*)x.val;
		break;
	case IS_FRACTION:
		out << *(FRACTION*)x.val;
		break;
	}
	return out;
}
