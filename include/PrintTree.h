#ifndef PRINTTREE_H_INCLUDED
#define PRINTTREE_H_INCLUDED

#include <algorithm>

#include "MyAnalysis.h"
#include "MyQueue.h"
#include "MyStringSTL.h"

#define DEBUG_PRINT_TREE 0

using namespace std;

void FillNewLine(MyQueue<MyString>& lines, size_t index, const vector<size_t>& rec_branch);
size_t LoadStr(MyQueue<MyString>& lines, const char str[], const vector<size_t>& rec_branch);
void PrintOperatorBranch(ostream& res, NODE* root, MyQueue<MyString>& lines, vector<size_t>& rec_branch);
void PrintTree(ostream& res, NODE* root, MyQueue<MyString>& lines, vector<size_t>& rec_branch);
void PrintTree(ostream& res, NODE* root);

#endif

