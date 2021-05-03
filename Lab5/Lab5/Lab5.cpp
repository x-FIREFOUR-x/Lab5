#include <iostream>
#include "Tree.h"
#include "Reader.h"
#include <map>

using namespace std;

int main()
{
    map<string, double> var;
    Tree tree;
    string s;
    getline(cin, s);
    Reader reader;
    cout << reader.getPostfix(s);
    tree.push_operator(reader.getPostfix(s));
    tree.print_tree();
    return 0;
}

