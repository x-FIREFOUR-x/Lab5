#include "Reader.h"
#include <vector>
#include <iostream>

string Reader::getPostfix(string s)
{
	string result = "";
	vector<char> stack;
	int i = 0;
	while (i < s.length())
	{
		
		char operation;
		if (s[i] != ' ')
		{
			int k = 0;
			
			while ((isalpha(s[i + k])) || (isdigit(s[i + k])) || (s[i + k] == '.' ))
				k++;
			//cout << k;
			//system("pause");
			if (k == 0)
			{
				k++;
				operation = s[i];
				if ((operation == '+') || (operation == '-') || (operation == '=') || (operation == '('))
					stack.push_back(operation);
				if (operation == ')')
				{
					while (*(stack.end() - 1) != '(')
					{
						result = string(1, *(stack.end() - 1)) + " " + result;
						stack.pop_back();
					}
					stack.pop_back();
				}
				if ((operation == '*') || (operation == '/') || (operation == '^'))
				{
					if ((*(stack.end() - 1) == '/') || (*(stack.end() - 1) == '^')|| (*(stack.end() - 1) == '*'))
					{
						result = string(1, *(stack.end() - 1)) + " " + result;
						stack.pop_back();
						stack.push_back(operation);
					}
					else
					{
						stack.push_back(operation);
					}
				}
			}
			else
			{
				result = s.substr(i, k) + " " + result;
			}
			i = k + i - 1;
		}
		i++;
	}
	for (int i = stack.size() - 1; i >= 0; i--)
	{
		string l = string(1, stack[i]);
		result = l + " " + result;
	}
	return result;
}