#include "PrintTree.h"

//Fill the index-th line
void FillNewLine(MyQueue<string>& lines, size_t index, const vector<size_t>& rec_branch) {
	if (index == lines.size()) {
		lines.push("");
	}
	string& line = lines[index];
	size_t j = line.size();
	size_t i = lower_bound(rec_branch.begin(), rec_branch.end(), j) - rec_branch.begin();
	for (; i < rec_branch.size(); ++i) {
		for (; j < rec_branch[i]; ++j) {
			line += ' ';
		}
		line += '|';
		++j;
	}
	line += "  ";	//2 space
}
//str must have the trailing carry
//return the lines that used
size_t LoadStr(MyQueue<string>& lines, const char str[], const vector<size_t>& rec_branch) {
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
			}
		} else {
			lines[i] += *str;
		}
	}
	return i;
}
void PrintOperatorBranch(ostream& res, NODE* root, MyQueue<string>& lines, vector<size_t>& rec_branch) {
	lines.front() += "-----";
	rec_branch.push_back(lines.front().size() - 3);
	int num = numOfOperands[root->op()];
	for (int i = 0; i < num - 1; ++i) {
		PrintTree(res, root->child[i], lines, rec_branch);
	}
	lines.front() += "";
	rec_branch.pop_back();
	PrintTree(res, root->child[num-1], lines, rec_branch);
}
void PrintTree(ostream& res, NODE* root, MyQueue<string>& lines, vector<size_t>& rec_branch) {
	ostringstream out;
	root->PrintNode(out);
	out << endl;
	int used_lines = LoadStr(lines, out.str().c_str(), rec_branch);
	#if DEBUG
	for (int i = 0; i < lines.size(); ++i) {
		cerr << lines[i] << endl;
	}
	cerr << endl << "branches:";
	for (int i = 0; i < rec_branch.size(); ++i) {
		cerr << rec_branch[i] << ' ';
	}
	cerr << endl;
	#endif // DEBUG
	switch (root->type) {
	case IS_CONSTANT:
	case IS_VARIABLE:
		while (used_lines--) {
			res << lines.front() << endl;
			lines.pop();
		}
		break;
	case IS_OPERATOR:
		PrintOperatorBranch(res, root, lines, rec_branch);
		break;
	default:
		cerr << "Invalid node type code " << root->type << endl;
		break;
	}
}
//driver function
void PrintTree(ostream& res, NODE* root) {
	MyQueue<string> lines;
	vector<size_t> rec_branch;
	lines.push(string());
	PrintTree(res, root, lines, rec_branch);
}
