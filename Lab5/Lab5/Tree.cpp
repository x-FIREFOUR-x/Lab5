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
void Tree::TLR(string str, int& index, Node*& node)
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
	//cout << RTL(root->ptr[0], 0) << endl;
	for (int i = 0; i < root->ptr.size(); i++)
	{
		LTR(root->ptr[i], 0);	// викликаєм функцію симетричного обходу починаючи з кореня
		cout << endl;
	}
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

void Tree::calculate(map<string, double>&var)
{
	for (int i = 0; i < root->ptr.size(); i++)
	{
		if (root->ptr[i]->date == "=")
			RTL(root->ptr[i], 0, var);
		else
			cout << RTL(root->ptr[i], 0, var);
	}
}


double Tree::RTL(Node* node, int level, map<string, double>&var)
{
	if (node != nullptr)
	{
		if (node->ptr[0] == nullptr)
		{
			if (isdigit(node->date[0]))
				return stod(node->date);
			else
			{
				//cout << "!" << var[node->date] << "!" << endl;
				return var[node->date];
			}
		}
		double sum = 0, right, left;
		right = RTL(node->ptr[1], level + 1, var);
		if (node->date == "+")
			sum = right + RTL(node->ptr[0], level + 1,var);
		if (node->date == "-")
			sum = right - RTL(node->ptr[0], level + 1, var);
		if (node->date == "*")
			sum = right * RTL(node->ptr[0], level + 1, var);
		if (node->date == "/")
			sum = right / RTL(node->ptr[0], level + 1, var);
		if (node->date == "^")
			sum = pow(right, RTL(node->ptr[0], level + 1, var));
		if (node->date == "=")
		{
			//cout << "!!!!";
			var[node->ptr[1]->date] = RTL(node->ptr[0], level + 1, var);
			//var.insert(make_pair(node->ptr[1]->date, RTL(node->ptr[0], level + 1, var)));
			//cout << var[node->ptr[1]->date] << endl;
		}
		return sum;
		//RTL(node->ptr[0], level + 1);
	}
}