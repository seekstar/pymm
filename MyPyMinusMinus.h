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
    bool Input(const char* str, string& information){
        vector<StrExpr> strExpr;
        NODE* root = NULL;
        CONST_OR_VARIABLE ans;

        if(IsEmptyString(str))
            return SUCCEED;

        if (FAIL == LexicalAnalysis(strExpr, str, information))
            return FAIL;

        #if DEBUG
        PrintStrExpr(strExpr);
        #endif // DEBUG

        if (FAIL == Parsing_dfs(root, strExpr.begin(), information))
            return FAIL;

#if DEBUG
        PrintTree(cout, root);
#endif

        if (FAIL == CalcByTree(ans, root, information))
            return FAIL;
        information += ToString(*ans.val);
        return SUCCEED;
    }
    bool LexicalAnalysis(vector<StrExpr>& strExpr, const char* str, string& information) {
        string sth;
        bool status = SUCCEED;
        for (; *str;) {
            sth.clear();
            SkipSpace(str);
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
                    ((information += "Unknown character ") += *str) += " \n";
                    status = FAIL;
                    break;
                }
                strExpr.push_back(StrExpr{IS_OPERATOR, sth});
            }else if(IsBeginningOfConst(*str)){
                GetConst(sth, str);
                strExpr.push_back(StrExpr{IS_CONSTANT, sth});
            }else if(!isspace(*str)){
                (((information += "Unknown character \"") += *str) += "\"!\n");
                status = FAIL;
                break;
            }
        }
        strExpr.push_back(StrExpr{IS_NIL, ""});

        return status;
    }

    bool Parsing_dfs(NODE*& operand, vector<StrExpr>::const_iterator now, string& information) {
        stack<NODE*>operator_sta;

        enum ERROR_TYPE
        {
            NO_ERROR,
            NO_OPERAND_BEFORE,
            UNEXPECTED_OPERAND,
            NO_SUCH_A_VARIABLE
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
                operand->val().val = new VARIABLE;
                GetConst(*operand->val().val, now->name.c_str());
                break;
            case IS_VARIABLE:
                it = variable_table.find(now->name);
                if (it == variable_table.end()) {
                    error_type = NO_SUCH_A_VARIABLE;
                    break;
                }
                operand = new NODE(IS_VARIABLE);
                operand->type = IS_VARIABLE;
                operand->val().val = &variable_table[now->name];
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
                #if DEBUG
                cerr << "operator code = " << op << endl;
                #endif
                switch (numOfOperands[op]) {
                case 0:
                    switch (op) {
                    case LEFT_PARENTHESIS:
                        Parsing_dfs(operand, now, information);
                        break;
                    case RIGHT_PARENTHESIS:
                        while (!operator_sta.empty()) {
                            assert(operator_sta.top());
                            OPERATOR top_op = operator_sta.top()->op();
                            operator_sta.top()->child[numOfOperands[top_op]-1] = operand;
                            operand = operator_sta.top();
                            operator_sta.pop();
                        }
                        finish = true;
                        break;
                    default:
                        ErrMsg(information, "Unexpected operator code ", op);
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
                        ErrMsg(information, "Unexpected operator code ", op);
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
                ErrMsg(information, "No such a node type ", now->type);
            }
        }
        assert(operator_sta.top());
        AddOperandToLastChild(operator_sta.top(), operand);
        operator_sta.pop();

        switch (error_type) {
        case NO_OPERAND_BEFORE:
            information += "No operand before the operator " + now->name + '\n';
            break;
        case UNEXPECTED_OPERAND:
            information += "Unexpected operand " + now->name + '\n';
            break;
        case NO_SUCH_A_VARIABLE:
            information += "No such a variable " + now->name;
            break;
        default:
            //skip
            break;
        }

        return error_type == NO_ERROR ? SUCCEED : FAIL;
    }

    bool CalcByTree(CONST_OR_VARIABLE& ans, const NODE* root, string& information)
    {
        bool result = SUCCEED;

        CONST_OR_VARIABLE ans1;
        CONST_OR_VARIABLE ans2;
        switch (root->type) {
        case IS_CONSTANT:
        case IS_VARIABLE:
            ans = root->val();
            break;
        case IS_OPERATOR:
            switch (root->op()) {
            case ASSIGN:
                result = CalcByTree(ans, root->child[0], information);
                result = CalcByTree(ans2, root->child[0], information);
                result = ans.Copy(ans2, information);
            case ADD:
                result = CalcByTree(ans1, root->child[0], information);
                #if DEBUG
                cerr << "ans1 = " << *(IntType*)ans1.val->val << endl;
                #endif // DEBUG
                result = CalcByTree(ans2, root->child[1], information);
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
                result = CalcByTree(ans1, root->child[0], information);
                result = CalcByTree(ans2, root->child[1], information);
                ans = ans1 - ans2;
                break;
            case MUL:
                result = CalcByTree(ans1, root->child[0], information);
                result = CalcByTree(ans2, root->child[1], information);
                ans = ans1 * ans2;
                break;
            case DIV:
                result = CalcByTree(ans1, root->child[0], information);
                result = CalcByTree(ans2, root->child[1], information);
                ans = ans1 / ans2;
                break;
            default:
                ErrMsg(information, "No such an operator ", root->op());
                break;
            }
            break;
        default:
            ErrMsg(information, "No such an operator ", root->op());
            break;
        }
        ans1.del();
        ans2.del();
        return result;
    }
};

#endif // MYPYMINUSMINUS_H_INCLUDED
