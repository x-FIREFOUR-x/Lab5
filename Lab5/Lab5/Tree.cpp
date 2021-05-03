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
void Tree::TLR(string str, int index, Node*& node)
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

			int in_last = str.find(" ", index);				// ��������� �������� ������� �� ������� ������ ���� ��� ��������� ��������� ������
			if (str.npos == in_last)
			{
				in_last = str.length();
			}
			index = in_last + 1;

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
	for (int i = 0 ; i < root->ptr[0]->ptr.size(); i++)
	LTR(root->ptr[i], 0);	// �������� ������� ������������ ������ ��������� � ������
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