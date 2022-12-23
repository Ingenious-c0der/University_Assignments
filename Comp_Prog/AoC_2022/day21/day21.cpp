#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <map>
using namespace std;

class Equation
{
 
 public:
    string operand_1;
    string operand_2;
    string operation;
    long long number = -1;
    bool is_number = false;


    Equation(string op1, string op2, string op)
    {
        operand_1 = op1;
        operand_2 = op2;
        operation = op;
    }
    Equation()
    {
    }
    Equation(long long number)
    {
        this->number = number;
        is_number = true;
    }
    string display()
    {
        if (is_number)
        {
            return  to_string(number);
        }
        else
        {
           return operand_1 + " " + operation + " " + operand_2;
        }
    }
};


long long solve(map<string, Equation> equations , string key)
{
    Equation eq = equations[key];
    if(eq.is_number)
    {
        return eq.number;
    }
    else
    {
        long long op1 = solve(equations, eq.operand_1);
        long long op2 = solve(equations, eq.operand_2);
        if(eq.operation == "+")
        {
            return op1 + op2;
        }
        else if(eq.operation == "*")
        {
            return op1 * op2;
        }
        else if(eq.operation == "/")
        {
            return op1 / op2;
        }
        else if(eq.operation == "-")
        {
            return op1 - op2;
        }
        else
        {
            cout << "ERROR in solve" << endl;
            exit(1);
        }
    }
    return 0;
}


int main()
{

    // read lines and tokensize them
    ifstream file("input.txt");
    map<string, Equation> equations;
    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string token;
        string key = "";
        vector<string> tokens;
        while (getline(ss, token, ' '))
        {
            tokens.push_back(token);
        }
        if (tokens.size() == 2)
        {
            key = tokens[0];
            key.pop_back(); // remove the colon
            long long number = stoll(tokens[1]);
            Equation eq(number);
            equations[key] = eq;
        }
        else if (tokens.size() == 4)
        {
            key = tokens[0];
            key.pop_back(); // remove the colon
            Equation eq(tokens[1], tokens[3], tokens[2]);
            equations[key] = eq;
        }
        else
        {
            cout << "ERROR" << endl;
            exit(1);
        }
    }
    long long answer = solve(equations, "root");
    cout<< answer << endl;
    // cout all the map contents
    // for (auto i : equations)
    // {
    //     cout << i.first << " "<< i.second.display()  << endl;
    // }

    return 0;
}