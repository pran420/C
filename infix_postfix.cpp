#include <bits/stdc++.h>
using namespace std;

string associativityOfOperator(char op)
{ // op:operator
    if (op == '^')
        return "RIGHT";
    return "LEFT";
}

int precedenceOfChar(char ch)
{ // ch:character
    if (ch == '^')
        return 4;
    else if (ch == '*' || ch == '/')
        return 3;
    else if (ch == '-' || ch == '+')
        return 2;
    else
        return 1;
}

void inToPostfixConvertor(string infix)
{
    stack<char> stac;
    string postfix;

    for (int j = 0; j < infix.length(); j++)
    {
        char ch = infix[j];

        if ((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
        {
            postfix = postfix + ch;
        }
        else if (ch == '(')
            stac.push('(');

        else if (ch == ')')
        {
            while (stac.top() != '(')
            {
                postfix = postfix + stac.top();
                stac.pop();
            }
            stac.pop();
        }

        else
        {
            while (!stac.empty() && precedenceOfChar(infix[j]) == precedenceOfChar(stac.top()) ||
                   !stac.empty() && precedenceOfChar(infix[j]) < precedenceOfChar(stac.top()) &&
                    associativityOfOperator(infix[j]) == "LEFT")
            {
                postfix = postfix + stac.top();
                stac.pop();
            }
            stac.push(ch);
        }
    }

    while (!stac.empty())
    {
        postfix = postfix + stac.top();
        stac.pop();
    }

    cout << endl
         << "Postfix : " << postfix << endl
         << endl;
}

int main()
{
    string expression;
    cout << "Enter the expression you want to convert from infix to postfix" << endl;
    cin >> expression;

    inToPostfixConvertor(expression);

    return 0;
}
