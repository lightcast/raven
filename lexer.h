#include <iostream>
#include <fstream>
#include <vector>

#include <iterator>
#include <algorithm>
#include <map>
// using std::copy;
// using std::cout;
// using std::cin;
// using std::ifstream;
using std::string;
// using std::istream_iterator;
// using std::vector;
// using std::endl;
// using std::cerr;
using namespace std;
using std::istream_iterator;

string keywords[] = {"let", "for", "if"};
string getString(char x)
{
    // string class has a constructor
    // that allows us to specify size of
    // string as first parameter and character
    // to be filled in given size as second
    // parameter.
    string s(1, x);

    return s;
}

void printVectorTest(std::vector<string> const &input)
{
    for (std::vector<string>::size_type i = 0; i < input.size(); i++)
    {
        std::cout << input.at(i) << endl;
    }
    std::cout << std::endl;
}

void lexer(vector<string> fileContents, std::vector<std::string> &tokens)
{
    bool commentStarted = false;

    for (std::vector<string>::size_type i = 0; i < fileContents.size(); i++)
    {
        string temp = fileContents.at(i);

        string token = "";

        string expression = "";
        bool isExpression = false;

        string str = "";

        string variable = "";
        string loopExpression = "";
        bool variableStarted = false;

        bool state = 0;
        bool isString = 0;

        bool functionStarted = false;
        bool methodStarted = false;

        bool forLoopStarted = false;
        bool loopExpressionBool = false;
        bool forLoopBody = false;
        string loopBody = "";

        //std::vector<std::string> x = split(temp, ' ');
        // break fileContents into chars
        vector<char> v(temp.begin(), temp.end());
        for (std::vector<char>::size_type i = 0; i < v.size(); i++)
        {
            token = token + v.at(i);
            //            cout << token << endl;

            // comments started
            if (i + 1 < v.size())
            {
                if (token == "/" && getString(v.at(i + 1)) == "*")
                {
                    commentStarted = true;
                    break;
                }
                else if (commentStarted == true && token != "*" && getString(v.at(i + 1)) != "/")
                {
                    break;
                }
                else if (commentStarted == true && token == "*" && getString(v.at(i + 1)) == "/")
                {
                    commentStarted = false;
                    i = i + 2;
                    continue;
                }
            }
            // comment are a hash sybmol
            if (token == "#")
            {
                break;
            }

            if (token == " ")
            {
                // we remove any spaces that is not part of a string
                if (state == false)
                {
                    token = "";
                }
                else
                {
                    token = " ";
                }
            }
            else if ((token == "\n") || (token == "<EOL>"))
            {
                // we check if we are at the end of the line
                // if we have items in expression then we know it's an expression
                if (expression != "" && isExpression == true)
                {
                    tokens.push_back("EXPR:" + expression);
                    // reset expression
                    expression = "";
                }
                else if (expression != "" && isExpression == false)
                {
                    // if we have items in expression then we know it's a number
                    // printToScreen("here:" + expression);
                    tokens.push_back("NUM:" + expression);
                    // reset expression
                    expression = "";
                }
                else if (variable != "")
                {
                    tokens.push_back("VAR:" + variable);
                    // reset variable
                    variable = "";
                    variableStarted = false;
                }
                // reset token
                token = "";
            }
            else if (token == "$" && state == false)
            {
                // start variable
                variableStarted = true;
                variable = variable + token;
                token = "";
            }
            else if (token == "for" && state == false)
            {
                // start for loop
                //cout << "right here";
                forLoopStarted = true;
                state = true;
                token = "";
            }
            else if (token == "(" && forLoopStarted == true)
            {
                cout << "right here" << endl;
                loopExpressionBool = true;
                token = "";
                continue;
            }
            else if (token == ")" && forLoopStarted == true && loopExpressionBool == true)
            {
                cout << "right here again" << endl;
                tokens.push_back("FOR:" + loopExpression);
                token = "";
                loopExpressionBool = false;
                continue;
            }

            else if (forLoopStarted == true && loopExpressionBool == true)
            {
                //cout << token << endl;
                loopExpression.append(token);
                token = "";
                //loopExpressionBool = false;
            }
            // else if (token == "{" && forLoopStarted == true)
            // {
            //     tokens.push_back("FORBODYBEGIN:");
            //     forLoopBody = true;
            //     token = "";
            // }
            // else if (token == "}" && forLoopStarted == true && forLoopBody == true)
            // {
            //     tokens.push_back("FORBODYEND:" + loopBody);
            //     token = "";
            //     forLoopStarted = false;
            //     forLoopBody = false;
            // }
            // else if (forLoopStarted == true && forLoopBody == true)
            // {
            //     loopBody.append(token);
            //     token = "";
            // }

            else if (token == "=" and state == false)
            {
                if (expression != "" && isExpression == false)
                {

                    tokens.push_back("NUM:" + expression);
                    // reset expression
                    expression = "";
                }
                if (variable != "")
                {
                    tokens.push_back("VAR:" + variable);
                    variable = "";
                    variableStarted = false;
                }
                //printToScreen("hhhh" + tokens.at(i = 1));

                if (tokens.size() > 2)
                {
                    // printToScreen( "-------" + v.at(5));
                    //printToScreen(v.at(i - 1));

                    if (tokens.at(tokens.size() - 1) == "EQUALS:")
                    {
                        tokens.at(tokens.size() - 1) = "EQEQ:";
                    }
                    else
                    {
                        tokens.push_back("EQUALS:");
                    }
                }
                else
                {
                    tokens.push_back("EQUALS:");
                }

                token = "";
            }
            else if ((token == "0") || (token == "1") || (token == "2") ||
                     (token == "3") || (token == "4") || (token == "5") ||
                     (token == "6") || (token == "7") || (token == "8") || (token == "9"))
            {
                // do not use regex in lexer
                // add token to expression
                expression = expression + token;

                //  cout << "here" + expression << endl;

                // reset token
                token = "";
            }
            else if (variableStarted == true)
            {
                if ((token == "<") || (token == ">"))
                {
                    if (variable != "")
                    {
                        tokens.push_back("VAR:" + variable);
                        variable = "";
                        variableStarted = false;
                    }
                }

                variable = variable + token;
                token = "";
            }
            else if (methodStarted == true && token == "length()")
            {
                string str = tokens.at(tokens.size() - 1);
                tokens.at(tokens.size() - 1) = "METHOD:GETLENGTH:" + str;
                token = "";
                methodStarted = false;
            }
            else if (methodStarted == true && token == "uppercase()")
            {
                string str = tokens.at(tokens.size() - 1);
                tokens.at(tokens.size() - 1) = "METHOD:UPPERCASE:" + str;
                token = "";
                methodStarted = false;
            }
            else if (methodStarted == true && token == "lowercase()")
            {
                string str = tokens.at(tokens.size() - 1);
                tokens.at(tokens.size() - 1) = "METHOD:LOWERCASE:" + str;
                token = "";
                methodStarted = false;
            }
            else if (methodStarted == true && token == "trim()")
            {
                string str = tokens.at(tokens.size() - 1);
                tokens.at(tokens.size() - 1) = "METHOD:TRIM:" + str;
                token = "";
                methodStarted = false;
            }
            else if (methodStarted == true && token == "isNumber()")
            {

                string str = tokens.at(tokens.size() - 1);
                tokens.at(tokens.size() - 1) = "METHOD:ISNUMBER:" + str;
                token = "";
                methodStarted = false;
            }
            /*
            else if(token == "(" && methodStarted == false){
                // function started
                string temp;
                
                temp = tokens.at(tokens.size() - 1);
                
                tokens.at(tokens.size() - 1) = "FUNCTION:" + temp;
                
                tokens.push_back("FUNCTION_START");
                token = "";
                functionStarted = true;
                
            } */
            else if (functionStarted == true && token == ")")
            {
                // function ended
                functionStarted = false;
                // push number inside
                if (expression != "" && isExpression == false)
                {

                    tokens.push_back("NUM:" + expression);
                    // reset expression
                    expression = "";
                }

                tokens.push_back("FUNCTION_END");
                token = "";
                state = false;
            }
            else if (token == "\n")
            {
                // if(expression != "" && isExpression == 1){
                //     tokens.push_back("EXPR:" + expression);
                //     expression = "";
                // }tokens
                // token = "";
            }
            else if (token == "print")
            {
                //string j = combineItemsInVector(v, i + 2);
                //sybmols["PRINT STRING"] = j;
                tokens.push_back("PRINT");
                token = "";
            }
            else if ((token == "true") || (token == "false"))
            {
                tokens.push_back("BOOLEAN:" + token);
                token = "";
            }
            else if ((token == "ENDIF") || (token == "endif"))
            {
                tokens.push_back("ENDIF");
                token = "";
            }
            else if ((token == "if") || (token == "IF"))
            {
                tokens.push_back("IF");
                token = "";
            }
            else if ((token == "THEN") || (token == "then"))
            {

                if (expression != "" && isExpression == false)
                {
                    tokens.push_back("NUM:" + expression);
                    expression = "";
                }

                tokens.push_back("THEN");
                token = "";
            }
            else if ((token == "INPUT") || (token == "input"))
            {
                tokens.push_back("INPUT");
                token = "";
            }
            else if (token == "getType")
            {
                tokens.push_back("GETTYPE:");

                // start the state
                // state = true;

                token = "";
            }
            else if ((token == "+") || (token == "-") || (token == "/") || (token == "*") || (token == "(") || (token == ")"))
            {
                // set isExpression to true so we can use later
                isExpression = 1;
                // add token to expression
                expression = expression + token;
                // reset token
                token = "";
            }
            else if ((token == "\"") || (token == " \""))
            {
                // comparing a space before a quote or no quote before a quote
                if (state == false)
                {
                    state = true;
                }
                else if (state == true)
                {
                    if (!expression.empty())
                    {
                        str = str + expression;
                    }

                    tokens.push_back("STRING:" + str + "\"");
                    str = "";

                    //method started
                    if (i + 1 <= v.size())
                    {
                        if (v.at(i + 1) == '.')
                        {
                            methodStarted = true;
                            i = i + 1;
                        }
                    }

                    state = false;
                    token = "";
                }
            }
            else if (state == true)
            {
                // we continue to add to string
                str = str + token;
                token = "";
            }
        }
    }
}