#ifndef MYARRAY_H_INCLUDED
#define MYARRAY_H_INCLUDED

#include <vector>
#include <assert.h>
#include <ostream>

#include "MyTrivialFunc.h"

using namespace std;

size_t Position(const vector<size_t>& len, const vector<size_t>& pos);
size_t CalcSize(const vector<size_t>& len);

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
		base.resize(CalcSize(len));
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
	/*value_type& operator () (size_t i, size_t j) {
		assert(2 == len.size());
		return base[i*len[0] + j];
	}
	const value_type& operator () (size_t i, size_t j) const {
		assert(2 == len.size());
		return base[i*len[0] + j];
	}*/

	//After return, newLen will become the old len
	void Expand(const vector<size_t>& newLen) {
		vector<value_type> tmp = base;
		base.resize(CalcSize(newLen));
		CopyArray(base, newLen, tmp, len);
		len = newLen;
	}
	void HandleOutOfBounds(const vector<size_t>& pos) {
		bool needExpand = false;
		vector<size_t> newLen = len;
		if (newLen.size() < pos.size())
			newLen.resize(pos.size());
		for (size_t i = 0; i < pos.size(); ++i) {
			if (pos[i] >= newLen[i]) {
				needExpand = true;
				newLen[i] = pos[i] + 1;
			}
		}
		if (needExpand) {
			Expand(newLen);
		}
	}
	size_t position(const vector<size_t>& pos) {
		HandleOutOfBounds(pos);
		return Position(len, pos);
	}
	//Do not handle out of bound
	size_t position(const vector<size_t>& pos) const {
		return Position(len, pos);
	}
	value_type& operator () (const vector<size_t>& pos) {
		return base[position(pos)];
	}
	const value_type& operator () (const vector<size_t>& pos) const {
		return base[position(pos)];
	}

	bool OutOfBound(const vector<size_t>& pos) const {
		for (size_t i = 0; i < pos.size(); ++i) {
			if (pos[i] >= len[i]) {
				return true;
			}
		}
		return false;
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

//Only copy [0,n) dimensions, the position of higher dimensions are given by now.
/*template<typename value_type>
void CopyArray(MyArray<value_type>& arr, const vector<value_type>& from, const vector<size_t>& from_len, vector<size_t>& now, int n) {
	if (0 == n) {
		arr(now) = from_len[position(from_len, now)];
	} else {
		for (now[n-1] = 0; now[n-1] < arr.len[n-1]; ++now[n-1]) {
			CopyArray(arr, now, n-1);
		}
	}
}*/

template<typename value_type>
void CopyArray(vector<value_type>& to, const vector<size_t>& to_len, const vector<value_type>& from, const vector<size_t>& from_len, vector<size_t>& now, int n) {
	if (0 == n) {
		int to_index = Position(to_len, now);
		ExpandVector(to, to_index);
		to[to_index] = from[Position(from_len, now)];
	} else {
		for (now[n-1] = 0; now[n-1] < from_len[n-1]; ++now[n-1]) {
			CopyArray(to, to_len, from, from_len, now, n-1);
		}
	}
}

template<typename value_type>
void CopyArray(vector<value_type>& to, const vector<size_t>& to_len, const vector<value_type>& from, const vector<size_t>& from_len) {
	vector<size_t>now(to_len.size(), 0);
	CopyArray(to, to_len, from, from_len, now, to_len.size()-1);
}

#endif // MYARRAY_H_INCLUDED
