#ifndef MYANALYSIS_H_INCLUDED
#define MYANALYSIS_H_INCLUDED

#include <ctype.h>
#include <map>
#include <set>
#include <stack>
#include <unordered_map>

#include "MyVariable.h"
#include "MyString.h"
#include "MyError.h"
#include "MyFlags.h"
//#include "MyStringSTL.h"

#define MAX_CHILD 4

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
    IS_USER_FUNC_OR_ARRAY,
	IS_SEPARATOR,
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
    /*INC_FRONT,
    DEC_FRONT,
    INC_BACK,
    DEC_BACK,*/
    INC,
    DEC,

    LESS,
    LESS_EQ,
    GREATER,
    GREATER_EQ,
    EQUAL,
    NOT_EQUAL,

    AND,
    OR,
    NOT,

    BIT_AND,
    BIT_OR,
    BIT_NOT,
    
    LEFT_PARENTHESIS,
    RIGHT_PARENTHESIS,
    //LEFT_BRACE,
    //RIGHT_BRACE
};

const char* OperatorName(OPERATOR op);

enum KEY_WORD {
    IF_KEY,
	ELSE_KEY,
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

enum SEPARATOR {
	LEFT_BRACE,
	RIGHT_BRACE,
	SEMICOLON,
	ENTER,
	COMMA
};

const char* SeparatorName(SEPARATOR separator);

struct StrExpr {
    NodeType type;
    string name;
};

struct NODE {
    NodeType type;
    void* sth;

    NODE* sibling;
    NODE* child[MAX_CHILD];
	bool output;

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
        case IS_USER_FUNC_OR_ARRAY:
            delete (string*)sth;
            break;
		case IS_SEPARATOR:
            assert(1);
			delete (SEPARATOR*)sth;
			break;
        case IS_NIL:
            break;  //skip
        }
    }
    void Init(NodeType _type) {
        type = _type;
		sibling = NULL;
		memset(child, 0, sizeof(child));
		output = false;
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
        case IS_USER_FUNC_OR_ARRAY:
            sth = new string;
            break;
		case IS_SEPARATOR:
            assert(1);
			sth = new SEPARATOR;
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
    string& user_func_or_array() {
        return *(string*)sth;
    }
	const string& user_func_or_array() const {
		return *(const string*)sth;
	}
	SEPARATOR& separator() {
        assert(1);
		return *(SEPARATOR*)sth;
	}
	const SEPARATOR& separator() const {
        assert(1);
		return *(const SEPARATOR*)sth;
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
        case IS_USER_FUNC_OR_ARRAY:
            out << *(string*)sth;
            break;
		case IS_SEPARATOR:
            assert(1);
			out << SeparatorName(*(SEPARATOR*)sth);
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



enum ERROR_TYPE
{
    NO_ERROR,
    NO_OPERAND_BEFORE,
    UNEXPECTED_OPERAND,
	UNEXPECTED_LEFT_BRACE,
	UNEXPECTED_ELSE_KEY,
	UNRECOGNIZED_KEY
};
void PrintErrorMsg(ERROR_TYPE type, const string& name, ostream& info);

bool LexicalAnalysis(vector<StrExpr>& strExpr, const char* str, ostream& info);

bool Parsing(NODE*& root, vector<StrExpr>::iterator& now, ostream& info);
bool Parsing_dfs(NODE*& operand, vector<StrExpr>::iterator& now, bool& finish, ostream& info);
void Parsing_IS_CONSTANT(NODE*& operand, ERROR_TYPE& error_type, const vector<StrExpr>::iterator& now);
bool Parsing_IS_OPERATOR(NODE*& operand, ERROR_TYPE& error_type, vector<StrExpr>::iterator& now,  stack<NODE*>& operator_sta, bool& finish, ostream& info);
bool Parsing_IS_KEY_WORD(NODE*& operand, ERROR_TYPE& error_type, vector<StrExpr>::iterator& now, ostream& info);
void Parsing_IS_SEPARATOR(ERROR_TYPE& error_type, const string& name, bool& needReturn, bool& finish, bool& need_output);
bool Parsing_IS_USER_FUNC_OR_ARRAY(NODE*& operand, vector<StrExpr>::iterator& now, ostream& info);

bool CalcByTree(const NODE* root, unordered_map<string, VARIABLE>& variable_table, ostream& info);
bool CalcByTree(CONST_OR_VARIABLE& ans, const NODE* root, bool create_variable, unordered_map<string, VARIABLE>& variable_table, ostream& info);
bool CalcByTree_IS_OPERATOR(const NODE* root, CONST_OR_VARIABLE& ans, unordered_map<string, VARIABLE>& variable_table, ostream& info);
bool CalcByTree_IS_STRUCTURE(const NODE* root, unordered_map<string, VARIABLE>& variable_table, ostream& info);
bool CalcByTree_IS_USER_FUNC_OR_ARRAY(const NODE* root, CONST_OR_VARIABLE& ans, bool create_variable, unordered_map<string, VARIABLE>& variable_table, ostream& info);

extern map<string, OPERATOR> operator_code;
extern map<OPERATOR, int>priority;
extern map<OPERATOR, int>numOfOperands;
extern map<OPERATOR, bool>associative;
extern set<char>symbols;
extern map<string, KEY_WORD> key_word_code;
extern map<string, SYS_FUNC> sys_func_code;
extern map<string, SEPARATOR> separator_code;
extern map<STRUCTURE, int> structureBranches;

void Init(void);

bool IsSymbol(char ch);
bool IsBeginOfVarialbeOrFunc(char ch);
bool IsPartOfVariableOrFunc(char ch);
bool IsAnOperator(const string& sth);
bool IsSysFunc(const string& sth);
bool IsKeyWord(const string& sth);



NODE* OperandBecomeLeftChild(OPERATOR op, NODE*& operand);
void AddOperandToLastChild(NODE* op, NODE*& operand);
void PopAllOperators(stack<NODE*>& operator_sta, NODE*& operand);


bool UpdateBraces(stack<char>& braces, const char*& str);

void PrintStrExpr(const vector<StrExpr> strExpr);

#endif // MYANALYSIS_H_INCLUDED

