#include <iostream>
#include "Tree.h"
using namespace std;
int main()
{

    Tree tree;
    tree.push_operator("+ abc a");
    tree.print_tree();

    return 0;
}

