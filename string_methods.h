#include<iostream>
#include<fstream>
#include <vector>


//#include "strings.h"

using namespace std;

std::string setStringToUppercase(std::string str) {
    // /std::string results;
    transform(str.begin(), str.end(), str.begin(), ::toupper); 
    return str;
}


std::string setStringLowercase(std::string str) {
    // /std::string results;
    transform(str.begin(), str.end(), str.begin(), ::tolower); 
    return str;
}



int getStringLength(std::string str){
    return str.length();
}


inline std::string& leftTrim(std::string& str, const char* t) {
str.erase(0, str.find_first_not_of(t));
return str;
}


inline std::string& rightTrim(std::string& str, const char* t) {
str.erase(str.find_last_not_of(t) + 1);
return str;
}



inline std::string& stringToTrim(std::string& str){

const char* ws = " \t\n\r\f\v";
cout << "here" << endl;
return leftTrim(rightTrim(str, ws), ws);
}



bool stringIsNumnber(std::string s) {
    return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);

  int i;
  char str[]="c3po...";
  i=0;
  while (isalnum(str[i])) i++;
  printf ("The first %d characters are alphanumeric.\n",i);
  return 0;

}


bool isString(){
    int i=0;
  char str[]="C++";
  while (str[i])
  {
    if (isalpha(str[i])) printf ("character %c is alphabetic\n",str[i]);
    else printf ("character %c is not alphabetic\n",str[i]);
    i++;
  }
}


inline const char * const BooleanToString(bool b)
{
  return b ? "true" : "false";
}


std::string stringMethods(std::string str){
    if (str.substr(0, 7) == "METHOD:") {
        string value = str.substr(7);  
        if(value.substr(0, 10) == "UPPERCASE:") {
            value = value.substr(10);
            if (value.substr(0, 7) == "STRING:") {
                // we remove the token but here we put it back
                value = "STRING:" + setStringToUppercase(value.substr(7));
                return value;
            }
        } else if (value.substr(0, 10) == "GETLENGTH:") {
            value = value.substr(10);
            if (value.substr(0, 7) == "STRING:") {
                // we remove the token but here we put it back
                value =  value = "NUM:" + std::to_string(getStringLength(value.substr(7)));
                return value;
            }   
        } else if(value.substr(0, 10) == "LOWERCASE:") {
                value = value.substr(10);
            if (value.substr(0, 7) == "STRING:") {
                // we remove the token but here we put it back
                value =  value = "STRING:" + setStringLowercase(value.substr(7));
                return value;
            }
        } else if(value.substr(0, 5) == "TRIM:") {
            value = value.substr(5);
            if (value.substr(0,7) == "STRING:") {
                value = value.substr(7);
                // we remove the token but here we put it back
                value = "STRING:" + stringToTrim(value);
                return value;
                                    
            }
        } else if(value.substr(0, 9) == "ISNUMBER:") {
            value = value.substr(9);
             cout << value << endl;
            if (value.substr(0,7) == "STRING:") {
                value = value.substr(7);
                cout << value << endl;
                string str = BooleanToString(stringIsNumnber(value));
                // we remove the token but here we put it back
                value = "BOOLEAN:" + str;
                return value;
            }
        } 
    }
    return std::string();
}