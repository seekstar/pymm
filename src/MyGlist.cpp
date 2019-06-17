#include "MyGlist.h"

ostream& operator << (ostream& out, const GLIST& x) {
    out << '{';
    for (size_t i = 0; i < x.s.size(); ++i) {
        out << x.s[i] << (i == x.s.size()-1 ? '}' : ',');
    }
    return out;
}
