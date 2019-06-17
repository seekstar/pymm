#ifndef MYGLIST_H_INCLUDED
#define MYGLIST_H_INCLUDED

#include <vector>
#include <ostream>

#include "MyVariable.h"

using namespace std;

class GLIST {
public:
    vector<VARIABLE> s;

    GLIST(){}
    GLIST(size_t n) {
        s.resize(n);
    }
    inline bool OutOfBound(size_t pos) {
        return pos >= s.size();
    }
    void HandleOutOfBound(size_t pos) {
        if (OutOfBound(pos))
            s.resize(pos+1);
    }
    VARIABLE& operator () (size_t pos) {
        HandleOutOfBound(pos);
        return s[pos];
    }
    VARIABLE& operator [] (size_t pos) {
        return s[pos];
    }
};

ostream& operator << (ostream& out, const GLIST& x);

#endif
