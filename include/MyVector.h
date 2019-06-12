#ifndef MYVECTOR_H_INCLUDED
#define MYVECTOR_H_INCLUDED

#include <algorithm>
#include <utility>

using namespace std;

template<typename value_type>
struct MyVector{
	value_type* base;
	size_t cap, tail;

	MyVector() {
		base = new value_type[2];
		tail = 0;
		cap = 2;
	}
	~MyVector() {
		delete base;
	}
	void HandleFull() {
		if (tail == cap) {
			cap += cap >> 1;
			auto tmp = base;
			base = new value_type[cap];
			for (size_t i = 0; i < tail; ++i) {
				swap(base[i], tmp[i]);
			}
			delete tmp;
		}
	}
	size_t size() {
		return tail;
	}
	void push_back(const value_type& val) {
		base[tail++] = val;
		HandleFull();
	}
	void pop_back(const value_type& val) {
		--tail;
	}
};

#endif // MYVECTOR_H_INCLUDED
