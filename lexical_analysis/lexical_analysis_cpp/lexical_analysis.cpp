#include <iostream>  
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <regex>
#include <algorithm>

using namespace std;

map<string, vector<string>> classifyTokens(const string &inputLine)
{
    
    set<string> keywords = {"if", "else", "int", "float", "return", "for", "while", "do", "switch", "case"};
    set<string> arithmeticOperators = {"+", "-", "*", "/", "="};
    set<string> logicalOperators = {">", ">=", "<", "<=", "==", "!="};
    set<string> punctuation = {";", ":", ","};
    set<string> parentheses = {"(", ")", "{", "}", "[", "]"};

    // Regex patterns
    regex identifierPattern("^[a-zA-Z_][a-zA-Z0-9_]*$");
    regex constantPattern("^[-+]?[0-9]*\\.?[0-9]+$");


    // Tokenize the input
    vector<string> tokens; 
    stringstream ss(inputLine); 
    string token;
    while (ss >> token)
    {
        tokens.push_back(token); 
    }

    // Classify tokens
    map<string, vector<string>> classifiedTokens;

    for (const string &token : tokens)
    {
        if (keywords.count(token))
        {
            classifiedTokens["Keyword"].push_back(token);
        }
        else if (arithmeticOperators.count(token))
        {
            classifiedTokens["Arithmetic Operator"].push_back(token);
        }
        else if (logicalOperators.count(token))
        {
            classifiedTokens["Logical Operator"].push_back(token);
        }
        else if (punctuation.count(token))
        {
            classifiedTokens["Punctuation"].push_back(token);
        }
        else if (parentheses.count(token))
        {
            classifiedTokens["Parenthesis"].push_back(token);
        }
        else if (regex_match(token, constantPattern))
        {
            classifiedTokens["Constant"].push_back(token);
        }
        else if (regex_match(token, identifierPattern))
        {
            classifiedTokens["Identifier"].push_back(token);
        }
    }

    return classifiedTokens;
}

// Function to format output
void formatOutput(const map<string, vector<string>> &classifiedTokens)
{
    for (const auto &pair : classifiedTokens)
    {
        const string &category = pair.first;
        const vector<string> &tokens = pair.second;

        set<string> uniqueTokens(tokens.begin(), tokens.end());

        cout << category << " (" << uniqueTokens.size() << "): ";
        for (const string &token : uniqueTokens)
        {
            cout << token << ", ";
        }
        cout << endl;
    }
}

int main()
{
    cout << "Enter '1' for console input or '2' for file input: ";
    int choice;
    cin >> choice;
    cin.ignore(); // Clear the input buffer

    string inputLine;

    if (choice == 1)
    {
        cout << "Enter a line of code: ";
        getline(cin, inputLine);
    }
    else if (choice == 2)
    {
        cout << "Enter file path: ";
        string filePath;
        cin >> filePath;

        ifstream file(filePath);
        if (!file)
        {
            cerr << "File not found." << endl;
            return 1;
        }

        stringstream buffer;
        buffer << file.rdbuf();
        inputLine = buffer.str();
    }
    else
    {
        cerr << "Invalid choice." << endl;
        return 1;
    }

    map<string, vector<string>> classifiedTokens = classifyTokens(inputLine);
    cout << "\nOutput:\n";
    formatOutput(classifiedTokens);

    return 0;
}


// int ab = { ( bc1 * 12.5 ) / ( 1cd * ( -10 ) } + 11 ;
// int ab = {(bc1*12.5)/(1cd*(-10)}+11;