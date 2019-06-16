#ifndef MYPYMINUSMINUS_H_INCLUDED
#define MYPYMINUSMINUS_H_INCLUDED

#include <vector>
#include <unordered_map>

#include "MyAnalysis.h"
//#include "MyStringSTL.h"

#include "PrintTree.h"

struct PYMM{
    unordered_map<string, VARIABLE> variable_table;
    stack<char> braces;
    string stored_input;

    //unordered_map<string, int> varNum;  //of user function or array

    PYMM(){
        Init();
    }

    bool Input(const char* input, ostream& info) {
        if (FAIL == Input2(input, info)) {
            stored_input.clear();
            return FAIL;
        } else {
            return SUCCEED;
        }
    }
    bool Input2(const char* input, ostream& info){
        vector<StrExpr> strExpr;
        NODE* root = NULL;

        if(IsEmptyString(input)) {
                return SUCCEED;
        }

        //AppendWithNoCarry(stored_input, input);
        stored_input += input;
        stored_input += '\n';
        UpdateBraces(braces, input);
        if (!braces.empty()) {
                return SUCCEED;
        }
        //stored_input += '\n';
        const char* str = stored_input.c_str();

        FAIL_THEN_RETURN(LexicalAnalysis(strExpr, str, info));

#if DEBUG
        PrintStrExpr(strExpr);
#endif // DEBUG

        auto now = strExpr.begin();
        FAIL_THEN_RETURN(Parsing(root, now, info));

#if DEBUG
        PrintTree(cerr, root);
#endif

        FAIL_THEN_RETURN(CalcByTree(root, variable_table, info));
        DelTree(root);

        stored_input.clear();
        return SUCCEED;
    }
};

#endif // MYPYMINUSMINUS_H_INCLUDED

