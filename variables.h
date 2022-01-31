#include<iostream>
#include<fstream>
#include <vector>

#include <iterator>
#include <algorithm>
#include <map>
// using std::copy;
// using std::cout;
// using std::cin;
// using std::ifstream;
using std::string;
using std::map;
// using std::istream_iterator;
using std::vector;
// using std::endl;
// using std::cerr;
using namespace std;
using std::istream_iterator;


string getVariable(string varName, map<string, string> &sybmols) {
    if (sybmols.find(varName) == sybmols.end()) {
        return "VARIABLE ERROR: Undefined Variable";
    } else {
        string value = sybmols.at(varName);
        return value;
    }    
}





void assignVariable(string varName, string varValue, map<string, string> &sybmols){
    sybmols[varName] = varValue;
}

