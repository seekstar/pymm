#ifndef MYPYMINUSMINUS_H_INCLUDED
#define MYPYMINUSMINUS_H_INCLUDED

#include <vector>
#include <unordered_map>

#include "MyAnalysis.h"
//#include "MyStringSTL.h"

#if DEBUG
#include "PrintTree.h"
#endif // DEBUG

struct PYMM{
    unordered_map<string, VARIABLE> variable_table;
    stack<char> braces;
    string stored_input;

    PYMM(){
        Init();
    }

    bool Input(const char* input, ostream& info){
        vector<StrExpr> strExpr;
        NODE* root = NULL;

        if(IsEmptyString(input)) {
                return SUCCEED;
        }

        AppendWithNoCarry(stored_input, input);
        UpdateBraces(braces, input);
        if (!braces.empty()) {
                return SUCCEED;
        }
        stored_input += '\n';
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

        stored_input.clear();
        return SUCCEED;
    }
};

#endif // MYPYMINUSMINUS_H_INCLUDED

