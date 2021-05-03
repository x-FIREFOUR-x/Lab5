#pragma once
#include <iostream>
#include <string>
#include <vector>
//#include <>
using namespace std;
struct Node
{
	string date;
	vector <Node*> ptr;
};
class Tree
{
	Node* root;
	void TLR(string, int&, Node*& );
	void LTR(Node* node, int level);
	double RTL(Node* node, int level);

public:
	Tree();
	void push_operator(string);
	//void calculate(ma);
	void print_tree();
};

