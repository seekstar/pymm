#ifndef MYMATH_H_INCLUDED
#define MYMATH_H_INCLUDED

//warning:这里定义0与任何数的最大公约数为另一个数
template<typename T>
T GCD(T a, T b) {
    T r;
    while((bool)b)
        r = a % b, a = b, b = r;
    return a;
}

#endif
