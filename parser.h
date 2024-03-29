#include <iostream>
#include <fstream>
#include <vector>

#include <sstream>

#include <iterator>
#include <algorithm>
#include <map>
// using std::copy;
// using std::cout;
// using std::cin;
// using std::ifstream;
using std::map;
using std::string;
// using std::istream_iterator;
using std::vector;
// using std::endl;
// using std::cerr;
using namespace std;
using std::istream_iterator;

//#include "lexer.h"
#include "variables.h"
#include "expressions.h"
#include "printing.h"
#include "strings.h"
#include "dataTypes.h"
#include "parserErrors.h"

#include "string_methods.h"

#include "loops.h"

inline const char *const BoolToString(bool b)
{
    return b ? "true" : "false";
}

void parseWhileLoop(vector<string> &tokens, int position)
{
}

// void compareExpression(string expression)
// {
//     string delimiter = "<";

//     string greater = expression.substr(0, boolCondition.find(delimiter));

//     boolCondition.erase(0, boolCondition.find(delimiter) + delimiter.length());
//     string less = boolCondition.substr(0, boolCondition.find(delimiter));

//     cout << "greater than" << variableValue << endl;
//     cout << "less than" << less << endl;
// }

int parseForLoop(vector<string> &tokens, int position, map<string, string> &sybmols)
{
    // this is the for loop boolean expression
    // for now we will hard code the for loop to make sure it works
    // cout << "aaaaahere111111" << endl;

    string temp1 = tokens.at(position + 1);

    string delimiter = ";";

    string variableDeclaration = temp1.substr(0, temp1.find(delimiter));
    temp1.erase(0, temp1.find(delimiter) + delimiter.length());
    string boolCondition = temp1.substr(0, temp1.find(delimiter));
    temp1.erase(0, temp1.find(delimiter) + delimiter.length());
    string iterator = temp1.substr(0, temp1.find(delimiter));

    /*cout << "VD" << variableDeclaration << endl;
    cout << "BC" << boolCondition << endl;
    cout << "IT" << iterator << endl;*/



    initializationExpression(variableDeclaration, sybmols, tokens);

    compareExpression(boolCondition);

    updateExpression(iterator);
    
    position  = position + 1;
    
   // cout<< position << "position" << endl;
    int i = loopExpressionBody(position,tokens);
    //cout << i << endl;


/*
    executeForLoop();

*/

return i;

}

void printFromParser(string str, map<string, string> &sybmols)
{
    //      printToScreen("kjkjkjkjjkjkjk");
    //printToScreen(str);
    if (getDataType(str) == "STRING:")
    {
        printToScreen(str);
    }
    else if (getDataType(str) == "NUM:")
    {
        printToScreen(str);
    }
    else if (str.substr(0, 5) == "EXPR:")
    {
        //printToScreen("------" + str);
        //string str = tokens.at(i + 1);
        //printToScreen("EXPR.......");
        //printToScreen(token);

        str = str.substr(5, str.size() - 2);
        str = to_string(evalExpression(str));

        printToScreen(str);
    }
    else if (getDataType(str) == "BOOLEAN:")
    {
        str = str.substr(8, str.size() - 2);
        printToScreen(str);
    }
    else if (str.substr(0, 4) == "VAR:")
    {
        //  printToScreen("------variable" + tokens.at(i + 1));
        string var = str.substr(4);
        printToScreen(getVariable(var, sybmols));
    }
}

