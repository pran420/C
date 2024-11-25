#include <iostream>
#include <vector>
#include <cctype>
#include <string>

using namespace std;

bool is_Operator_or_not(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '=';
}

bool is_ValidIdentifier_or_not(const string &strings)
{
    if (strings.empty())
        return false;

    if (!isalpha(strings[0]) && strings[0] != '_')
        return false;

    for (char ch : strings)
    {
        if (!isalnum(ch) && ch != '_')
            return false;
    }

    return true;
}

bool extract_Identifiers_And_Operators(const string &expressions, vector<string> &identifier, vector<char> &operators)
{
    string currIdentifier = "";
    bool expect_Operator = false;

    for (size_t i = 0; i < expressions.length(); ++i)
    {
        char ch = expressions[i];

        if (isspace(ch))
        {
            continue;
        }

        if (is_Operator_or_not(ch))
        {
            if (!expect_Operator)
            {
                return false;
            }
            operators.push_back(ch);
            expect_Operator = false;
        }
        else if (ch == '_' || isalnum(ch))
        {
            currIdentifier += ch;

            if (i == expressions.length() - 1 || is_Operator_or_not(expressions[i + 1]) || isspace(expressions[i + 1]))
            {
                if (is_ValidIdentifier_or_not(currIdentifier))
                {
                    identifier.push_back(currIdentifier);
                    currIdentifier = "";
                    expect_Operator = true;
                }
                else
                {
                    return false;
                }
            }
        }
        else
        {
            return false;
        }
    }

    return expect_Operator;
}

int main()
{
    string expression;

    cout << "Enter arithmetic expression  to be validated : ";
  
    cin >> expression;

    vector<string> identifiers;
    vector<char> operators;

    if (extract_Identifiers_And_Operators(expression, identifiers, operators))
    {
        cout << "The entered arithmetic expression is valid" << endl;

        cout << "Identifiers: ";
        for (const string &id : identifiers)
        {
            cout << id << " ";
        }
        cout << endl;

        cout << "Operators: ";
        for (char op : operators)
        {
            cout << op << " ";
        }
        cout << endl;
    }
    else
    {
        cout << "The entered arithmetic expression is invalid" << endl;
    }

    return 0;
}
