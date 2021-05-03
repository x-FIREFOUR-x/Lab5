#include "Tree.h"
Tree::Tree()
{
	Node* node = new Node;				// створюєм корінь 
	root = node;
	root->date = "Statement list";
}
void Tree::push_operator(string str)
{
	int index = 0;							// індекс початку підрядка в рядку str (підрядок це елемент який потрібно поміщати в вузол) 
	root->ptr.push_back(nullptr);			// створюєм вказіник на нового нащадка
	int number = root->ptr.size() - 1;		// взнаєм індекс вказівника на нового нащадка

	TLR(str, index, root->ptr[number]);		
}
void Tree::TLR(string str, int index, Node*& node)
{
	if (index < str.length())		// перевіряєм чи потрібно створювати нащадків
	{
		node = new Node;										// створюєм новий вузол (нащадка)

		int in_last = str.find(" ", index);						
		if (str.npos == in_last)
		{
			in_last = str.length();
		}
		node->date = str.substr(index, in_last - index);		// кладем в вузол значення (виділяєм підрядок)
		index = in_last + 1;

		if (!(isdigit(node->date[0])) && !(isalpha(node->date[0])) && ((node->date[0]) != '_'))
		{
			node->ptr.push_back(nullptr);
			TLR(str, index, node->ptr[0]);

			int in_last = str.find(" ", index);				// обчислюєм значення індекса на елемент вперед який був відкочений зарахунок рекурсії
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
	LTR(root->ptr[i], 0);	// викликаєм функцію симетричного обходу починаючи з кореня
}
void Tree::LTR(Node* node, int level)
{
	if (node != nullptr)
	{
		LTR(node->ptr[0], level + 1);	// викликаєм цю функцію для лівого нащадка

		for (int i = 0; i < level; i++)		// обробка вузла (виведення з врахуванням відповідного рівня)
		{
			cout << "\t";
		}
		cout << node->date << endl;			// виведення значення вузла

		LTR(node->ptr[1], level + 1);	// викликаєм цю функцію для правого нащадка 
	}
	
}