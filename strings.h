
#include<iostream>
#include<fstream>
#include <vector>

#include <iterator>
#include <algorithm>
#include <map>
#include <cctype>
#include <locale>

using std::string;
using namespace std;

std::string getCharsInString(std::string str){
    std::string results;
    for(unsigned i = 0; i < str.length(); i++){
        results.at(i);
    }
    return results;
}















// TO DO:

// https://www.w3schools.com/python/ref_string_replace.asp

std::string stringReplace(std::string str) {
    // /std::string results;
    transform(str.begin(), str.end(), str.begin(), ::tolower); 
    return str;
}


// https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/String/concat
std::string stringConcat(std::string str) {
    // /std::string results;
    transform(str.begin(), str.end(), str.begin(), ::tolower); 
    return str;
}


// https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/String/substr
std::string stringSubString(std::string str) {
  return str;  
}



std::string stringFind(std::string str) {
  return str;  
}
