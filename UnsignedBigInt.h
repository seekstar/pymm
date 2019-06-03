#ifndef UNSIGNEDBIGINT_H_INCLUDED
#define UNSIGNEDBIGINT_H_INCLUDED

#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdio>
#include <cassert>
#include <cstring>
#include <sstream>
#include <string>

#include "MyString.h"

using namespace std;

typedef long long LL;

struct UnsignedBigInt;

UnsignedBigInt operator + (LL a, const UnsignedBigInt& b);
UnsignedBigInt operator * (int a, const UnsignedBigInt& b);
bool operator < (const int& a, const UnsignedBigInt& b);

template<typename T1, typename T2>
bool operator != (const T1& a, const T2& b);

template<typename T1, typename T2>
bool operator > (const T1& a, const T2& b);

template<typename T1, typename T2>
bool operator <= (const T1& a, const T2& b);

template<typename T1, typename T2>
bool operator >= (const T1& a, const T2& b);

UnsignedBigInt sqrt(const UnsignedBigInt& x, int m);

const long long tens[] = {1LL,10LL,100LL,1000LL,10000LL,100000LL,1000000LL,10000000LL,100000000LL,1000000000LL};
const int pow2[] = {1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768,65536,131072,262144,524288,1048576,
                    2097152,4194304,8388608,16777216,33554432,67108864,134217728,268435456,536870912,1073741824
                   };
struct UnsignedBigInt
{
    static const int BASE = 1000000000;
    static const int WIDTH = 9;

    vector<int>s;

    UnsignedBigInt() {}
    explicit UnsignedBigInt(int num) {
        s.push_back(num);
    }
    explicit UnsignedBigInt(LL num)
    {
        *this = num;
    }
    explicit UnsignedBigInt(const string& str)
    {
        *this = str;
    }
    explicit UnsignedBigInt(const char* str)
    {
        *this = str;
    }
    explicit UnsignedBigInt(const vector<int>& in): s(in)
    {
        clean();
    }
    UnsignedBigInt& clean()
    {
        while(!s.empty() && !s.back())
            s.pop_back();
        return *this;
    }

    explicit operator LL()
    {
        assert(1);//dangerous function
        LL ans;
        if(s.empty())
            ans = 0;
        else
        {
            ans = s[0];
            if(s.size() > 1)
                ans += (LL)s[1] * BASE;
        }
        return ans;
    }
    explicit operator double() const
    {
        double ans = 1;
        double k = 1;
        for (size_t i = 0; i < s.size(); ++i, k *= BASE) {
            ans *= k * s[i];
        }
        return ans;
    }
    explicit operator string() const
    {
        ostringstream ans;
        if (s.empty()) {
            ans << '0';
        } else {
            ans << s.back();
            for(int i = (int)s.size()-2; i >= 0; --i)
                ans << setfill('0') << setw(WIDTH) << s[i];
        }
        return ans.str();
    }

    /*UnsignedBigInt& operator = (const int num) {
        assert(num < BASE);
        s.resize(1);
        s[0] = num;
        return *this;
    }*/
    UnsignedBigInt& operator = (LL num)
    {
        s.clear();
        while (num)
        {
            s.push_back(num % BASE);
            num /= BASE;
        }
        return clean();
    }

    UnsignedBigInt& assign(const char* str, int slen)
    {
        int len;
        int ended, start;

        s.clear();
        len = slen%WIDTH ? slen / WIDTH + 1 : slen / WIDTH;
        for (int i = 0; i < len; i++)
        {
            ended = slen - i*WIDTH;
            start = max(0, ended - WIDTH);
            s.push_back(MyAtoi(str+start, ended-start));
        }
        return clean();
    }
    UnsignedBigInt& operator = (const string& str)
    {
        return assign(str.c_str(), str.length());
    }
    UnsignedBigInt& operator = (const char* str)
    {
        return assign(str, strlen(str));
    }

    //Independent
    UnsignedBigInt& AddEq(const UnsignedBigInt& b, int aBegin = 0, int bBegin = 0)
    {
        LL remain = 0;

        if((int)s.size() - aBegin > (int)b.s.size() - bBegin)
        {
            for(; bBegin < (int)b.s.size(); aBegin++, bBegin++)
            {
                remain += (LL)s[aBegin] + b.s[bBegin];
                s[aBegin] = remain % BASE;
                remain /= BASE;
            }
            for(; aBegin < (int)s.size(); aBegin++)
            {
                remain += s[aBegin];
                s[aBegin] = remain % BASE;
                remain /= BASE;
            }
        }
        else
        {
            if(aBegin < (int)s.size())
            {
                for(; aBegin < (int)s.size(); aBegin++, bBegin++)
                {
                    remain += (LL)s[aBegin] + b.s[bBegin];
                    s[aBegin] = remain % BASE;
                    remain /= BASE;
                }
            }
            else
                s.resize(aBegin, 0);
            for(; bBegin < (int)b.s.size(); bBegin++)
            {
                s.push_back((b.s[bBegin] + remain) % BASE);
                remain = (b.s[bBegin] + remain) / BASE;
            }
        }
        if(remain)
            s.push_back(remain);
        return *this;
    }
    UnsignedBigInt& operator += (const UnsignedBigInt& b)
    {
        return AddEq(b);
    }
    UnsignedBigInt operator + (const UnsignedBigInt& b) const
    {
        UnsignedBigInt c = *this;
        return c += b;
    }

