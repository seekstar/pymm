#include "MyDouble.h"

bool IsZero(double x) {
    return abs(x) < 1e-6;
}
bool NotZero(double x) {
    return !IsZero(x);
}

bool Equal(double lhs, double rhs) {
    return abs(lhs - rhs) < 1e-6;
}
bool NotEqual(double lhs, double rhs) {
    return !Equal(lhs, rhs);
}
