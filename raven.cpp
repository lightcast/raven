// <a href="https://www.flaticon.com/free-icons/crow" title="crow icons">Crow icons created by Freepik - Flaticon</a>

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

#include "lexer.h"
#include "parser.h"

//#include <cassert>

//#include <ncurses.h>

//#include "array.h"

//using std::array;

//#define KEY_UP 72
//#define KEY_DOWN 80
//#define KEY_LEFT 75
//#define KEY_RIGHT 77

std::vector<std::string> tokens;
std::map<std::string, std::string> sybmols;

std::vector<std::string> commandLineHistory;

std::vector<std::string> split(const std::string &text, char delim)
{
    std::vector<std::string> elems;
    std::size_t start = 0, end = 0;
    while ((end = text.find(delim, start)) != std::string::npos)
    {
        elems.push_back(text.substr(start, end - start));
        start = end + 1;
    }
    elems.push_back(text.substr(start));
    return elems;
}

vector<string> readLine(string line)
{
    vector<string> vector;
    string eol = "<EOL>";
    vector.push_back(line + eol);

    return vector;
}

void printVariables(std::map<std::string, std::string> sybmols)
{
    //    for (auto elem : &sybmols) {
    //        std::cout << elem.first << " " << elem.second <<"\n";
    //    }

    // show content:
    for (std::map<std::string, std::string>::iterator it = sybmols.begin(); it != sybmols.end(); ++it)
        std::cout << it->first << " => " << it->second << '\n';
}

vector<string> readFile(string fileName)
{
    ifstream inFile;
    inFile.open(fileName);
    if (!inFile)
    {
        cerr << "Unable to open file";
        exit(1);
    }

    string result = "";
    string x;
    vector<string> DataArray;
    vector<string> vector;

    string line;
    if (inFile.is_open())
    {
        while (std::getline(inFile, line))
        {
            // std::cout << line << std::endl;
            string eol = "<EOL>";
            vector.push_back(line + eol);
        }

        copy(std::istream_iterator<string>(inFile),
             std::istream_iterator<string>(),
             std::back_inserter(DataArray));

        inFile.close();
    }
    return vector;
}

std::string combineItemsInVector(std::vector<char> vec, int startPosition)
{
    std::string results;
    for (size_t i = startPosition; i != vec.size(); i++)
    {
        results = results + vec[i];
    }
    std::cout << results << endl;
    return results;
}

int main(int argc, char *argv[])
{
    // if we don't have agrs go into interpreter mode
    if (argc < 2)
    {
        string command;
        cout << "Raven 0.1 (default, Mar 27 2019, 16:54:48)" << endl;
        cout << "Type \"help\", for more information." << endl;

        bool exit = false;
        int keyArrow = 0;

        while (exit == false)
        {
            cout << ">>> ";
            keyArrow = 0;
            std::getline(std::cin, command);
            commandLineHistory.push_back(command);

            if (!command.compare("exit"))
            {
                cout << "exit";
                exit = true;
            }
            else if (!command.compare("help"))
            {

                cout << "help" << endl;
                tokens.clear();
            }
            else if (!command.compare("clearVars"))
            {
                tokens.clear();
                sybmols.clear();
            }
            else if (!command.compare("printVars"))
            {
                printVariables(sybmols);
                tokens.clear();
            }
            else
            {
                try
                {

                    vector<string> fileContents = readLine(command);
                    lexer(fileContents, tokens);
                    parser(tokens, sybmols);
                    //cout << ">>> " ;
                    //std::getline (std::cin,command);
                    tokens.clear();
                    //sybmols.clear();
                }
                catch (...)
                {
                    cout << "Exception caught\n";
                    tokens.clear();
                    // cout << ">>> " ;
                    //std::getline (std::cin,command);
                }
            }

            // names.push_back(name);
            // weights.push_back(weight);
            //         cin >> name;
        }
    }
    else
    {
        string fn = argv[1];
        //  printToScreen(fn);
        // printToScreen(fn.substr(fn.find_last_of(".") + 1));
        if (fn.substr(fn.find_last_of(".") + 1) != "rvn")
        {
            printToScreen("Unkown file type. Programs written in raven must have a .rvn extension.");
            return 0;
        }

        vector<string> fileContents = readFile(fn);

        lexer(fileContents, tokens);
        parser(tokens, sybmols);
        printVector(tokens);
    }

    return 0;
}
