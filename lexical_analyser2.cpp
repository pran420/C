#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <cctype>

using namespace std;

const vector<string> c_keywords = {
    "switch", "typedef", "union", "unsigned", "void", "volatile", "while", "class",
    "else", "float", "for", "goto", "if", "inline", "int", "long",
    "auto", "break", "case", "char", "const", "continue", "default", "do", "double",
    "register", "return", "short", "signed", "sizeof", "static", "struct"};

const vector<char> c_separators = {'(', ')', '{', '}', '[', ']', ',', ';', ':'};

const vector<string> operators = {
    "+=", "-=", "*=", "/=", "%=", "&&", "||", "!", "&", "|", "^", "~", "<<", ">>",
    "+", "-", "*", "/", "%", "=", "==", "!=", "<", ">", "<=", ">=", "++", "--"};

bool is_Keyword(const string &inputWord)
{
    return find(c_keywords.begin(), c_keywords.end(), inputWord) != c_keywords.end();
}

bool is_Constant(const string &inputWord)
{
    regex const_Regex("^\\d+(\\.\\d+)?$");
    return regex_match(inputWord, const_Regex);
}

bool is_Identifier(const string &inputWord)
{
    regex id_Regex("^[a-zA-Z_][a-zA-Z0-9_]*$");
    return regex_match(inputWord, id_Regex);
}

bool is_Separator(char c)
{
    return find(c_separators.begin(), c_separators.end(), c) != c_separators.end();
}

bool is_Operator(const string &inputWord)
{
    return find(operators.begin(), operators.end(), inputWord) != operators.end();
}

vector<string> tokenizing(const string &line)
{
    vector<string> tokens;
    string token;

    for (size_t i = 0; i < line.size(); i++)
    {
        char c = line[i];

        if (is_Separator(c))
        {
            if (!token.empty())
            {
                tokens.push_back(token);
                token.clear();
            }
            tokens.push_back(string(1, c));
        }

        else if (ispunct(c) && !is_Separator(c))
        {
            if (!token.empty())
            {
                tokens.push_back(token);
                token.clear();
            }

            string op(1, c);

            if (i + 1 < line.size() && ispunct(line[i + 1]))
            {
                string nextOp = op + line[i + 1];
                if (is_Operator(nextOp))
                {
                    op = nextOp;
                    i++;
                }
            }
            tokens.push_back(op);
        }
        else if (isalnum(c) || c == '_')
        {
            token += c;
        }

        else if (isspace(c))
        {
            if (!token.empty())
            {
                tokens.push_back(token);
                token.clear();
            }
        }
    }

    if (!token.empty())
    {
        tokens.push_back(token);
    }

    return tokens;
}

int main()
{
    string code;
    string line;

    cout << "Enter the code " << endl;

    while (getline(cin, line))
    {
        if (line == "eof")
            break;
        code += line + '\n';
    }

    vector<string> tokens = tokenizing(code);

    int keywordCount = 0, constantCount = 0, identifierCount = 0, separatorCount = 0, operatorCount = 0;

    for (const string &token : tokens)
    {
        if (is_Keyword(token))
        {

            keywordCount++;
        }
        else if (is_Constant(token))
        {

            constantCount++;
        }
        else if (is_Identifier(token))
        {

            identifierCount++;
        }
        else if (token.size() == 1 && is_Separator(token[0]))
        {

            separatorCount++;
        }
        else if (is_Operator(token))
        {

            operatorCount++;
        }
    }
    cout << "\nSummary:\n";
    cout << "Keywords: " << keywordCount << endl;
    cout << "Constants: " << constantCount << endl;
    cout << "Identifiers: " << identifierCount << endl;
    cout << "Separators: " << separatorCount << endl;
    cout << "Operators: " << operatorCount << endl;

    return 0;
}
