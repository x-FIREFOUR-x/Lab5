#include "Tree.h"
Tree::Tree()
{
	Node* node = new Node;				// �������� ����� 
	root = node;
	root->date = "Statement list";
}
void Tree::push_operator(string str)
{
	int index = 0;							// ������ ������� ������� � ����� str (������� �� ������� ���� ������� ������� � �����) 
	root->ptr.push_back(nullptr);			// �������� ������� �� ������ �������
	int number = root->ptr.size() - 1;		// ����� ������ ��������� �� ������ �������

	TLR(str, index, root->ptr[number]);		
}
void Tree::TLR(string str, int& index, Node*& node)
{
	if (index < str.length())		// ��������� �� ������� ���������� �������
	{
		node = new Node;										// �������� ����� ����� (�������)

		int in_last = str.find(" ", index);						
		if (str.npos == in_last)
		{
			in_last = str.length();
		}
		node->date = str.substr(index, in_last - index);		// ������ � ����� �������� (������� �������)
		index = in_last + 1;

		if (!(isdigit(node->date[0])) && !(isalpha(node->date[0])) && ((node->date[0]) != '_'))
		{
			node->ptr.push_back(nullptr);
			TLR(str, index, node->ptr[0]);

			node->ptr.push_back(nullptr);
			TLR(str, index, node->ptr[1]);
		}
		else
		{
			node->ptr.push_back(nullptr);
			node->ptr.push_back(nullptr);
		}
	}
}

void Tree::print_tree()
{
	cout << RTL(root->ptr[0], 0) << endl;
	for (int i = 0; i < root->ptr.size(); i++)
	{
		LTR(root->ptr[i], 0);	// �������� ������� ������������ ������ ��������� � ������
		cout << endl;
	}
	
}
void Tree::LTR(Node* node, int level)
{
	if (node != nullptr)
	{
		LTR(node->ptr[0], level + 1);	// �������� �� ������� ��� ����� �������

		for (int i = 0; i < level; i++)		// ������� ����� (��������� � ����������� ���������� ����)
		{
			cout << "\t";
		}
		cout << node->date << endl;			// ��������� �������� �����

		LTR(node->ptr[1], level + 1);	// �������� �� ������� ��� ������� ������� 
	}
	
}

double Tree::RTL(Node* node, int level)
{
	if (node != nullptr)
	{
		if (node->ptr[0] == nullptr)
		{
			return stod(node->date);
		}
		double sum, right, left;
		right = RTL(node->ptr[1], level + 1);
		if (node->date == "+")
			sum = right + RTL(node->ptr[0], level + 1);
		if (node->date == "-")
			sum = right - RTL(node->ptr[0], level + 1);
		if (node->date == "*")
			sum = right * RTL(node->ptr[0], level + 1);
		if (node->date == "/")
			sum = right / RTL(node->ptr[0], level + 1);
		if (node->date == "^")
			sum = pow(right, RTL(node->ptr[0], level + 1));
		return sum;
		//RTL(node->ptr[0], level + 1);
	}

}