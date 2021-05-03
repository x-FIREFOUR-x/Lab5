#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct Node
{
	string date;
	vector <Node*> ptr;
};
class Tree
{
	Node* root;
	void TLR(string, int, Node*& );
	void LTR(Node* node, int level);

public:
	Tree();
	void push_operator(string);
	void print_tree();
};

