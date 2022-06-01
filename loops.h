
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


void initializationExpression(string expression, map<string, string> &sybmols, std::vector<std::string> &tokens){


    string delimiter = "=";
    string variable = expression.substr(0, expression.find(delimiter));
    expression.erase(0, expression.find(delimiter) + delimiter.length());

    string variableValue = expression.substr(0, expression.find(delimiter));

   //cout << variable << "variable...." << endl;
   //cout << variableValue << "variableValue....." << endl;


   //tokens.push_back("VAR:" + variable);


   assignVariable(variable, variableValue, sybmols); 

}


void updateExpression(string expression){
   // cout << "updateExpression......" << expression << endl;


    
}


void executeWhileLoop(vector<string> &tokens, int position)
{
    


}

void compareExpression(string expression)
{
    string delimiter = "<";

    string greater = expression.substr(0, expression.find(delimiter));

    expression.erase(0, expression.find(delimiter) + delimiter.length());
    string less = expression.substr(0, expression.find(delimiter));

   // cout << "greater than" << greater << endl;
   // cout << "less than" << less << endl;
}


// vector<string> &tokens, int position)
void executeForLoop()
{



    
    // this is the for loop boolean expression
    // for now we will hard code the for loop to make sure it works
    
}






int loopExpressionBody(int position, vector<string> &tokens){

   //    cout << "position" << position;
    int loopPositionEnd = 0;
    int size = tokens.size();
     for (std::vector<string>::size_type i = position; i < size; i++)
    {
         string token = tokens.at(i);

        
        if (token == "FORBODYBEGIN:")
        {



        }

        else if(token == "FORBODYEND:"){
            loopPositionEnd = i;
        }
    }


    //cout << "loopPositionend" << loopPositionEnd;
    return loopPositionEnd;

}