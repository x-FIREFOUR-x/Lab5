#include "Reader.h"
#include <vector>
#include <iostream>
#include <fstream>

string Reader::getPostfix(string s)
{
	string result = "";
	vector<string> stack;
	int i = 0;
	bool fl = false;
	int pos = s.find("if ");
	if (pos != s.npos)
	{
		fl = true;
		i = pos + 3;
	}
	while (i < s.length())
	{	
		if (s.find("}") != s.npos)
		{
			return "}";
		}
		if (s.find("else ") != s.npos)
		{
			return "else";
		}
		string operation;
		if (s[i] != ' ')
		{
			int k = 0;
			
			while ((isalpha(s[i + k])) || (isdigit(s[i + k])) || (s[i + k] == '.' ))
				k++;
			if (k == 0)
			{
				k++;
				operation = s[i];
				if ((s[i]!=')') && (s[i]!='(') && !isalpha(s[i + k]) && !isdigit(s[i + k]) && (s[i + k] != ' ') && (s[i + k] != ')') && (s[i + k] != '('))
				{
					operation = operation + string(1, s[i + 1]);
					k++;
				}
				if (operation == "(")
					stack.push_back(operation);
				if ((operation == "==") || (operation == "!="))
				{
					while (!stack.empty() && ((*(stack.end() - 1) == "/") || (*(stack.end() - 1) == "*") || (*(stack.end() - 1) == "^") || (*(stack.end() - 1) == "+") || (*(stack.end() - 1) == "-") || (*(stack.end() - 1) == "<=") || (*(stack.end() - 1) == "<") || (*(stack.end() - 1) == ">=") || (*(stack.end() - 1) == ">")))
					{
						result = *(stack.end() - 1) + " " + result;
						stack.pop_back();
					}
					stack.push_back(operation);
				}
				if ((operation == ">") || (operation == ">=") || (operation == "<=") || (operation == "<"))
				{
					while (!stack.empty() && ((*(stack.end() - 1) == "/") || (*(stack.end() - 1) == "*") || (*(stack.end() - 1) == "^") || (*(stack.end() - 1) == "+") || (*(stack.end() - 1) == "-")))
					{
						result = *(stack.end() - 1) + " " + result;
						stack.pop_back();
					}
					stack.push_back(operation);
				}

				if (operation == "&&")
				{
					while (!stack.empty()&&((*(stack.end() - 1) == "/") || (*(stack.end() - 1) == "*") || (*(stack.end() - 1) == "^") || (*(stack.end() - 1) == "+") || (*(stack.end() - 1) == "-") || (*(stack.end() - 1) == "==") || (*(stack.end() - 1) == "!=") || (*(stack.end() - 1) == "<=") || (*(stack.end() - 1) == "<") || (*(stack.end() - 1) == ">=") || (*(stack.end() - 1) == ">")))
					{
						result = *(stack.end() - 1) + " " + result;
						stack.pop_back();
					}
					stack.push_back(operation);
				}
				if (operation == "||")
				{
					while (!stack.empty() && ((*(stack.end() - 1) == "/") || (*(stack.end() - 1) == "*") || (*(stack.end() - 1) == "^") || (*(stack.end() - 1) == "+") || (*(stack.end() - 1) == "-") || (*(stack.end() - 1) == "==") || (*(stack.end() - 1) == "!=") || (*(stack.end() - 1) == "<=") || (*(stack.end() - 1) == "<") || (*(stack.end() - 1) == ">=") || (*(stack.end() - 1) == ">") || (*(stack.end() - 1) == "&&")))
					{
						result = *(stack.end() - 1) + " " + result;
						stack.pop_back();
					}
					stack.push_back(operation);
				}
				if ((operation == "+") || (operation == "-") || (operation == "="))
				{				
					while(!stack.empty()&&((*(stack.end() - 1) == "/") || (*(stack.end() - 1) == "*") || (*(stack.end() - 1) == "^")|| (*(stack.end() - 1) == "+") || (*(stack.end() - 1) == "-")))
					{
						result = *(stack.end() - 1) + " " + result;
						stack.pop_back();
					}
					stack.push_back(operation);
				}
				if (operation == ")")
				{
					while (*(stack.end() - 1) != "(")
					{
						result = *(stack.end() - 1) + " " + result;
						stack.pop_back();
					}
					stack.pop_back();
				}
				if (operation == "^")
				{
					if (!stack.empty())
					{
						stack.push_back(operation);
					}
					else
					{
						stack.push_back(operation);
					}
				}
				if ((operation == "*") || (operation == "/"))
				{
					while (!stack.empty()&&((*(stack.end() - 1) == "/") || (*(stack.end() - 1) == "*") || (*(stack.end() - 1) == "^")))
					{
						result = *(stack.end() - 1) + " " + result;
						stack.pop_back();
							
					}
					stack.push_back(operation);
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
		result = stack[i] + " " + result;
	}
	if (fl)
		result = "if " + result;
	return result;
}

Tree Reader::read_code(string name_file)
{
	ifstream fin;
	fin.open(name_file);
	vector<string> code;

	string str;
	while (!fin.eof())
	{
		getline(fin, str);
		code.push_back(str);
	}
	code.push_back("");
	Tree tree;
	for (int i = 0; i < code.size() - 1; i++)
	{
		if (code[i].find(';') == code[i].length() - 1)
		{
			str = code[i].substr(0, code[i].length() - 1);
			str = getPostfix(str);
			tree.push_operator(str);
		}
		else
		{
			if (code[i].find("}") != code[i].npos)
			{
				if (code[i + 1].find("else") != code[i].npos)
				{
					str = "}else";
					 i = i + 1;
				}
				else
				{
					str = "}";
				}
			}
			else
			{
				str = code[i];
				str = getPostfix(str);
			}
			if (str!="")
				tree.push_operator(str);
		}
	}
	return tree;
}