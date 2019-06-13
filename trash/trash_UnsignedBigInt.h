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
