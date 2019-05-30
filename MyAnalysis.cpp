#include "MyAnalysis.h"

map<string, OPERATOR> operator_code;
map<OPERATOR, int>priority;
map<OPERATOR, int>numOfOperands;
map<OPERATOR, bool>associative;
set<char>symbols;
map<string, KEY_WORD> key_word_code;
map<string, SYS_FUNC> sys_func_code;

string NodeType2string(NodeType type)
{
    string ans;
    switch (type) {
    case IS_CONSTANT:
        ans = "IS_CONSTANT";
        break;
    case IS_VARIABLE:
        ans =  "IS_VARIABLE";
        break;
    case IS_OPERATOR:
        ans =  "IS_OPERATOR";
        break;
    case IS_KEY_WORD:
        ans =  "IS_KEY_WORD";
        break;
    case IS_STRUCTURE:
        ans =  "IS_STRUCTURE";
        break;
    case IS_SYS_FUNC:
        ans =  "IS_SYS_FUNC";
        break;
    case IS_USER_FUNC:
        ans =  "IS_USER_FUNC";
        break;
    case IS_NIL:
        ans =  "IS_NIL";
        break;
    default:
        ans =  "Error!";
        break;
    }
    return ans;
}

const char* OperatorName(OPERATOR op)
{
    switch (op) {
    case NIL:
        return "/\\";
    case ASSIGN:
        return "=";
    case ADD:
        return "+";
    case ADD_EQ:
        return "+=";
    case SUB:
        return "-";
    case SUB_EQ:
        return "-=";
    case MUL:
        return "*";
    case MUL_EQ:
        return "*=";
    case DIV:
        return "/";
    case DIV_EQ:
        return "/=";
    case MODULUS:
        return "%";
    case MODULUS_EQ:
        return "%=";
    case MINUS:
        return "-";
    case LESS:
        return "<";
    case LESS_EQ:
        return "<=";
    case GREATER:
        return ">";
    case GREATER_EQ:
        return ">=";
    case LEFT_PARENTHESIS:
        return "(";
    case RIGHT_PARENTHESIS:
        return ")";
    default:
        return "ERROR";
    }
}

const char* KeyWordName(KEY_WORD key_word)
{
    switch (key_word) {
    case IF_KEY:
        return "if";
    case WHILE_KEY:
        return "while";
    case FOR_KEY:
        return "for";
    case DO_KEY:
        return "do";
    }
    return "ERROR";
}

const char* StructureName(STRUCTURE structure)
{
    switch (structure) {
    case IF:
        return "if";
    case WHILE:
        return "while";
    case FOR:
        return "for";
    case DO_WHILE:
        return "do_while";
    }
    return "ERROR";
}

const char* SysFuncName(SYS_FUNC sys_func)
{
    switch (sys_func) {
    case SQRT:
        return "sqrt";
    case SIN:
        return "sin";
    case COS:
        return "cos";
    case ABS:
        return "abs";
    }
    return "ERROR";
}

NODE* OperandBecomeLeftChild(OPERATOR op, NODE*& operand) {
    NODE* ans = new NODE(IS_OPERATOR);
    ans->op() = op;
    ans->child[0] = operand;
    operand = NULL;
    return ans;
}

void AddOperandToLastChild(NODE* op, NODE*& operand) {
    op->child[numOfOperands[op->op()]-1] = operand;
    operand = op;
}

void PopAllOperators(stack<NODE*>& operator_sta, NODE*& operand) {
    while (!operator_sta.empty()) {
        assert(operator_sta.top());
        OPERATOR top_op = operator_sta.top()->op();
        operator_sta.top()->child[numOfOperands[top_op]-1] = operand;
        operand = operator_sta.top();
        operator_sta.pop();
    }
}

#if DEBUG
void PrintStrExpr(const vector<StrExpr> strExpr)
{
    for (auto expr : strExpr) {
        cout << NodeType2string(expr.type) << ' ' << expr.name << endl;
    }
    cout << endl;
}
#endif
