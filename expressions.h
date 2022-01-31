#include<iostream>
#include<fstream>
#include <vector>

#include <iterator>
#include <algorithm>
#include <map>
#include <string>
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



class Stack
{
    private:
        vector<string> stack; 

    public:
        int size;
      
      void push(std::string item){
          //if(stack.length < size){
            stack.push_back(item);
          //}
      }

      std::string pop(){
          string result = "-1";
          if(stack.size() != 0){
            result = stack.back();
            stack.pop_back();
          }
          return result;
        }

      void display(){
          if(stack.size() == 0){
            //console.log("Stack is empty!");
          }else{
          /* console.log("Stack data:");
            let arry = this.stack.reverse();
            for(let item in arry){
              item = arry[item]
            }*/
          }
        }

      bool isEmpty(){
          return stack.empty();
        }

        std::string topChar(){
          std::string result = "-1";

          if(!stack.empty()){
            result = stack.back();
          }
          return result;
        }

};

 






//#include "printing.h"
std::string operators[] = {"+", "-", "*", "/", "^"};

bool isOperand(std::string str){
  /*if((str == "0") || (str == "1") || (str == "2") ||
     (str == "3") || (str == "4") || (str == "5") ||
     (str == "6") || (str == "7") || (str == "8") || (str == "9")){
    return true;
  }
  return false; */



    std::string::const_iterator it = str.begin();
    while (it != str.end() && std::isdigit(*it)) ++it;
    return !str.empty() && it == str.end();
}


bool isOperator(std::string str){
    if((str == "+") || (str == "-") || (str == "/") || (str == "*") || (str == "%")){
        return true;
    }
    return false;
}

template<size_t N>
bool existsInArray(std::string (&arr)[N], std::string x)
{
    //std::cout << std::end(arr) - std::begin(arr);
    bool exists = std::find(std::begin(arr), std::end(arr), x) != std::end(arr);
    return exists;
}



int getPrecedence(std::string c){
    int result = 0;
    std::string str[] = {"-", "/"};

    for( unsigned int num = 0; num < sizeof(operators)/sizeof(operators[0]); num = num + 1 ){
        std::string temp = operators[num];
        result += 1;

        if(temp == c){
            bool exists = existsInArray(str, c );
            if(exists == true){
                result -= 1;
            }
            break;
        }
    }
    return result;
}




void printVector2(std::vector<string> const &input)
{
	for (std::vector<string>::size_type i = 0; i < input.size(); i++) {
	    std::cout << input.at(i) << endl;
    }
    std::cout << std::endl;
}


void pv(std::vector<string> const &input)
{
	for (std::vector<string>::size_type i = 0; i < input.size(); i++) {
	    std::cout << input.at(i) << endl;
    }
    std::cout << std::endl;
}





vector<string> toPostFix(string expr){
     vector<string> strVector;
     string result;
     Stack stack; // = new Stack(15);
     string cpop;
     string str;

    string numTemp; 
    // cout << "HERE" +  expr << endl;
     vector<char> v(expr.begin(), expr.end());
     int size = v.size();
     for (std::vector<char>::size_type i = 0; i < size; i++) {
        str = v.at(i);
        if(str == " "){
            continue;
        }
       
      //  cout << str << endl;
     if(isOperand(str)){
         result += str;
        if(str != " "){
          numTemp += str;
        }
         
     }else if( isOperator(str) ){


      


         while(true){
             std::string topChar = stack.topChar();
            // cout << "topchar" << topChar << endl;
            // cout << str<<endl;
             //cout << result << endl;
             if( (stack.isEmpty()) || (topChar == "(") ){
                 stack.push(str);
               // if(strVector.empty()){
                    strVector.push_back(numTemp);
                    numTemp = "";
                //}
               
                 break;
             }else{

                int pC = getPrecedence(str);
                int pTC = getPrecedence(topChar);

                if(pC > pTC){
                    stack.push(str);
                    if(!numTemp.empty()){
                      strVector.push_back(numTemp);
                      numTemp = "";

                    }
                    break;
                }else{
                    if(!numTemp.empty()){
                      strVector.push_back(numTemp);
                      numTemp = "";

                    }

                    std::string temp = stack.pop();
                    strVector.push_back(temp);
                    result += temp;
                    
                }
             }
         }
    } else if(str == "("){
        stack.push(str);
    } else if(str == ")"){
        cpop = stack.pop();
         strVector.push_back(numTemp);
         numTemp = "";

        while(cpop != "("){
          result += cpop;
          strVector.push_back(cpop);
         cpop = stack.pop();
       } 
    }     
        
    }

    //if(!numTemp.isEmpty()){
      strVector.push_back(numTemp);
   // }

 while(!stack.isEmpty()){
    cpop = stack.pop();
    result += cpop;
    strVector.push_back(cpop);
  }

  //cout << "hhhh" <<endl;
  //printVector2(strVector);

//cout << result <<endl;
  //return result;

  return strVector;
}




//shuntingYard

int evalExpression(std::string expression) {
  //expression = toPostFix(expression);
     vector<string> strVector = toPostFix(expression);
//  cout << "help.." << expression <<endl;

    Stack stack; // = new Stack(15);
    int result = 0;
    std::string str;

    //vector<char> v(expression.begin(), expression.end());
    
     //int size = v.size();
     //for (std::vector<char>::size_type i = 0; i < size; i++) {
    for (std::vector<string>::size_type i = 0; i < strVector.size(); i++) {
        //str = v.at(i);
        str = strVector.at(i);
      //  cout << "str" << str <<endl;
        std::string rightOperand;
        std::string leftOperand;
    

    if(isOperand(str)){
     // cout << "he " << endl;
      stack.push(str);
    }else if(isOperator(str)){
      if(!stack.isEmpty()){
        rightOperand = stack.pop();
      }
      
      if(!stack.isEmpty()){
        leftOperand = stack.pop();
      }
     // cout << "right" << rightOperand <<endl;
      //cout << "left" << leftOperand <<endl;
      if(!rightOperand.empty() && !leftOperand.empty()){

        if(!str.empty()){
            if(str == "+"){
                result = stoi(leftOperand) + stoi(rightOperand);
            }else if(str == "-") {
                result = stoi(leftOperand) - stoi(rightOperand);
            }else if(str == "*") {
               result = stoi(leftOperand) * stoi(rightOperand);
            }else if(str == "/") {
                result = stoi(leftOperand) / stoi(rightOperand);
            }else if(str == "^") {
                result = stoi(leftOperand) * stoi(rightOperand);
            }else if(str == "%") {
               result = stoi(leftOperand) % stoi(rightOperand);
            }
        }
        stack.push(std::to_string(result));
      }
    }
  }

  return result;
}