    //Independent
    UnsignedBigInt& operator += (LL num)
    {
        assert(num >= 0 && num - 1 + BASE >= 0);
        size_t i;
        for(i = 0; num && i < s.size() ; i++)
        {
            num += s[i];
            s[i] = num % BASE;
            num /= BASE;
        }
        if(num)
            s.push_back(num);
        return *this;
    }
    UnsignedBigInt operator + (LL num) const
    {
        UnsignedBigInt ans = *this;
        return ans += num;
    }
    friend UnsignedBigInt operator + (LL a, const UnsignedBigInt& b);

    //Independent
    UnsignedBigInt& operator *= (const int& num)
    {
        assert(0 <= num && num < BASE);
        if(num)
        {
            LL remain = 0;
            for(size_t i = 0; i < s.size(); i++)
            {
                remain += (LL)s[i] * num;
                s[i]=remain % BASE;
                remain /= BASE;
            }
            if(remain)
                s.push_back(remain);
        }
        else
            s.clear();
        return *this;
    }
    inline UnsignedBigInt operator * (const int& num) const
    {
        UnsignedBigInt ans = *this;
        ans *= num;
        return ans;
    }
    friend UnsignedBigInt operator * (int a, const UnsignedBigInt& b);
    UnsignedBigInt operator * (const UnsignedBigInt& b) const
    {
        UnsignedBigInt ans;
        for(size_t j = 0; j < b.s.size(); j++)
            ans.AddEq(*this * b.s[j], j);
        return ans;
    }
    UnsignedBigInt& operator *= (const UnsignedBigInt& b)
    {
        return *this = *this * b;
    }

    int cmp(const UnsignedBigInt& b)const
    {
        if(s.size() != b.s.size())
            return (int)s.size() - (int)b.s.size();
        else if(s.size() == 0 && b.s.size() == 0)
            return 0;
        else
        {
            int i;
            for(i = (int)s.size()-1; i > 0 && s[i] == b.s[i]; i--);

            return s[i] - b.s[i];
        }
    }
    bool operator < (const UnsignedBigInt& b)const
    {
        return cmp(b) < 0;
    }
    bool operator > (const UnsignedBigInt& b)const
    {
        return cmp(b) > 0;
    }
    bool operator == (const UnsignedBigInt& b)const
    {
        return cmp(b) == 0;
    }
    bool operator != (const UnsignedBigInt& b) const
    {
        return cmp(b) != 0;
    }
    bool operator <= (const UnsignedBigInt& b)const
    {
        return cmp(b) <= 0;
    }
    bool operator >= (const UnsignedBigInt& b)const
    {
        return cmp(b) >= 0;
    }

    bool operator == (const int b) const
    {
        return s.size() == 1 ? (s[0] == b) : (s.size() ? 0 : b == 0);
    }
    bool operator < (const int b) const
    {
        return s.size() == 1 ? (s[1] < b) : (s.size() ? 0 : b != 0);
    }
    friend bool operator > (const int b, const UnsignedBigInt& obj);

    UnsignedBigInt& operator -= (const UnsignedBigInt& b)
    {
        assert(*this >= b);
        size_t i;
        int r = 0;
        for(i = 0; i < b.s.size(); i++)
        {
            s[i] -= b.s[i] + r;
            if(s[i] < 0)
            {
                s[i] += BASE;
                r = 1;
            }
            else
                r = 0;
        }
        while(r)//肯定可以，不需要 i < s.size()
        {
            s[i]--;
            if(s[i] < 0)
                s[i] += BASE;
            else
                r = 0;
            i++;
        }
        return clean();
    }
    UnsignedBigInt operator - (const UnsignedBigInt& b)const
    {
        UnsignedBigInt ans = *this;;
        ans -= b;
        return ans;
    }

    UnsignedBigInt& operator -= (int b)
    {
        if(b)
        {
            assert(s.size() && b < BASE);
            size_t i = 0;
            do
            {
                s[i] -= b;
                if(s[i] < 0)
                {
                    s[i] += BASE;
                    b = 1;
                }
                else
                    b = 0;
                i++;
            }
            while(b);
        }
        return *this;
    }
    UnsignedBigInt operator - (int b) const
    {
        UnsignedBigInt ans = *this;
        return ans -= b;
    }

    UnsignedBigInt& operator /= (int num)
    {
        assert(0 < num && num < BASE);
        LL rem = 0;//remain
        for(int i = (int)s.size() - 1; i >= 0; i--)
        {
            rem = rem * BASE + s[i];
            s[i] = rem / num;
            rem %= num;
        }
        return clean();
    }
    UnsignedBigInt operator / (int num) const
    {
        UnsignedBigInt ans = *this;
        return ans /= num;
    }

