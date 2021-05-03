#include <iostream>
#include "Tree.h"
#include "Reader.h"
#include <map>

using namespace std;

int main()
{
    string file;
    getline(cin, file);
    Reader scan;
    Tree tree = scan.read_code(file);
    tree.print_tree();
    string s;
    getline(cin, s);
    Reader reader;
    cout << reader.getPostfix(s);
    return 0;
}

