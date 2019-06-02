#include "MyAnalysis.h"

map<string, OPERATOR> operator_code;
map<OPERATOR, int>priority;
map<OPERATOR, int>numOfOperands;
map<OPERATOR, bool>associative;
set<char>symbols;
map<string, KEY_WORD> key_word_code;
map<string, SYS_FUNC> sys_func_code;
map<string, SEPARATOR> separator_code;

void Init(void){
    operator_code["="] = ASSIGN;
    priority[ASSIGN] = 14;
    numOfOperands[ASSIGN] = 2;
    associative[ASSIGN] = RIGHT_ASSOCIATIVE;

    operator_code["+"] = ADD;
    priority[ADD] = 4;
    numOfOperands[ADD] = 2;
    associative[ADD] = LEFT_ASSOCIATIVE;

    operator_code["-"] = SUB;
    priority[SUB] = 4;
    numOfOperands[SUB] = 2;
    associative[SUB] = LEFT_ASSOCIATIVE;

    operator_code["*"] = MUL;
    priority[MUL] = 3;
    numOfOperands[MUL] = 2;
    associative[MUL] = LEFT_ASSOCIATIVE;

    operator_code["/"] = DIV;
    priority[DIV] = 3;
    numOfOperands[DIV] = 2;
    associative[DIV] = LEFT_ASSOCIATIVE;

    operator_code["%"] = MODULUS;
    priority[MODULUS] = 3;
    numOfOperands[MODULUS] = 2;
    associative[MODULUS] = LEFT_ASSOCIATIVE;

    //operator_code["-"] = MINUS;
    priority[MINUS] = 2;
    numOfOperands[MINUS] = 1;
    associative[MINUS] = RIGHT_ASSOCIATIVE;

    operator_code["<"] = LESS;
    priority[LESS] = 6;
    numOfOperands[LESS] = 2;
    associative[LESS] = LEFT_ASSOCIATIVE;

    operator_code["<="] = LESS_EQ;
    priority[LESS_EQ] = 6;
    numOfOperands[LESS_EQ] = 2;
    associative[LESS_EQ] = LEFT_ASSOCIATIVE;

    operator_code[">"] = GREATER;
    priority[GREATER] = 6;
    numOfOperands[GREATER] = 2;
    associative[GREATER] = LEFT_ASSOCIATIVE;

    operator_code[">="] = GREATER_EQ;
    priority[GREATER_EQ] = 6;
    numOfOperands[GREATER_EQ] = 2;
    associative[GREATER_EQ] = LEFT_ASSOCIATIVE;

    operator_code["("] = LEFT_PARENTHESIS;
    priority[LEFT_PARENTHESIS] = 1;
    numOfOperands[LEFT_PARENTHESIS] = 0;
    associative[LEFT_PARENTHESIS] = LEFT_ASSOCIATIVE;

    operator_code[")"] = RIGHT_PARENTHESIS;
    priority[RIGHT_PARENTHESIS] = 1;
    numOfOperands[RIGHT_PARENTHESIS] = 0;
    associative[RIGHT_PARENTHESIS] = LEFT_ASSOCIATIVE;

    symbols.insert('=');
    symbols.insert('+');
    symbols.insert('-');
    symbols.insert('*');
    symbols.insert('/');
    symbols.insert('<');
    symbols.insert('>');
    symbols.insert('&');
    symbols.insert('^');
    symbols.insert('%');
    symbols.insert('!');
    symbols.insert('(');
    symbols.insert(')');
    symbols.insert('[');
    symbols.insert(']');
    symbols.insert('{');
    symbols.insert('}');
    symbols.insert('?');
    symbols.insert(':');
    symbols.insert(';');

    key_word_code["if"] = IF_KEY;
    key_word_code["while"] = WHILE_KEY;
    key_word_code["for"] = FOR_KEY;
    key_word_code["do"] = DO_KEY;

	separator_code["{"] = LEFT_BRACE;
	separator_code["}"] = RIGHT_BRACE;
	separator_code[";"] = SEMICOLON;
	separator_code["\n"] = ENTER;
}

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
bool IsSeparator(const string& sth) {
	return separator_code.find(sth) != separator_code.end();
}

