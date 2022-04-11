
#include <iostream>

using namespace std;

void compareExpression(string expression)
{
    string delimiter = "<";

    cout << expression.npos == expression.find(">");
    if (expression.find('>'))
    {
        cout << "true" << endl;
    }
    else
    {
        cout << "false" << endl;
    }

    cout << expression.find('<') << endl;

    string greater = expression.substr(0, expression.find(delimiter));

    expression.erase(0, expression.find(delimiter) + delimiter.length());
    string less = expression.substr(0, expression.find(delimiter));

    cout << "greater than" << greater << endl;
    cout << "less than" << less << endl;
}

int main(int argc, char *argv[])
{
    compareExpression("10 < 20;");

    return 0;
}