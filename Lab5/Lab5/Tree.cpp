#include "Tree.h"
Tree::Tree()
{
	Node* node = new Node;				// створюєм корінь 
	root = node;
	root->date = "Statement list";
	subRoot.push_back(root);
}
void Tree::push_operator(string str)
{
	if (str.substr(0, 3) != "if ")
	{
		if (str[0] != '}')
		{
			int index = 0;							// індекс початку підрядка в рядку str (підрядок це елемент який потрібно поміщати в вузол) 
			subRoot.back()->ptr.push_back(nullptr);			// створюєм вказіник на нового нащадка
			int number = subRoot.back()->ptr.size() - 1;		// взнаєм індекс вказівника на нового нащадка

			TLR(str, index, subRoot.back()->ptr[number]);
		}
		else
		{
			
			if (str.find("else") == str.npos)
			{
				
				if (subRoot.back()->date == "List1")
				{
					
					subRoot.pop_back();
					subRoot.pop_back();
				}
				else
				{
					subRoot.pop_back();
				}
			}
			else
			{
				subRoot.pop_back();
			}
		}
	}
	else
	{
		pushIf(subRoot.back(), str);
	}
}

void Tree::push_operator(Node* root, string str)
{
	int index = 0;							// індекс початку підрядка в рядку str (підрядок це елемент який потрібно поміщати в вузол) 
	root->ptr.push_back(nullptr);			// створюєм вказіник на нового нащадка
	int number = root->ptr.size() - 1;		// взнаєм індекс вказівника на нового нащадка
	TLR(str, index, root->ptr[number]);
}

void Tree::pushIf(Node* root1, string str)
{
	int index = 0;							// індекс початку підрядка в рядку str (підрядок це елемент який потрібно поміщати в вузол) 
	root1->ptr.push_back(nullptr);			// створюєм вказіник на нового нащадка
	int number = root1->ptr.size() - 1;		// взнаєм індекс вказівника на нового нащадка
	Node* node = new Node;
	node->date = "if";
	root1->ptr[number] = node;
	node->ptr.push_back(nullptr);
	node->ptr.push_back(nullptr);
	node->ptr.push_back(nullptr);
	index = 3;
	TLR(str, index, node->ptr[0]);
	Node* list2 = new Node;
	list2->date = "List2";
	node->ptr[2] = list2;
	Node* list1 = new Node;
	list1->date = "List1";
	node->ptr[1] = list1;
	subRoot.push_back(list2);
	subRoot.push_back(list1);
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
	for (int i = 0; i < root->ptr.size(); i++)
	{
		LTR(root->ptr[i], 0);	// викликаєм функцію симетричного обходу починаючи з кореня
		cout << endl;
	}
	//cout << root[]
}

void Tree::LTR(Node* node, int level)
{
	if (node != nullptr)
	{
		if (!node->ptr.empty())
			LTR(node->ptr[0], level + 1);	// викликаєм цю функцію для лівого нащадка
		for (int i = 0; i < level; i++)		// обробка вузла (виведення з врахуванням відповідного рівня)
		{
			cout << "\t";
		}
		cout << node->date << endl;			// виведення значення вузла
		for(int i = 1; i < node->ptr.size(); i++)
			LTR(node->ptr[i], level + 1);	// викликаєм цю функцію для правого нащадка 
	}
	
}

void Tree::calculate(map<string, double>&var)
{
	for (int i = 0; i < root->ptr.size(); i++)
	{
		if (root->ptr[i] != nullptr)
		{
			if (root->ptr[i]->date == "=")
				RTL(root->ptr[i], 0, var);
			else
			{
				if (root->ptr[i]->date == "if")
				{
					choose(root->ptr[i], var);
				}
				else
					cout << "result: " << RTL(root->ptr[i], 0, var) << endl;
			}
				
		}
		
	}
}

void Tree::calculate(Node*root, map<string, double>& var)
{
	for (int i = 0; i < root->ptr.size(); i++)
	{
		if (root->ptr[i] != nullptr)
		{
			if (root->ptr[i]->date == "=")
				RTL(root->ptr[i], 0, var);
			else
			{
				if (root->ptr[i]->date == "if")
				{
					choose(root->ptr[i], var);
				}
				else
					cout << "result:" << RTL(root->ptr[i], 0, var) << endl;
			}

		}

	}
}

void Tree::choose(Node*root, map<string, double>& var)
{
	if (RTL(root->ptr[0], 0, var))
		calculate(root->ptr[1], var);
	else
		calculate(root->ptr[2], var);
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
		if (node->date == ">")
			if (right > RTL(node->ptr[0], level + 1, var))
				sum = 1;
		if (node->date == "<")
			if (right < RTL(node->ptr[0], level + 1, var))
				sum = 1;
		if (node->date == ">=")
			if (right >= RTL(node->ptr[0], level + 1, var))
				sum = 1;
		if (node->date == "<=")
			if (right <= RTL(node->ptr[0], level + 1, var))
				sum = 1;
		if (node->date == "==")
			if (right == RTL(node->ptr[0], level + 1, var))
				sum = 1;
		if (node->date == "!=")
			if (right != RTL(node->ptr[0], level + 1, var))
				sum = 1;
		if (node->date == "&&")
			if (right && RTL(node->ptr[0], level + 1, var))
				sum = 1;
		if (node->date == "||")
			if (right || RTL(node->ptr[0], level + 1, var))
				sum = 1;
		if (node->date == "=")
		{
			var[node->ptr[1]->date] = RTL(node->ptr[0], level + 1, var);
		}
		
		return sum;
	}
}