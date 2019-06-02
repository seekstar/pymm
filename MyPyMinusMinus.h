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

    PYMM(){
        Init();
    }

    bool Input(const char* str, ostream& info){
        vector<StrExpr> strExpr;
        NODE* root = NULL;

        if(IsEmptyString(str))
            return SUCCEED;

        FAIL_THEN_RETURN(LexicalAnalysis(strExpr, str, info));

        #if DEBUG
        PrintStrExpr(strExpr);
        #endif // DEBUG

        auto now = strExpr.begin();
        FAIL_THEN_RETURN(Parsing(root, now, info));

#if DEBUG
        PrintTree(cout, root);
#endif

        FAIL_THEN_RETURN(CalcByTree(root, variable_table, info));

        return SUCCEED;
    }
};

#endif // MYPYMINUSMINUS_H_INCLUDED

