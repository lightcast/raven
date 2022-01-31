using std::string;

std::string getDataType(string str){
    std::string result;
     if (str.substr(0, 7) == "STRING:") {
         result = "string";
    } else if (str.substr(0, 4) == "NUM:") {
        result = "number";        
    } else if (str.substr(0, 8) == "BOOLEAN:") {
        result = "boolean";
    }
    return result;
}