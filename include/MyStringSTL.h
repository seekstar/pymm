#ifndef STRING_H_INCLUDED
#define STRING_H_INCLUDED

#include <ostream>

#include "MyVector.h"

using namespace std;
/*
struct MyString : public MyVector<char> {
	MyString() {
		this->base[0] = 0;
	}
	MyString(const char* str) {
		append(str);
	}
	void push_back(char ch) {
		MyVector<char>::push_back(ch);
		base[tail] = 0;
	}
	void pop_back() {
		--tail;
	}
	const char* c_str() const {
		return base;
	}

	MyString& append(char ch) {
		push_back(ch);
		return *this;
	}
	MyString& append(const char* str) {
		for (; *str; ++str) {
			MyVector<char>::push_back(*str);
		}
		base[tail] = 0;
		return *this;
	}
	MyString& append(const MyString& b) {
		return append(b.base);
	}
	MyString& append(size_t cnt, char ch) {
		while (cnt--) {
			MyVector<char>::push_back(ch);
		}
		base[tail] = 0;
		return *this;
	}

	MyString& operator += (const char* str) {
		return append(str);
	}
	MyString& operator += (const MyString& b) {
		return append(b);
	}
	MyString& operator += (char ch) {
		return append(ch);
	}
};

ostream& operator << (ostream& out, const MyString& rhs);*/

typedef string MyString;

#endif // STRING_H_INCLUDED
