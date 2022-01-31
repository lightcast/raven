#include <vector>
#include <map>

using std::string;
using std::istream_iterator;
using std::map;


void printMap(std::map<std::string, std::string> mp){
    for(auto it = mp.cbegin(); it != mp.cend(); ++it){
        std::cout << it->first << " " << it->second <<  "\n";
    }
}


void printToScreen(std::string toPrint){

//cout<< "toprint" << toPrint << endl;


    if (toPrint.substr(0, 7) == "STRING:") {
        toPrint = toPrint.substr(7);
        toPrint = toPrint.substr(1, toPrint.length() - 2);
    } else if (toPrint.substr(0, 4) == "NUM:") {
        toPrint = toPrint.substr(4);
    } else if (toPrint.substr(0, 5) == "EXPR:") {


        toPrint = toPrint.substr(5);


    } else if (toPrint.substr(0, 8)  == "BOOLEAN:") {
        toPrint = toPrint.substr(8, toPrint.size() - 2);
       // printToScreen(str);
    } 
    std::cout << toPrint << endl;
} 


void printToScreen(std::string toPrint,  map<string, string>&sybmols){
 //   cout << toPrint << endl;
    if (toPrint.substr(0, 4) == "VAR:") {
       // printToScreen(getVariable(var, sybmols));
        string var = toPrint.substr(4);
        toPrint = getVariable(var, sybmols);
    }
    std::cout << toPrint << endl;
} 


void printVector(std::vector<string> const &input)
{
	for (std::vector<string>::size_type i = 0; i < input.size(); i++) {
	    std::cout << input.at(i) << endl;
    }
    std::cout << std::endl;
}


