#ifndef MYARITHMETIC_H_INCLUDED
#define MYARITHMETIC_H_INCLUDED

template <typename T>
void AddMod(T &x, T mod) {
    if (x >= mod)
        x -= mod;
}
//--x, then mod. Can handle unsigned.
template <typename T>
void DecMod(T &x, T mod) {
    x = x ? x - 1 : mod - 1;
}

#endif

