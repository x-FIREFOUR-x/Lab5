#include <iostream>
#include "Tree.h"
using namespace std;
int main()
{

    Tree tree;
    tree.push_operator("+ abc a");
    tree.push_operator("= 2 a");

    tree.push_operator("+ / ^ ^ 3 2 - 5 1 * 2 4 3");
    tree.print_tree();

    return 0;
}

