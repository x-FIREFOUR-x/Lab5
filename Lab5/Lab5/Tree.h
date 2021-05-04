#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;
struct Node
{
	string date;
	vector <Node*> ptr;
};
class Tree
{
	Node* root;
	vector<Node*> subRoot;
	void TLR(string, int&, Node*& );
	void LTR(Node* node, int level);
	double RTL(Node* node, int level, map<string, double>& var);

public:
	Tree();
	void push_operator(string);
	void pushIf(Node*, string);
	void push_operator(Node*, string);
	void calculate(map<string, double>&);
	void calculate(Node*, map<string, double>&);
	void print_tree();
};

