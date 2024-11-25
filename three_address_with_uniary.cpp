#include <iostream>
#include <stack>
#include <string>
#include <cctype> 

using namespace std;

bool check_isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool isUnaryMinus(const string& exp, int index) {
    return exp[index] == '-' && (index == 0 || exp[index - 1] == '(');
}

int precedenceOfOperator(char opr) {
    if (opr == '/' || opr == '*')
        return 2;
    if (opr == '-' || opr == '+')
        return 1;
    if (opr == '~')  
        return 3;
    return 0;
}

string inToPostConversion(string infixString) {
    stack<char> operatorStack;
    string postfixString = "";

    for (int j = 0; j < infixString.length(); j++) {
        char currentCharacter = infixString[j];

        
        if (isalnum(currentCharacter)) {
            postfixString += currentCharacter;
        }
        
        else if (currentCharacter == '(') {
            operatorStack.push(currentCharacter);
        }
        
        else if (currentCharacter == ')') {
            while (!operatorStack.empty() && operatorStack.top() != '(') {
                postfixString += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.pop(); 
        }
        
        else if (check_isOperator(currentCharacter)) {
            if (isUnaryMinus(infixString, j)) {
                operatorStack.push('~');  
            } else {
               
                while (!operatorStack.empty() && precedenceOfOperator(operatorStack.top()) >= precedenceOfOperator(currentCharacter)) {
                    postfixString += operatorStack.top();
                    operatorStack.pop();
                }
                operatorStack.push(currentCharacter);
            }
        }
    }

    while (!operatorStack.empty()) {
        postfixString += operatorStack.top();
        operatorStack.pop();
    }

    return postfixString;
}

void generateThreeAddressCode(string exp) {
    stack<string> stac;
    int tempVarNum = 1;

    for (int i = 0; i < exp.length(); i++) {
        char currentCharacter = exp[i];

        if (isalnum(currentCharacter)) {
            string operand(1, currentCharacter); 
            stac.push(operand); 
        }
        else if (check_isOperator(currentCharacter) || currentCharacter == '~') {
            string operandNo2, operandNo1;

            if (currentCharacter == '~') { 
                operandNo1 = stac.top(); stac.pop();
                string temp = "t" + to_string(tempVarNum++);
                cout << temp << " = -" << operandNo1 << endl;
                stac.push(temp);
            } else {
                operandNo2 = stac.top(); stac.pop();
                operandNo1 = stac.top(); stac.pop();
                string temp = "t" + to_string(tempVarNum++);
                cout << temp << " = " << operandNo1 << " " << currentCharacter << " " << operandNo2 << endl;
                stac.push(temp);
            }
        }
    }

    cout << "Final result is in: " << stac.top() << endl;
}

int main() {
    string infixExpression, postfixExpression;

    cout << "Enter an arithmetic expression: ";
    cin >> infixExpression;


    postfixExpression = inToPostConversion(infixExpression);

    generateThreeAddressCode(postfixExpression);

    return 0;
}
