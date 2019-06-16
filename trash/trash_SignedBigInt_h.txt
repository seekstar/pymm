SignedBigInt& operator /= (int num)
	{
	    assert(num);
	    if(num < 0)
        {
            is_minus = !is_minus;
            num = -num;
        }
        absVal /= num;
        return *this;
	}
	SignedBigInt operator / (int num) const
	{
	    SignedBigInt ans = *this;
	    return ans /= num;
	}

