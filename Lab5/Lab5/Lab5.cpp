#include <iostream>
#include "Reader.h"

using namespace std;

int main()
{
    string s;
    getline(cin, s);
    Reader reader;
    cout << reader.getPostfix(s);
    return 0;
}

