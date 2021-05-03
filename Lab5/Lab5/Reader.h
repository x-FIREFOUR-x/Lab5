#pragma once
#include<string>
#include "Tree.h"

using namespace std;

class Reader
{
public:
	string getPostfix(string);
	Tree read_code(string);
};