const char* NodeTypeName(NodeType type) {
    switch (type) {
    case IS_CONSTANT:
        return "IS_CONSTANT";
    case IS_VARIABLE:
        return "IS_VARIABLE";
    case IS_OPERATOR:
        return "IS_OPERATOR";
    case IS_KEY_WORD:
        return "IS_KEY_WORD";
    case IS_STRUCTURE:
        return "IS_STRUCTURE";
    case IS_SYS_FUNC:
        return "IS_SYS_FUNC";
    case IS_USER_FUNC:
        return "IS_USER_FUNC";
    case IS_SEPARATOR:
        return"IS_SEPARATOR";
    case IS_NIL:
        return "IS_NIL";
    }
    return "Error!";
}
/*string NodeType2string(NodeType type)
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
    case IS_SEPARATOR:
        ans = "IS_SEPARATOR";
        break;
    case IS_NIL:
        ans =  "IS_NIL";
        break;
    default:
        ans =  "Error!";
        break;
    }
    return ans;
}*/

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
    case ELSE_KEY:
        return "else";
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

const char* SeparatorName(SEPARATOR separator) {
	switch (separator) {
	case LEFT_BRACE:
		return "{";
	case RIGHT_BRACE:
		return "}";
	case SEMICOLON:
		return ";";
	case ENTER:
		return "<CR>";
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

bool LexicalAnalysis(vector<StrExpr>& strExpr, const char* str, ostream& info) {
    string sth;
    bool status = SUCCEED;
    for (; *str;) {
        sth.clear();
		SkipSpaceExceptEnter(str);
		if (*str == '\n') {
			strExpr.push_back(StrExpr{IS_SEPARATOR, "\n"});
			++str;
			continue;
		} else if ('\0' == *str) {
			break;
		}
		//Is the beginning of a variable or function or key word.
        if(IsBeginOfVarialbeOrFunc(*str)){
            do{
                sth.push_back(*str++);
            }while(IsPartOfVariableOrFunc(*str));
            SkipSpaceExceptEnter(str);
            if('(' == *str){
               if (IsSysFunc(sth)) {
                    strExpr.push_back(StrExpr{IS_SYS_FUNC, sth});
               } else if (IsKeyWord(sth)) {
					strExpr.push_back(StrExpr{IS_KEY_WORD, sth});
			   } else {
                    strExpr.push_back(StrExpr{IS_USER_FUNC, sth});
               }
            }else{
                strExpr.push_back(StrExpr{IS_VARIABLE, sth});
            }
        }else if(IsSymbol(*str)){
            //Will cause some problems, such as misunderstand expressions like "pair<pair<int, int>>" and interpret ">>" as right shift.
            do{
                sth.push_back(*str++);
            }while(IsAnOperator(sth));
            sth.pop_back();
            --str;
            if (!sth.empty()) {
            	strExpr.push_back(StrExpr{IS_OPERATOR, sth});
			} else {
				do {
					sth.push_back(*str++);
				} while (IsSeparator(sth));
				sth.pop_back();
				--str;
				if (sth.empty()) {
					info << "Unknown chracter " << *str << '\n';
       	        	status = FAIL;
                	break;
				}
				strExpr.push_back(StrExpr{IS_SEPARATOR, sth});
            }
        }else if(IsBeginningOfConst(*str)){
            GetConst(sth, str);
            strExpr.push_back(StrExpr{IS_CONSTANT, sth});
        }else if(!isspace(*str)){
			info << "Unknown character \"" << *str << "\"!\n";
            status = FAIL;
            break;
        }
    }
    strExpr.push_back(StrExpr{IS_NIL, ""});

    return status;
}

bool Parsing(NODE*& root, vector<StrExpr>::iterator& now, ostream& info) {
    FAIL_THEN_RETURN(Parsing_dfs(root, now, info));
    NODE* operand = root;
    while (operand) {
        FAIL_THEN_RETURN(Parsing_dfs(operand->sibling, now, info));
        operand = operand->sibling;
    }
    return SUCCEED;
}
bool Parsing_dfs(NODE*& operand, vector<StrExpr>::iterator& now, ostream& info) {
    stack<NODE*>operator_sta;
	bool need_output = false;

    ERROR_TYPE error_type = NO_ERROR;

    //bool finish = false;
	bool needReturn = false;
    operand = NULL;
    for (; !needReturn && NO_ERROR == error_type && now->type != IS_NIL; ++now) {
        switch (now->type) {
        case IS_CONSTANT:
            Parsing_IS_CONSTANT(operand, error_type, now);
            break;
        case IS_VARIABLE:
            operand = new NODE(IS_VARIABLE);
            operand->variable() = now->name;
            break;
        case IS_OPERATOR:
            Parsing_IS_OPERATOR(operand, error_type, now, operator_sta, needReturn, info);
 			break;
		case IS_KEY_WORD:
			break;
		case IS_SEPARATOR:
			Parsing_IS_SEPARATOR(error_type, now->name, needReturn, need_output);  //finish
			break;
		default:
		    ErrMsg(info, "No such a node type ", now->type);
			break;
        }
    }
    PopAllOperators(operator_sta, operand);

    if (NO_ERROR != error_type) {
        --now;
        switch (error_type) {
        case NO_OPERAND_BEFORE:
            info << "No operand before the operator " << now->name << '\n';
            break;
        case UNEXPECTED_OPERAND:
            info << "Unexpected operand " << now->name << '\n';
            break;
        case UNEXPECTED_LEFT_BRACE:
            info << "Unexpected '{'\n";
            break;
        case UNEXPECTED_ELSE_KEY:
            info << "Unexpected else key\n";
            break;
        case UNRECOGNIZED_KEY:
            info << "Unrecognized key " << now->name << '\n';
            break;
        default:
            //skip
            break;
        }
    }

    if (operand && need_output) {
        operand->output = true;
    }
    return error_type == NO_ERROR ? SUCCEED : FAIL;
}

void Parsing_IS_CONSTANT(NODE*& operand, ERROR_TYPE& error_type, const vector<StrExpr>::iterator& now) {
	if (operand != NULL) {
        error_type = UNEXPECTED_OPERAND;
		return;
    }
    operand = new NODE(IS_CONSTANT);
    operand->constant().val = new VARIABLE;
    GetConst(*operand->constant().val, now->name.c_str());
}

bool Parsing_IS_OPERATOR(NODE*& operand, ERROR_TYPE& error_type, vector<StrExpr>::iterator& now, stack<NODE*>& operator_sta, bool& needReturn, ostream& info) {
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

    switch (numOfOperands[op]) {
    case 0:
        switch (op) {
        case LEFT_PARENTHESIS:
            FAIL_THEN_RETURN(Parsing_dfs(operand, ++now, info));
            --now;  //because the for loop will increase it soon.
            break;
        case RIGHT_PARENTHESIS:
            PopAllOperators(operator_sta, operand);
            needReturn = true;
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
            needReturn = true;
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
    return SUCCEED;
}

bool Parsing_IS_KEY_WORD(NODE*& operand, ERROR_TYPE& error_type, vector<StrExpr>::iterator& now, stack<NODE*>& operator_sta, ostream& info) {
	operand->Init(IS_STRUCTURE);
	KEY_WORD code = key_word_code[now->name];
	switch (code) {
	case IF_KEY:
        operand->structure() = IF;
		++now;	//skip '('
		Parsing_dfs(operand->child[0], now, info);
		if (now->name == "{")
			++now;	//skip '{'
		FAIL_THEN_RETURN(Parsing_dfs(operand->child[1], now, info));
		if (now->type == IS_SEPARATOR && key_word_code[now->name] == ELSE_KEY) {
			++now;	//skip else
			if (now->name == "{")
				++now;	//skip '{'
			Parsing_dfs(operand->child[1], now, info);
		}
		break;
	case ELSE_KEY:
        error_type = UNEXPECTED_ELSE_KEY;
        break;
    default:
        error_type = UNRECOGNIZED_KEY;
        break;
	}
	return SUCCEED;
}

void Parsing_IS_SEPARATOR(ERROR_TYPE& error_type, const string& name, bool& needReturn, bool& need_output) {
	switch (separator_code[name]) {
	case LEFT_BRACE:
		error_type = UNEXPECTED_LEFT_BRACE;
		break;
	case RIGHT_BRACE:
		//finish = true;
		needReturn = true;
		break;
	case SEMICOLON:
		needReturn = true;
		break;
	case ENTER:
		//finish = true;
		needReturn = true;
		need_output = true;
		break;
	}
}

bool CalcByTree(const NODE* root, unordered_map<string, VARIABLE>& variable_table, ostream& info) {
    while (root) {
        CONST_OR_VARIABLE ans;
        FAIL_THEN_RETURN(CalcByTree(ans, root, false, variable_table, info));
        if (root->output) {
            info << ToString(*ans.val) << endl;
        }
        ans.del();
        root = root->sibling;
    }
    return SUCCEED;
}
bool CalcByTree(CONST_OR_VARIABLE& ans, const NODE* root, bool create_variable, unordered_map<string, VARIABLE>& variable_table, ostream& info) {
    bool result = SUCCEED;
	unordered_map<string, VARIABLE>::iterator it;

    switch (root->type) {
    case IS_CONSTANT:
        ans = root->constant();
		break;
    case IS_VARIABLE:
		ans.Init(true, true);
		it = variable_table.find(root->variable());
		if (it == variable_table.end()) {
			if (create_variable) {
				ans.val = &variable_table[root->variable()];
			} else {
				info << "No such a variable " << root->variable() << '\n';
				result = FAIL;
			}
		} else {
			ans.val = &it->second;
		}
        break;
    case IS_OPERATOR:
		CalcByTree_IS_OPERATOR(root, ans, variable_table, info);
        break;
    default:
        ErrMsg(info, "No such an operator ", root->op());
        break;
    }
    return result;
}

bool CalcByTree_IS_OPERATOR(const NODE* root, CONST_OR_VARIABLE& ans, unordered_map<string, VARIABLE>& variable_table, ostream& info) {
    CONST_OR_VARIABLE ans1;
    CONST_OR_VARIABLE ans2;
	switch (root->op()) {
    case ASSIGN:
        FAIL_THEN_RETURN(CalcByTree(ans, root->child[0], true, variable_table, info));
        FAIL_THEN_RETURN(CalcByTree(ans2, root->child[1], false, variable_table, info));
        FAIL_THEN_RETURN(ans.Copy(ans2, info));
        break;
    case ADD:
        FAIL_THEN_RETURN(CalcByTree(ans1, root->child[0], false, variable_table, info));
        FAIL_THEN_RETURN(CalcByTree(ans2, root->child[1], false, variable_table, info));
        ans = ans1 + ans2;
        break;
    case SUB:
        FAIL_THEN_RETURN(CalcByTree(ans1, root->child[0], false, variable_table, info));
        FAIL_THEN_RETURN(CalcByTree(ans2, root->child[1], false, variable_table, info));
        ans = ans1 - ans2;
        break;
    case MUL:
        FAIL_THEN_RETURN(CalcByTree(ans1, root->child[0], false, variable_table, info));
        FAIL_THEN_RETURN(CalcByTree(ans2, root->child[1], false, variable_table, info));
        ans = ans1 * ans2;
        break;
    case DIV:
        FAIL_THEN_RETURN(CalcByTree(ans1, root->child[0], false, variable_table, info));
        FAIL_THEN_RETURN(CalcByTree(ans2, root->child[1], false, variable_table, info));
        ans = ans1 / ans2;
        break;
    default:
        ErrMsg(info, "No such an operator ", root->op());
        break;
    }
    ans1.del();
    ans2.del();
	return SUCCEED;
}

bool UpdateBraces(stack<char>& braces, const char*& str) {
    for (; *str; ++str) {
        switch (*str) {
        case '(':
            braces.push('(');
            break;
        case ')':
            if (braces.top() == '(')
                braces.pop();
            else
                return FAIL;
            break;
        case '[':
            braces.push('[');
            break;
        case ']':
            if (braces.top() == '[')
                braces.pop();
            else
                return FAIL;
            break;
        case '{':
            braces.push('{');
            break;
        case '}':
            if (braces.top() == '{')
                braces.pop();
            else
                return FAIL;
            break;
        }
    }
    return SUCCEED;
}

void PrintStrExpr(const vector<StrExpr> strExpr)
{
    for (auto expr : strExpr) {
        cout << NodeTypeName(expr.type) << ' ' << expr.name << endl;
    }
    cout << endl;
}
