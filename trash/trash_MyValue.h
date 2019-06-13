/*void Init_new(VAL_TYPE t) {
		type = t;
		switch (type) {
		case IS_INTEGER:
			val = new IntType;
			break;
		case IS_DOUBLE:
			val = new double;
			break;
		case IS_BOOL:
			val = new bool;
			break;
		case IS_FRACTION:
			val = new FRACTION;
			break;
		}
	}*/
	template<typename T>
	void Assign(VAL_TYPE t, const T& v) {
		type = t;
		switch (type) {
		case IS_INTEGER:
			val = new IntType(v);
			break;
		case IS_DOUBLE:
			val = new double(v);
			break;
		case IS_BOOL:
			val = new bool(v);
			break;
		case IS_FRACTION:
			val = new FRACTION(v);
			break;
		}
	}
