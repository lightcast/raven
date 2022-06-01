
#include <iostream>
#include <vector>

using std::string;

using namespace std;



std::vector<std::string> vDelimiter = {"<", ">", "==", "=>", "=<", "!="};

string findDelimiter(string expression){
    
    string delimiter = "";

    for(int i = 0; i < vDelimiter.size(); i++){
        delimiter = vDelimiter.at(i);
        size_t found = expression.find(delimiter);

        if(found != string::npos)
            //cout << "not found" << found << endl;
            return delimiter;

    }
    return delimiter;
}

void compareExpression(string expression)
{
    
    string delimiter = findDelimiter(expression);

    cout << delimiter << endl;
   
    string greater = expression.substr(0, expression.find(delimiter));

    expression.erase(0, expression.find(delimiter) + delimiter.length());
    string less = expression.substr(0, expression.find(delimiter));

    cout << "greater than" << greater << endl;
    cout << "less than" << less << endl;


    for(int i = 0; greater == less; i++){
        cout << "hello world";
    }


}

int main(int argc, char *argv[])
{
    compareExpression("10 == 20;");

    return 0;
}