    int operator % (int num) const
    {
        assert(0 < num && num < BASE);
        LL rem = 0;
        for(int i = (int)s.size()-1; i >= 0; i--)
        {
            rem = rem * BASE + s[i];
            rem %= num;
        }
        return rem;
    }

    UnsignedBigInt& operator <<= (int n)
    {
        int add = 0;
        for(size_t i = 0; i < s.size(); i++)
        {
            (s[i] <<= n) += add;
            add = s[i] / BASE;
            s[i] %= BASE;
        }
        if(add)
            s.push_back(add);
        return *this;
    }
    UnsignedBigInt operator << (int n) const
    {
        UnsignedBigInt ans = *this;
        return ans <<= n;
    }

    UnsignedBigInt& operator >>= (int n)
    {
        LL rem = 0;
        for(int i = (int)s.size() - 1; i >= 0; i--)
        {
            rem *= BASE;
            rem += s[i];
            s[i] = rem >> n;
            rem %= pow2[n];
        }
        return clean();
    }
    UnsignedBigInt operator >> (int n)
    {
        UnsignedBigInt ans = *this;
        return ans >>= n;
    }

    //UnsignedBigInt& operator <<= (int n)
    //UnsignedBigInt& operator >>= (int n)
    //You should make sure that ans == 0 before invoke the function.
    //you should clean ans before you use it after you invoking this function
    void div_mod(const UnsignedBigInt& b, UnsignedBigInt& ans, UnsignedBigInt& rem) const
    {
        assert(!b.s.empty());
        UnsignedBigInt expNum(1);
        UnsignedBigInt divisor(b);

        rem = *this;
        while(divisor <= rem)
        {
            divisor <<= 1;
            expNum <<= 1;
        }
        divisor >>= 1;
        expNum >>= 1;
        while(!expNum.s.empty())
        {
            if(rem >= divisor)
            {
                rem -= divisor;
                ans += expNum;
            }
            divisor >>= 1;
            expNum >>= 1;
        }
    }
    UnsignedBigInt operator / (const UnsignedBigInt& b)const
    {
        UnsignedBigInt ans;
        UnsignedBigInt rem;//remain = 0
        div_mod(b, ans, rem);
        return ans.clean();
    }
    UnsignedBigInt& operator /= (const UnsignedBigInt& b)
    {
        return *this = *this / b;
    }

    //void div_mod(const UnsignedBigInt& b, UnsignedBigInt& ans, UnsignedBigInt& rem)
    UnsignedBigInt operator % (const UnsignedBigInt& b) const
    {
        UnsignedBigInt ans;
        UnsignedBigInt rem;//remain = 0
        div_mod(b, ans, rem);
        return rem;
    }
    UnsignedBigInt& operator %= (const UnsignedBigInt& b)
    {
        return *this = *this % b;
    }

    inline UnsignedBigInt Move_right_BASE(int n) const
    {
        return n >= (int)s.size() ? UnsignedBigInt() : UnsignedBigInt(vector<int>(s.begin() + n, s.end()));
    }

    //n < WIDTH
    UnsignedBigInt& MoveEq_right_small_10(int n)
    {
        LL rem = 0;
        for(int i = (int)s.size() - 1; i >= 0; i--)
        {
            rem *= BASE;
            rem += s[i];
            s[i] = rem / tens[n];
            rem %= tens[n];
        }
        return clean();
    }
    inline UnsignedBigInt Move_right_10(int n) const
    {
        return Move_right_BASE(n / WIDTH).MoveEq_right_small_10(n % WIDTH);
    }

    inline UnsignedBigInt Move_left_BASE(int n)
    {
        UnsignedBigInt ans = *this;
        ans.s.insert(ans.s.begin(), n, 0);
        return ans;
    }

    inline UnsignedBigInt BigTens(int n) const
    {
        UnsignedBigInt ans;
        ans.s.resize(n / WIDTH + 1, 0);
        ans.s[n / WIDTH] = tens[n % WIDTH];
        return ans;
    }

    UnsignedBigInt operator ^ (int m) const
    {
        if(0 == m)
            return UnsignedBigInt(1);
        assert(m > 0);
        UnsignedBigInt ans = *this;
        m--;
        while(m--)
            ans *= *this;
        return ans;
    }

    //Independent
    //Number of digits in decimal
    size_t digit() const
    {
        size_t i;
        LL temp;
        if(s.size())
        {
            i = ((int)s.size()-1) * WIDTH;
            for(temp = s.back(); temp; temp /= 10)
                i++;
        }
        else
            i = 0;
        return i;
    }
};

UnsignedBigInt sqrt(const UnsignedBigInt& x, int m = 2);

ostream& operator << (ostream& out, const UnsignedBigInt& a);
istream& operator >> (istream& in, UnsignedBigInt& a);

#endif // UNSIGNEDBIGINT_H_INCLUDED
