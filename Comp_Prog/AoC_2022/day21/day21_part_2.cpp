#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <map>
#include <iomanip>
using namespace std;

class Equation
{

public:
    string operand_1;
    string operand_2;
    string operation;
    long double number = -1;
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
    Equation(long double number)
    {
        this->number = number;
        is_number = true;
    }
    string display()
    {
        if (is_number)
        {
            return to_string(number);
        }
        else
        {
            return operand_1 + " " + operation + " " + operand_2;
        }
    }
};

bool is_ancestor(map<string, Equation> equations, string key1, string key2)
{
    if (key1 == key2)
    {
        return true;
    }
    else
    {
        if (equations[key2].is_number)
        {
            return false;
        }
        return is_ancestor(equations, key1, equations[key2].operand_1) || is_ancestor(equations, key1, equations[key2].operand_2);
    }
}
long double back_track(map<string, Equation> equations, long double value, string key);
long double solve(map<string, Equation> equations, string key)
{
    Equation eq = equations[key];
    if (eq.is_number)
    {
        return eq.number;
    }
    else
    {
        long double op1 = solve(equations, eq.operand_1);
        long double op2 = solve(equations, eq.operand_2);
        if (eq.operation == "+")
        {
            return op1 + op2;
        }
        else if (eq.operation == "*")
        {
            return op1 * op2;
        }
        else if (eq.operation == "/")
        {
            return op1 / op2;
        }
        else if (eq.operation == "-")
        {
            return op1 - op2;
        }
        else if (eq.operation == "=")
        {
            cout << "op1: " << op1 << " op2: " << op2 << endl;
            if(is_ancestor(equations, "humn", eq.operand_1))
            {
                back_track(equations, op2, eq.operand_1);
            }
            else
            {
                back_track(equations, op1, eq.operand_2);
            }
            return op1 == op2;
        }
        else
        {
            cout << "ERROR" << endl;
            exit(1);
        }
    }
    return 0;
}

string get_inverse(string operation)
{
    if (operation == "+")
    {
        return "-";
    }
    else if (operation == "-")
    {
        return "+";
    }
    else if (operation == "*")
    {
        return "/";
    }
    else if (operation == "/")
    {
        return "*";
    }
    else
    {
        cout << "ERROR" << endl;
        exit(1);
    }
}

long double back_track(map<string, Equation> equations, long double value, string key)
{
    if (equations[key].is_number)
    {
        if (key == "humn")
        {
            std::cout << std::setprecision(16);
            cout << "humn should be : " << value << endl;
            return value;
        }
    }
    else
    {
        
        string op1 = equations[key].operand_1;
        string op2 = equations[key].operand_2;
        string operation = equations[key].operation;
        string inverse_op = get_inverse(operation);
        if(is_ancestor(equations, "humn",op1))
        {
            long double value_to_pass = 0 ; 
            if(inverse_op == "+")
            {
                value_to_pass = value + solve(equations,op2);
            }
            else if(inverse_op == "-")
            {
                value_to_pass = value - solve(equations,op2);
            }
            else if(inverse_op == "*")
            {
                value_to_pass = value * solve(equations,op2);
            }
            else if(inverse_op == "/")
            {
               // cout<<"float check : "<<( value% solve(equations,op2) == 0)<<endl;
                value_to_pass = value / solve(equations,op2);
            }
            else
            {
                cout << "ERROR" << endl;
                exit(1);
            }
            cout<< "key: " << op1 << " value: " << value_to_pass << endl;
           return  back_track(equations, value_to_pass, op1);
        }
        else
        {
            long double value_to_pass = 0 ; 
            if(inverse_op == "+")
            {
                value_to_pass = value + solve(equations,op1);
            }
            else if(inverse_op == "-")
            {
                value_to_pass = value - solve(equations,op1);
            }
            else if(inverse_op == "*")
            {
                value_to_pass = value * solve(equations,op1);
            }
            else if(inverse_op == "/")
            {
                //cout<<"float check : "<<( value % solve(equations,op1) == 0)<<endl;
                value_to_pass = value / solve(equations,op1);
            }
            else
            {
                cout << "ERROR" << endl;
                exit(1);
            }
            cout<< "key: " << op2 << " value: " << value_to_pass << endl;
            return back_track(equations, value_to_pass, op2);
        }
    }
}


int main()
{

    // read lines and tokensize them
    ifstream file("smolinput.txt");
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
            long double number = stoll(tokens[1]);
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
    long double answer = solve(equations, "root");
    //cout << answer << endl;
    return 0;
}