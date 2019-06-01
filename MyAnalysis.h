#ifndef MYANALYSIS_H_INCLUDED
#define MYANALYSIS_H_INCLUDED

#include <ctype.h>
#include <map>
#include <set>
#include <stack>

#include "MyVariable.h"
#include "MyString.h"
//#include "MyStringSTL.h"

#define MAX_CHILD 3

using namespace std;

const bool LEFT_ASSOCIATIVE = false;
const bool RIGHT_ASSOCIATIVE = true;

enum NodeType {
    IS_CONSTANT,
    IS_VARIABLE,
    IS_OPERATOR,
    IS_KEY_WORD,
    IS_STRUCTURE,
    IS_SYS_FUNC,
    IS_USER_FUNC,
    IS_NIL
};

string NodeType2string(NodeType type);

enum OPERATOR {
    NIL,
    ASSIGN,
    ADD,
    ADD_EQ,
    SUB,
    SUB_EQ,
    MUL,
    MUL_EQ,
    DIV,
    DIV_EQ,
    MODULUS,
    MODULUS_EQ,
    MINUS,
    LESS,
    LESS_EQ,
    GREATER,
    GREATER_EQ,
    LEFT_PARENTHESIS,
    RIGHT_PARENTHESIS,
    //LEFT_BRACE,
    //RIGHT_BRACE
};

const char* OperatorName(OPERATOR op);

enum KEY_WORD {
    IF_KEY,
    WHILE_KEY,
    FOR_KEY,
    DO_KEY
};

const char* KeyWordName(KEY_WORD key_word);

enum STRUCTURE {
    IF,
    WHILE,
    FOR,
    DO_WHILE
};

const char* StructureName(STRUCTURE structure);

enum SYS_FUNC {
    SQRT,
    SIN,
    COS,
    ABS
};

const char* SysFuncName(SYS_FUNC sys_func);

struct StrExpr {
    NodeType type;
    string name;
};

struct NODE {
    NodeType type;
    void* sth;

    NODE* sibling;
    NODE* child[MAX_CHILD];

    NODE(NodeType _type) {
        Init(_type);
    }
    ~NODE() {
        del();
    }
    void del() {
        if (!sth) return;
        switch (type) {
        case IS_CONSTANT:
        case IS_VARIABLE:
			((CONST_OR_VARIABLE*)sth)->del();
            delete (CONST_OR_VARIABLE*)sth;
            break;
        case IS_OPERATOR:
            delete (OPERATOR*)sth;
            break;
        case IS_KEY_WORD:
            delete (KEY_WORD*)sth;
            break;
        case IS_STRUCTURE:
            delete (STRUCTURE*)sth;
            break;
        case IS_SYS_FUNC:
            delete (SYS_FUNC*)sth;
            break;
        case IS_USER_FUNC:
            delete (string*)sth;
            break;
        case IS_NIL:
            break;  //skip
        }
    }
    void Init(NodeType _type) {
        type = _type;
        switch (type) {
        case IS_CONSTANT:
            sth = new CONST_OR_VARIABLE(false, true);
            break;
        case IS_VARIABLE:
			sth = new string;
            break;
        case IS_OPERATOR:
            sth = new OPERATOR;
            break;
        case IS_KEY_WORD:
            sth = new KEY_WORD;
            break;
        case IS_STRUCTURE:
            sth = new STRUCTURE;
            break;
        case IS_SYS_FUNC:
            sth = new SYS_FUNC;
            break;
        case IS_USER_FUNC:
            sth = new string;
            break;
        default:
            static char tmp[20];
            MyItoa(tmp, type);
            cerr << "Internal error: No such a type code " << tmp << '\n';
            break;
        }
    }
    CONST_OR_VARIABLE& constant() {
        return *(CONST_OR_VARIABLE*)sth;
    }
    const CONST_OR_VARIABLE& constant() const {
        return *(const CONST_OR_VARIABLE*)sth;
    }
	string& variable() {
		return *(string*)sth;
	}
	const string& variable() const {
		return *(const string*)sth;
	}
    OPERATOR& op() {
        return *(OPERATOR*)sth;
    }
    const OPERATOR& op() const {
        return *(const OPERATOR*)sth;
    }
    KEY_WORD& key_word() {
        return *(KEY_WORD*)sth;
    }
    const KEY_WORD& key_word() const {
        return *(const KEY_WORD*)sth;
    }
    STRUCTURE& structure() {
        return *(STRUCTURE*)sth;
    }
    const STRUCTURE& structure() const {
        return *(const STRUCTURE*)sth;
    }
    SYS_FUNC& sys_func() {
        return *(SYS_FUNC*)sth;
    }
    const SYS_FUNC& sys_func() const {
        return *(const SYS_FUNC*)sth;
    }
    string& user_func() {
        return *(string*)sth;
    }

    void PrintNode(ostream& out) {
        switch (type) {
        case IS_CONSTANT:
            ((CONST_OR_VARIABLE*)sth)->Print(out);
            break;
        case IS_VARIABLE:
			out << *(string*)sth;
            break;
        case IS_OPERATOR:
            out << OperatorName(*(OPERATOR*)sth);
            break;
        case IS_KEY_WORD:
            out << KeyWordName(*(KEY_WORD*)sth);
            break;
        case IS_STRUCTURE:
            out << StructureName(*(STRUCTURE*)sth);
            break;
        case IS_SYS_FUNC:
            out << SysFuncName(*(SYS_FUNC*)sth);
            break;
        case IS_USER_FUNC:
            out << *(string*)sth;
            break;
        case IS_NIL:
            out << "/\\";
            break;
        }
    }
};

struct OPERAND_OR_OPERATOR {
    bool is_operator;
    union {
        CONST_OR_VARIABLE val;
        OPERATOR op;
    };
};

extern map<string, OPERATOR> operator_code;
extern map<OPERATOR, int>priority;
extern map<OPERATOR, int>numOfOperands;
extern map<OPERATOR, bool>associative;
extern set<char>symbols;
extern map<string, KEY_WORD> key_word_code;
extern map<string, SYS_FUNC> sys_func_code;

NODE* OperandBecomeLeftChild(OPERATOR op, NODE*& operand);
void AddOperandToLastChild(NODE* op, NODE*& operand);
void PopAllOperators(stack<NODE*>& operator_sta, NODE*& operand);

#if DEBUG
void PrintStrExpr(const vector<StrExpr> strExpr);
#endif // DEBUG

#endif // MYANALYSIS_H_INCLUDED

