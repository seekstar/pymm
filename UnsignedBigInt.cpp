#include "UnsignedBigInt.h"

using namespace std;

UnsignedBigInt operator + (LL a, const UnsignedBigInt& b)
{
    return b + a;
}

UnsignedBigInt operator * (int a, const UnsignedBigInt& b)
{
    return b * a;
}

bool operator < (const int& a, const UnsignedBigInt& b)
{
    return b.s.size() == 1 ? (a < b.s[0]) : !b.s.empty();
}

template<typename T1, typename T2>
bool operator != (const T1& a, const T2& b)
{
    return !(a == b);
}
template<typename T1, typename T2>
bool operator > (const T1& a, const T2& b)
{
    return b < a;
}
template<typename T1, typename T2>
bool operator <= (const T1& a, const T2& b)
{
    return !(b < a);
}
template<typename T1, typename T2>
bool operator >= (const T1& a, const T2& b)
{
    return !(a < b);
}

UnsignedBigInt sqrt(const UnsignedBigInt& x, int m)
{
    UnsignedBigInt x0;
    int n = x.s.size();

    if(m <= 1)
    {
        assert(m >= 0);
        if(1 == m)
            x0 = x;
    }
    else if(n <= m)
    {
        int L = 0, R = x.BASE - 1, mid;
        while(L < R)
        {
            mid = L + ((R - L + 1) >> 1);
            if((UnsignedBigInt(mid) ^ m) <= x)
                L = mid;
            else
                R = mid - 1;
        }
        x0.s.push_back(L);
    }
    else if(n <= (m << 1))
    {
        x0.s.resize(2, 0);
        int L = 0, R = x.BASE - 1, mid;
        while(L < R)
        {
            mid = L + ((R - L + 1) >> 1);
            x0.s[1] = mid;
            if((x0 ^ m) <= x)
                L = mid;
            else
                R = mid - 1;
        }
        x0.s[1] = L;
        L = 0, R = x.BASE - 1;
        while(L < R)
        {
            mid = L + ((R - L + 1) >> 1);
            x0.s[0] = mid;
            if((x0 ^ m) <= x)
                L = mid;
            else
                R = mid - 1;
        }
        x0.s[0] = L;
    }
    else
    {
        int mov = (n / m) >> 1;//开方后右边的位数
        x0.s.assign(x.s.begin() + mov * m, x.s.end());
        x0 = (sqrt(x0, m)+1LL).Move_left_BASE(mov);//+1,使其大于零点
        UnsignedBigInt x1;
        do
        {
            x1 = ((m-1)*x0+x/(x0^(m-1)))/m;
            swap(x0, x1);
        }
        while(x0 < x1);
        swap(x0, x1);
        /*x0 = ((m-1)*x0+x/(x0^(m-1)))/m;
        x0 = ((m-1)*x0+x/(x0^(m-1)))/m;*/
    }
    return x0;
}

ostream& operator << (ostream& out, const UnsignedBigInt& a)
{
    return out << (string)a;
}

istream& operator >> (istream& in, UnsignedBigInt& a)
{
    string str;
    if(in >> str)
        a = str;
    return in;
}
