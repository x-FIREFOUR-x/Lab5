#include <iostream>
#include "Tree.h"
#include "Reader.h"

using namespace std;

int main()
{

    Tree tree;
    tree.push_operator("+ abc a");
    tree.push_operator("= 2 a");

    tree.push_operator("+ / ^ ^ 3 2 - 5 1 * 2 4 3");
    tree.print_tree();

    string s;
    getline(cin, s);
    Reader reader;
    cout << reader.getPostfix(s);
    return 0;
}

