#include <iostream>
#include "Tree.h"
#include "Reader.h"
#include <map>

using namespace std;

int main()
{
    map <string, double> var;
    string file;
    getline(cin, file);

    Reader scan;
    Tree tree = scan.read_code(file);
    tree.print_tree();

    tree.calculate(var);
    ////string s;
    return 0;
}

