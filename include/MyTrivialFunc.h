#ifndef MYTRIVIALFUNC_CPP_INCLUDED
#define MYTRIVIALFUNC_CPP_INCLUDED

#include <vector>

using namespace std;

template<typename value_type>
void ExpandVector(vector<value_type>& s, size_t i) {
	if (s.size() <= i) {
		s.resize(i+1);
	}
}

#endif // MYTRIVIALFUNC_CPP_INCLUDED
