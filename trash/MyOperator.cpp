#include "MyOperator.h"

CONST_OR_VARIABLE IntType_IntType_Op(IntType& lhs, IntType& rhs, OPERATOR op)
{
    static CONST_OR_VARIABLE ans;
    switch (op) {
    case ADD:
    	ans.type = IS_INTEGER;
    	ans.val = new IntType;
        *ans.val = lhs + rhs;
        break;
    case SUB:
    	ans.type = IS_INTEGER;
    	ans.val = new IntType;
        *ans.val = lhs - rhs;
        break;
    case MUL:
        ans.type = IS_INTEGER;
    	ans.val = new IntType;
        *ans.val = lhs * rhs;
        break;
    case FLOOR_DIV:
        ans.type = IS_DOUBLE;
    	ans.val = new double;
        *ans.val = (double)lhs / (double)rhs;
        break;
	case ADD_EQ:

    }
    return ans;
}

double IntType_double_Op(IntType& lhs, double& rhs, OPERATOR op)
{
    static CONST_OR_VARIABLE ans;
}

double DoubleOp(double lhs, double rhs, OPERATOR op)
{
    double ans;
    switch (op){
    case ADD:
        ans = lhs + rhs;
        break;
    case SUB:
        ans = lhs - rhs;
        break;
    case MUL:
        ans = lhs * rhs;
        break;
    case FLOOR_DIV:
        ans = lhs / rhs;
        break;
    }
    return ans;
}

