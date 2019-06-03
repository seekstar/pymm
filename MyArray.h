#ifndef MYARRAY_H_INCLUDED
#define MYARRAY_H_INCLUDED

#include <vector>
#include <assert.h>
#include <ostream>

using namespace std;

template<typename value_type>
struct MyArray {
	vector<size_t> len;	//the length of corresponding dimensions. len[0] is the length of the lowest dimension
	vector<value_type> base;

	MyArray() {}
	MyArray(size_t n) {
		resize(n);
	}
	MyArray(size_t n, size_t m) {
		resize(n, m);
	}
	MyArray(const vector<size_t>& _len) {
		resize(_len);
	}

	void resize(size_t n) {
		len.resize(1);
		len[0] = n;
		ResizeBase();
	}
	void resize(size_t n, size_t m) {
		len.resize(2);
		len[0] = m;
		len[1] = n;
		ResizeBase();
	}
	void resize(const vector<size_t>& _len) {
		len = _len;
		ResizeBase();
	}
	void ResizeBase() {
		size_t siz = 1;
		for (size_t i : len) {
			siz *= i;
		}
		base.resize(siz);
	}
	size_t size() {
		return base.size();
	}

	value_type& operator () (size_t i) {
		assert(1 == len.size());
		return base[i];
	}
	const value_type& operator () (size_t i) const {
		assert(1 == len.size());
		return base[i];
	}
	value_type& operator () (size_t i, size_t j) {
		assert(2 == len.size());
		return base[i*len[0] + j];
	}
	const value_type& operator () (size_t i, size_t j) const {
		assert(2 == len.size());
		return base[i*len[0] + j];
	}

	size_t position(const vector<size_t>& pos) const {
		size_t lower_mul = 1, ans = 0;
		for (size_t i = 0; i < pos.size(); ++i) {
			ans += pos[i] * lower_mul;
			lower_mul *= len[i];
		}
		return ans;
	}
	value_type& operator () (const vector<size_t>& pos) {
		return base[position(pos)];
	}
	const value_type& operator () (const vector<size_t>& pos) const {
		return base[position(pos)];
	}
};

//Only print [0, n) dimensions, the position of higher dimensions are given by now.
template<typename value_type>
void PrintArray(ostream& out, const MyArray<value_type>& arr, vector<size_t>& now, int n) {
	if (0 == n) {
		out << arr(now);
	} else {
		out << '{';
		for (now[n-1] = 0; now[n-1] < arr.len[n-1]; ++now[n-1]) {
			PrintArray(out, arr, now, n-1);
			if (now[n-1] < arr.len[n-1]) {
				out << ',';
			}
		}
		out << '}';
	}
}

template<typename value_type>
ostream& operator << (ostream& out, const MyArray<value_type>& arr) {
	vector<size_t> now;
	now.resize(arr.len.size());
	for (size_t i = 0; i < now.size(); ++i) {
		PrintArray(out, arr, now, now.size());
	}
	return out;
}


#endif // MYARRAY_H_INCLUDED
