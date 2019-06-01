#ifndef MYPYMINUSMINUS_H_INCLUDED
#define MYPYMINUSMINUS_H_INCLUDED

#include <vector>
#include <map>
#include <set>
#include <unordered_map>
#include <stack>

#include "MyString.h"
#include "MyAnalysis.h"
#include "MyFlags.h"
#include "MyError.h"
//#include "MyStringSTL.h"

#if DEBUG
#include "PrintTree.h"
#endif // DEBUG

struct PYMM{
    unordered_map<string, VARIABLE> variable_table;

    PYMM(){
        Init();
    }
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

        key_word_code["if"] = IF_KEY;
        key_word_code["while"] = WHILE_KEY;
        key_word_code["for"] = FOR_KEY;
        key_word_code["do"] = DO_KEY;
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
    bool Input(const char* str, ostream& info){
        vector<StrExpr> strExpr;
        NODE* root = NULL;
        CONST_OR_VARIABLE ans;

        if(IsEmptyString(str))
            return SUCCEED;

        FAIL_THEN_RETURN(LexicalAnalysis(strExpr, str, info));

        #if DEBUG
        PrintStrExpr(strExpr);
        #endif // DEBUG

        auto now = strExpr.begin();
        FAIL_THEN_RETURN(Parsing_dfs(root, now, info));

#if DEBUG
        PrintTree(cout, root);
#endif

        FAIL_THEN_RETURN(CalcByTree(ans, root, false, info));

        info << ToString(*ans.val);

        return SUCCEED;
    }
    bool LexicalAnalysis(vector<StrExpr>& strExpr, const char* str, ostream& info) {
        string sth;
        bool status = SUCCEED;
        for (; *str;) {
            sth.clear();
            SkipSpace(str);
			//Is the beginning of a variable or function or key word.
            if(IsBeginOfVarialbeOrFunc(*str)){
                do{
                    sth.push_back(*str++);
                }while(IsPartOfVariableOrFunc(*str));
                SkipSpace(str);
                if('(' == *str){
                    if(IsSysFunc(sth)){
                        strExpr.push_back(StrExpr{IS_SYS_FUNC, sth});
                   }else{
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
                if (sth.empty()) {
					info << "Unknown chracter " << *str << '\n';
                    status = FAIL;
                    break;
                }
                strExpr.push_back(StrExpr{IS_OPERATOR, sth});
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

    bool Parsing_dfs(NODE*& operand, vector<StrExpr>::iterator& now, ostream& info) {
        stack<NODE*>operator_sta;

        enum ERROR_TYPE
        {
            NO_ERROR,
            NO_OPERAND_BEFORE,
            UNEXPECTED_OPERAND,
        };
        ERROR_TYPE error_type = NO_ERROR;

        OPERATOR op = NIL;
        bool finish = false;
        operand = NULL;
        for (; !finish && NO_ERROR == error_type && now->type != IS_NIL; ++now) {
            decltype(variable_table.begin()) it;
            NODE* tmp = NULL;
            switch (now->type) {
            case IS_CONSTANT:
                if (operand != NULL) {
                    error_type = UNEXPECTED_OPERAND;
                    break;
                }
                operand = new NODE(IS_CONSTANT);
                operand->constant().val = new VARIABLE;
                GetConst(*operand->constant().val, now->name.c_str());
                /*#if DEBUG
                cerr << "operand: " << *(IntType*)operand->constant().val->val << endl;
                #endif*/ // DEBUG
                break;
            case IS_VARIABLE:
                operand = new NODE(IS_VARIABLE);
                operand->variable() = now->name;
                break;
            case IS_OPERATOR:
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
                break;
            default:
                ErrMsg(info, "No such a node type ", now->type);
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

    bool CalcByTree(CONST_OR_VARIABLE& ans, const NODE* root, bool create_variable, ostream& info)
    {
        bool result = SUCCEED;
		unordered_map<string, VARIABLE>::iterator it;

        CONST_OR_VARIABLE ans1;
        CONST_OR_VARIABLE ans2;
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
            switch (root->op()) {
            case ASSIGN:
                FAIL_THEN_RETURN(CalcByTree(ans, root->child[0], true, info));
                FAIL_THEN_RETURN(CalcByTree(ans2, root->child[1], false, info));
                FAIL_THEN_RETURN(ans.Copy(ans2, info));
                #if DEBUG
                cerr << "ans = " << *(IntType*)ans.val->val << endl;
                cerr << "ans2 = " << *(IntType*)ans2.val->val << endl;
                #endif // DEBUG
                break;
            case ADD:
                FAIL_THEN_RETURN(CalcByTree(ans1, root->child[0], false, info));
                #if DEBUG
                cerr << "ans1 = " << *(IntType*)ans1.val->val << endl;
                #endif // DEBUG
                FAIL_THEN_RETURN(CalcByTree(ans2, root->child[1], false, info));
                #if DEBUG
                cerr << "ans2 = " << *(IntType*)ans2.val->val << endl;
                cerr << endl;
                #endif // DEBUG
                ans = ans1 + ans2;
                #if DEBUG
                cerr << *(IntType*)ans.val->val << endl;
                #endif // DEBUG
                break;
            case SUB:
                FAIL_THEN_RETURN(CalcByTree(ans1, root->child[0], false, info));
                FAIL_THEN_RETURN(CalcByTree(ans2, root->child[1], false, info));
                ans = ans1 - ans2;
                break;
            case MUL:
                FAIL_THEN_RETURN(CalcByTree(ans1, root->child[0], false, info));
                FAIL_THEN_RETURN(CalcByTree(ans2, root->child[1], false, info));
                ans = ans1 * ans2;
                break;
            case DIV:
                FAIL_THEN_RETURN(CalcByTree(ans1, root->child[0], false, info));
                FAIL_THEN_RETURN(CalcByTree(ans2, root->child[1], false, info));
                ans = ans1 / ans2;
                break;
            default:
                ErrMsg(info, "No such an operator ", root->op());
                break;
            }
            break;
        default:
            ErrMsg(info, "No such an operator ", root->op());
            break;
        }
        ans1.del();
        ans2.del();
        return result;
    }
};

#endif // MYPYMINUSMINUS_H_INCLUDED
