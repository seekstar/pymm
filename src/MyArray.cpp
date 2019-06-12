#include "MyArray.h"

//Do not consider out of bound
size_t Position(const vector<size_t>& len, const vector<size_t>& pos) {
	size_t lower_mul = 1, ans = 0;
	for (size_t i = 0; i < pos.size(); ++i) {
		ans += pos[i] * lower_mul;
		lower_mul *= len[i];
	}
	return ans;
}

size_t CalcSize(const vector<size_t>& len) {
	size_t ans = 1;
	for (size_t i : len)
		ans *= i;
	return ans;
}
