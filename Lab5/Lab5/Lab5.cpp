#include <iostream>
#include "Tree.h"
#include "Reader.h"
#include <map>

using namespace std;

int main()
{
    map <string, double> var;
    string file;
    cout << "Input path file code: ";
    getline(cin, file);

    Reader scan;
    Tree tree = scan.read_code(file);
    cout << "Tree AST: " << endl;
    tree.print_tree();

    cout << endl << "Results: " << endl;
    tree.calculate(var);
    
    return 0;
}

