#include "MyAnalysis.h"

map<string, OPERATOR> operator_code;
map<OPERATOR, int>priority;
map<OPERATOR, int>numOfOperands;
map<OPERATOR, bool>associative;
set<char>symbols;
map<string, KEY_WORD> key_word_code;
map<string, SYS_FUNC> sys_func_code;

bool IsSymbol(char ch){
    return symbols.find(ch) != symbols.end();
}
bool IsBeginOfVarialbeOrFunc(char ch){
    return isalpha(ch) || ch == '_';
}
bool IsPartOfVariableOrFunc(char ch){
    return IsBeginOfVarialbeOrFunc(ch) || isdigit(ch);
}
bool IsAnOperator(const string& sth){
    return operator_code.find(sth) != operator_code.end();
}
bool IsSysFunc(const string& sth){
    return sys_func_code.find(sth) != sys_func_code.end();
}
bool IsKeyWord(const string& sth) {
	return key_word_code.find(sth) != key_word_code.end();
}

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

bool Parsing_dfs(NODE*& operand, vector<StrExpr>::iterator& now, ostream& info) {
    stack<NODE*>operator_sta;
       
    ERROR_TYPE error_type = NO_ERROR;

    bool finish = false;
    operand = NULL;
    for (; !finish && NO_ERROR == error_type && now->type != IS_NIL; ++now) {
        switch (now->type) {
        case IS_CONSTANT:
            Parsing_IS_CONSTANT(operand, error_type, now, finish);
            break;
        case IS_VARIABLE:
            operand = new NODE(IS_VARIABLE);
            operand->variable() = now->name;
            break;
        case IS_OPERATOR:
            Parsing_IS_OPERATOR(operand, error_type, now, operator_sta, finish, info);
 			break;
		default:
		    ErrMsg(info, "No such a node type ", now->type);
			break;
        }
    }
    PopAllOperators(operator_sta, operand);

    switch (error_type) {
    case NO_OPERAND_BEFORE:
		info << "No operand before the operator " << now->name << '\n';
        break;
    case UNEXPECTED_OPERAND:
		info << "Unexpected operand " << now->name << '\n';
        break;
    default:
        //skip
        break;
    }

    return error_type == NO_ERROR ? SUCCEED : FAIL;
}

void Parsing_IS_CONSTANT(NODE*& operand, ERROR_TYPE& error_type, const vector<StrExpr>::iterator& now, bool& finish) {
	if (operand != NULL) {
        error_type = UNEXPECTED_OPERAND;
		return;
    }
    operand = new NODE(IS_CONSTANT);
    operand->constant().val = new VARIABLE;
    GetConst(*operand->constant().val, now->name.c_str());
    /*#if DEBUG
    cerr << "operand: " << *(IntType*)operand->constant().val->val << endl;
    #endif*/ // DEBUG
}

void Parsing_IS_OPERATOR(NODE*& operand, ERROR_TYPE& error_type, vector<StrExpr>::iterator& now, stack<NODE*>& operator_sta, bool& finish, ostream& info) {
    OPERATOR op = NIL;
    NODE* tmp = NULL;
	if (now->name == "-") {
        if (operand) {     //There are operands before
            op = SUB;
        } else {
            op = MINUS;
        }
    } else {
        op = operator_code[now->name];
    }
    /*#if DEBUG
    cerr << "operator code = " << op << endl;
    #endif*/
    switch (numOfOperands[op]) {
    case 0:
        switch (op) {
        case LEFT_PARENTHESIS:
            Parsing_dfs(operand, ++now, info);
            --now;  //because the for loop will increase it soon.
            break;
        case RIGHT_PARENTHESIS:
            PopAllOperators(operator_sta, operand);
            finish = true;
            break;
        default:
            ErrMsg(info, "Unexpected operator code ", op);
            break;
        }
        break;
    case 1:
        switch (op) {
        case MINUS:
            tmp = new NODE(IS_OPERATOR);
            tmp->op() = MINUS;
            operator_sta.push(tmp);
            break;
        default:
            ErrMsg(info, "Unexpected operator code ", op);
            break;
        }
        break;
    case 2:
        if (NULL == operand) {
            error_type = NO_OPERAND_BEFORE;
            finish = true;
            break;
        }
        while (!operator_sta.empty()) {
            assert(operator_sta.top());
            OPERATOR top_op = operator_sta.top()->op();
            //The smaller, the more prior
            if(priority[op] < priority[top_op] ||
               (priority[op] == priority[top_op] && associative[op] == RIGHT_ASSOCIATIVE))
            {
                break;
            } else {
                operator_sta.top()->child[numOfOperands[top_op]-1] = operand;
                operand = operator_sta.top();
                operator_sta.pop();
            }
        }
        operator_sta.push(OperandBecomeLeftChild(op, operand));
        break;
    case 3:
        break;
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
