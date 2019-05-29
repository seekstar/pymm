#ifndef PRINTTREE_H_INCLUDED
#define PRINTTREE_H_INCLUDED

#include <string>
#include <algorithm>

#include "MyAnalysis.h"
#include "MyQueue.h"

using namespace std;

#if DEBUG
void FillNewLine(MyQueue<string>& lines, size_t index, const vector<size_t>& rec_branch);
size_t LoadStr(MyQueue<string>& lines, const char str[], const vector<size_t>& rec_branch);
void PrintOperatorBranch(ostream& res, NODE* root, MyQueue<string>& lines, vector<size_t>& rec_branch);
void PrintTree(ostream& res, NODE* root, MyQueue<string>& lines, vector<size_t>& rec_branch);
void PrintTree(ostream& res, NODE* root);
#endif // DEBUG

#endif

