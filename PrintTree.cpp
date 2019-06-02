#include "PrintTree.h"

//Fill the index-th line. Fill until print the last '|'.
void FillNewLine(MyQueue<MyString>& lines, size_t index, const vector<size_t>& rec_branch) {
	if (index == lines.size()) {
		lines.push("");
	}
	MyString& line = lines[index];
	size_t j = line.size();
	size_t i = lower_bound(rec_branch.begin(), rec_branch.end(), j) - rec_branch.begin();
	for (; i < rec_branch.size(); ++i) {
		for (; j < rec_branch[i]; ++j) {
			line += ' ';
		}
		line += '|';
		++j;
	}
}
//str must have the trailing carry
//return the lines that used
//Do not fill extra line.
size_t LoadStr(MyQueue<MyString>& lines, const char str[], const vector<size_t>& rec_branch) {
	size_t i = 0, max_len = 0;
	for (; *str; ++str) {
		if ('\n' == *str) {
			max_len = max(max_len, lines[i].size());
			for (size_t j = 0; j <= i; ++j) {
				//obviously max_len >= lines[j].size()
				lines[j].append(max_len - lines[j].size(), ' ');
			}
			++i;
			//There is a next line
			if (*(str+1)) {
				FillNewLine(lines, i, rec_branch);
				lines[i] += "  ";	//2 space
			}
		} else {
			lines[i] += *str;
		}
	}
	return i;
}
void PrintABranch(MyQueue<MyString>& lines, vector<size_t>& rec_branch) {
	lines.front() += "-----";
	rec_branch.push_back(lines.front().size() - 3);
}
int NumOfBranches(const NODE* root) {
	switch (root->type) {
	case IS_OPERATOR:
		return numOfOperands[root->op()];
	case IS_STRUCTURE:
		return structureBranches[root->structure()];
	default:
		assert(1);
		return -1;
	}
}
bool LastChildHasSibling(const NODE* root) {
	return root ? (root->child[NumOfBranches(root)-1]->sibling != NULL) : false;
}
void PrintBranches(ostream& res, NODE* root, MyQueue<MyString>& lines, vector<size_t>& rec_branch) {
	assert(root);
	int num_branch = NumOfBranches(root);
	PrintABranch(lines, rec_branch);
	for (int i = 0; i < num_branch - 1; ++i) {
		PrintTree(res, root->child[i], lines, rec_branch);
		FillNewLine(lines, 0, rec_branch);
		lines.front() += "--";
	}
	bool lastHasSibling = LastChildHasSibling(root);
	if (!lastHasSibling)
		rec_branch.pop_back();
	PrintTree(res, root->child[num_branch-1], lines, rec_branch);
	if (lastHasSibling)
		rec_branch.pop_back();
	//FillNewLine(lines, 0, rec_branch);
}
//Do not print the last '\n'
void PrintTree(ostream& res, NODE* root, MyQueue<MyString>& lines, vector<size_t>& rec_branch) {
	while (root) {
		FillNewLine(lines, 0, rec_branch);
		ostringstream out;
		if (root->output) {
			out << "(o)";
		}
		root->PrintNode(out);
		out << endl;
		int used_lines = LoadStr(lines, out.str().c_str(), rec_branch);
		#if DEBUG_PRINT_TREE
		for (size_t i = 0; i < lines.size(); ++i) {
			cerr << lines[i] << endl;
		}
		cerr << endl << "branches:";
		for (size_t i = 0; i < rec_branch.size(); ++i) {
			cerr << rec_branch[i] << ' ';
		}
		cerr << endl;
		#endif // DEBUG_PRINT_TREE
		switch (root->type) {
		case IS_CONSTANT:
		case IS_VARIABLE:
			while (used_lines--) {
				res << lines.front() << endl;
				lines.pop();
			}
			break;
		case IS_OPERATOR:
		case IS_STRUCTURE:
			PrintBranches(res, root, lines, rec_branch);
			break;
		default:
			cerr << "Invalid node type code " << root->type << endl;
			break;
		}
		root = root->sibling;
	}
}
//driver function
void PrintTree(ostream& res, NODE* root) {
	assert(root);
	MyQueue<MyString> lines;
	vector<size_t> rec_branch;
	lines.push(MyString());
	PrintTree(res, root, lines, rec_branch);
}