void parser(vector<string> &tokens, map<string, string> &sybmols)
{
    int size = tokens.size();
    bool leave = false;

    for (std::vector<string>::size_type i = 0; i < size; i++)
    {
        //std::cout << tokens.at(i) << endl;
        if (leave)
            break;

        //printToScreen("==================token======================");

        string token = tokens.at(i);

        if (token == "ENDIF")
        {
            printToScreen("FOUND AN ENDIF");
        }
        else if (token == "IF")
        {
            //printToScreen("inside of if");
            if (i + 4 <= size)
            {
                //  printVector(tokens);

                if (tokens.at(i + 1).substr(0, 3) == "NUM" && tokens.at(i + 2).substr(0, 4) == "EQEQ" &&
                    tokens.at(i + 3).substr(0, 3) == "NUM" && tokens.at(i + 4).substr(0, 4) == "THEN")
                {
                    /*
                        printToScreen("inside of if");
                        printToScreen(tokens.at(i + 1));
                        printToScreen(tokens.at(i + 3));*/

                    string temp1 = tokens.at(i + 1).substr(4);
                    string temp2 = tokens.at(i + 3).substr(4);

                    int firstNum = stoi(temp1);
                    int secondNum = stoi(temp2);

                    if (firstNum == secondNum)
                    {
                        //   printve
                        // string insideIf = tokens.at(5);
                        //cout << insideIf << endl;
                        //  cout << tokens.at(6) << endl;
                        string value = tokens.at(6);
                        printFromParser(value, sybmols);
                    }
                }
            }
            i = i + 5;
        }
        else if (token == "FOR:")
        {
          int num = parseForLoop(tokens, i, sybmols);
          i = num;
        }
        else if (token == "WHILE:")
        {
            parseWhileLoop(tokens, i);
        }

        else if (token == "PRINT")
        {
            // we will print to the screen
            // there's an imported c++ file that takes care of printing

            /*cout << "token" << token << endl;
            cout << "token method" << token.at(i + 1) << endl;*/

            if (i + 1 <= size)
            {
                string value = tokens.at(i + 1);
                if (value.substr(0, 4) == "VAR:")
                {
                    //cout <<"right here" << endl;

                    printToScreen(value, sybmols);
                }
                else if (value.substr(0, 7) == "METHOD:")
                {
                    // cout << "method" << value << endl;
                    string str = stringMethods(value);
                    if (!str.empty())
                    {
                        printToScreen(str);
                    }
                }
                else
                {
                    // cout << "hhhh" << endl;

                    if (value.substr(0, 5) == "EXPR:")
                    {
                        printFromParser(value, sybmols);
                    }
                    else
                    {
                        printToScreen(value);
                    }
                }

                i = i + 1;
            }











        }
        else if (token.substr(0, 4) == "VAR:")
        {
            // cout << "var" << endl;

            if (i + 1 < size && i + 2 <= size)
            {
                if (tokens.at(i + 1) == "EQUALS:")
                {
                    string varName = token;
                    string varValue = tokens.at(i + 2);
                    if (varValue.substr(0, 4) == "NUM:")
                    {
                        varName = varName.substr(4);
                        varValue = varValue.substr(4);
                        assignVariable(varName, varValue, sybmols);

                        // printToScreen("==================MAP======================");
                        // printMap(sybmols);
                    }
                    else if (varValue.substr(0, 7) == "STRING:")
                    {
                        cout << "var string" << endl;
                        varName = varName.substr(4);
                        varValue = varValue.substr(7);
                        varValue = varValue.substr(1, varValue.length() - 2);
                        printToScreen("-----" + varValue);

                        assignVariable(varName, varValue, sybmols);
                    }
                    else if (varValue.substr(0, 8) == "BOOLEAN:")
                    {
                        varName = varName.substr(4);
                        varValue = varValue.substr(8);
                        varValue = varValue.substr(1, varValue.length() - 2);
                        //printToScreen("-----" + varValue);

                        assignVariable(varName, varValue, sybmols);
                    }
                }
            }
        }
        else if (token.substr(0, 7) == "METHOD:")
        {
            string value = token.substr(7);
            if (value.substr(0, 10) == "GETLENGTH:")
            {
                value = value.substr(10);
                if (value.substr(0, 7) == "STRING:")
                {
                    value = value.substr(7);
                    cout << to_string(getStringLength(value)) << endl;
                }
            }
            else if (value.substr(0, 10) == "UPPERCASE:")
            {
                value = value.substr(10);
                if (value.substr(0, 7) == "STRING:")
                {
                    value = value.substr(7);
                    cout << setStringToUppercase(value) << endl;
                }
            }
            else if (value.substr(0, 10) == "LOWERCASE:")
            {
                value = value.substr(10);
                if (value.substr(0, 7) == "STRING:")
                {
                    value = value.substr(7);
                    cout << setStringLowercase(value) << endl;
                }
            }
            else if (value.substr(0, 5) == "TRIM:")
            {
                value = value.substr(5);
                if (value.substr(0, 7) == "STRING:")
                {
                    value = value.substr(7);

                    cout << stringToTrim(value) << endl;
                }
            }
            else if (value.substr(0, 9) == "ISNUMBER:")
            {
                value = value.substr(9);
                if (value.substr(0, 7) == "STRING:")
                {
                    value = value.substr(7);
                    //cout << value << endl;
                    cout << BoolToString(stringIsNumnber(value)) << endl;
                }
            }
        }
        else if (token.substr(0, 9) == "FUNCTION:")
        {
            if (token.substr(9) == "GETTYPE:")
            {

                if (i + 3 <= size && tokens.at(i + 1) == "FUNCTION_START" && tokens.at(i + 3) == "FUNCTION_END")
                {
                    //printVector(tokens);
                    string value = tokens.at(i + 2);
                    printToScreen(getDataType(value));
                    i = i + 3;
                }
                else
                {
                    if (i + 1 <= size)
                    {
                        string varName = token;
                        string varValue = tokens.at(i + 1);

                        if (getDataType(varValue) == "STRING:")
                        {
                            varValue = varValue.substr(7);
                            typeError(varValue);
                            leave = true;
                            break;
                        }
                        else if (getDataType(varValue) == "NUM:")
                        {
                            varValue = varValue.substr(4);
                            typeError(varValue);
                            leave = true;
                            break;
                        }
                        else if (getDataType(varValue) == "BOOLEAN:")
                        {
                            varValue = varValue.substr(8);
                            typeError(varValue);
                            leave = true;
                            break;
                        }
                        else
                        {
                        }
                        i = i + 1;
                    }
                }
            }
            else if (token.substr(0, 10) == "GETLENGTH:")
            {

                if (i + 3 <= size && tokens.at(i + 1) == "FUNCTION_START" && tokens.at(i + 3) == "FUNCTION_END")
                {
                    //printVector(tokens);
                    string value = tokens.at(i + 2);
                    string dataType = getDataType(value);

                    if (dataType == "STRING:")
                    {
                        //     varValue = varValue.substr(7);
                        //    int stringLength = getStringLength(varValue);
                        // printToScreen(to_string(stringLength));
                    }
                    else
                    {
                    }

                    i = i + 3;
                }
                else
                {
                    if (i + 1 <= size)
                    {
                        string varName = token;
                        string varValue = tokens.at(i + 1);

                        if (getDataType(varValue) == "STRING:")
                        {
                            varValue = varValue.substr(7);
                            typeError(varValue);
                            leave = true;
                            break;
                        }
                        else if (getDataType(varValue) == "NUM:")
                        {
                            varValue = varValue.substr(4);
                            typeError(varValue);
                            leave = true;
                            break;
                        }
                        else if (getDataType(varValue) == "BOOLEAN:")
                        {
                            varValue = varValue.substr(8);
                            typeError(varValue);
                            leave = true;
                            break;
                        }
                        else
                        {
                        }
                        i = i + 1;
                    }
                }
            }
        }
    }
}