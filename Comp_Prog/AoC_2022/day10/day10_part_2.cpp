#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

int main()
{

    ifstream file("input.txt");
    string line;
    vector<string> tokens;
    int cycle = 0;
    int X = 1;
    int signal_strength = 0;
    int delta = 0;
    int sub = 0;
    vector<char> op_line(40, '.');
    vector<char> crt(40, '.');
    while (getline(file, line))
    {
        stringstream ss(line);
        string token;
        while (getline(ss, token, ' '))
        {
            tokens.push_back(token);
        }
        if (tokens.size() == 2)
        {
            delta = stoi(tokens[1]);
            cycle++;
        }
        else
        {
            cycle++;
        }

        if ((cycle - sub - 1) == X || (cycle - sub - 1) == X - 1 || (cycle - sub - 1) == X + 1)
        {
            op_line[cycle - sub - 1] = '#';
           // cout << cycle - sub << " " << X << " lit" << endl;
        }
        else
        {
           // cout << cycle - sub << " " << X << " dark" << endl;
        }
        // op_line[cycle-sub] = '#' if tokens[0] == "1" else '.';
        if (cycle == 20 || (cycle - 20) % 40 == 0)
        {
            signal_strength += cycle * X;

            // cout << cycle << " " << X << " " << cycle * X << endl;
        }
        if ((cycle - sub) % 40 == 0)
        {
            sub = cycle;
            // PRINT OPLINE
            for (auto i : op_line)
            {
                cout << i;
            }
            cout << endl;
            op_line = crt;
        }
        if (delta != 0)
        {
            cycle++;

            if ((cycle - sub - 1) == X || (cycle - sub - 1) == X - 1 || (cycle - sub - 1) == X + 1)
            {
                op_line[cycle - sub - 1] = '#';
                //cout << cycle - sub << " " << X << " lit" << endl;
            }
            else
            {
               // cout << cycle - sub << " " << X << " dark" << endl;
            }
            if (cycle == 20 || (cycle - 20) % 40 == 0)
            {
               
                signal_strength += cycle * X;
            }

            X += delta;
            if ((cycle - sub) % 40 == 0)
            {
                // cout<<cycle-sub<<endl ;
                // cout<< ((cycle - sub) % 40 == 0) <<endl; 
                // cout<< "here boi"<<endl;
                sub = cycle;
                // PRINT OPLINE
                for (auto i : op_line)
                {
                    cout << i;
                }
                cout << endl;
                
                op_line = crt;
            }
            delta = 0;
        }

        tokens = {};
    }
    cout << cycle << endl;
    cout << signal_strength << endl;

    return 0;
}