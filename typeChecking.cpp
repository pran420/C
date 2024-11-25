#include <iostream>
#include <string>
#include <regex>
#include <cctype>
using namespace std;

enum class Type {
    INT,
    FLOAT,
    STRING,
    CHAR,
    BOOLEAN,
    INVALID
};

Type parseType(const string& typeStr) {
    if (typeStr == "int") return Type::INT;
    if (typeStr == "float") return Type::FLOAT;
    if (typeStr == "string") return Type::STRING;
    if (typeStr == "char") return Type::CHAR;
    if (typeStr == "boolean") return Type::BOOLEAN;
    return Type::INVALID;
}

bool isInteger(const string& value) {
    regex intRegex(R"([-+]?[0-9]+)");
    return regex_match(value, intRegex);
}

bool isFloat(const string& value) {
   
    regex floatRegex(R"([-+]?[0-9]*\.[0-9]+([eE][-+]?[0-9]+)?|[-+]?[0-9]+[eE][-+]?[0-9]+)");
    return regex_match(value, floatRegex);
}

bool isChar(const string& value) {
    return value.length() == 1;
}

bool isBoolean(const string& value) {
    return value == "true" || value == "false";
}

bool isValueOfType(const string& value, Type type) {
    switch (type) {
        case Type::INT:
            return isInteger(value);
        case Type::FLOAT:
            return isFloat(value);
        case Type::STRING:
            return true; 
        case Type::CHAR:
            return isChar(value);
        case Type::BOOLEAN:
            return isBoolean(value);
        default:
            return false;
    }
}

int main() {
    string name;

     cout<<"Enter the name of the variable :";
 cin>>name;

    string typeStr, value;
    cout << "Enter the type : ";
    cin >> typeStr;
    cout << "Enter the value: ";
    cin.ignore();  
    getline(cin, value);

  
    Type type = parseType(typeStr);

   
    if (type == Type::INVALID) {
        cout << "Error: Invalid type specified." << endl;
        return 1;
    }

    if (isValueOfType(value, type)) {
        cout << "The variable '" << name << "' is of type " << typeStr  << endl;
    } else {
        cout << " The variable '" << name << "' does not match type " << typeStr << endl;
    }

    return 0;
}
