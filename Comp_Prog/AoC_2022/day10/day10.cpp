#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

int main()
{

    ifstream file("input.txt");
    // tokenize
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
        cout<< cycle-sub << " " << X << " " << endl;
        if ((cycle - sub) == X || (cycle - sub) == X - 1 || (cycle - sub) == X + 1)
        {
            op_line[cycle - sub] = '#';
        }
        // op_line[cycle-sub] = '#' if tokens[0] == "1" else '.';
        if (cycle == 20 || (cycle - 20) % 40 == 0)
        {
            signal_strength += cycle * X;
            sub = cycle;
            // PRINT OPLINE
            for (auto i : op_line)
            {
                cout << i;
            }
            cout << endl;
            op_line = crt;
            // cout << cycle << " " << X << " " << cycle * X << endl;
        }
        if (delta != 0)
        {
            cycle++;
            cout<< cycle-sub << " " << X << " " << endl;
            if (cycle - sub == X || cycle - sub == X - 1 || cycle - sub == X + 1)
            {
                op_line[cycle - sub] = '#';
            }
            if (cycle == 20 || (cycle - 20) % 40 == 0)
            {
                sub = cycle;
                signal_strength += cycle * X;
                for (auto i : op_line)
                {
                    cout << i;
                }
                cout << endl;
                op_line = crt;
                // cout << cycle << " " << X << " " << cycle * X << endl;
            }
            X += delta;

            delta = 0;
        }

        tokens = {};
    }
    cout << signal_strength << endl;

    return 0;
}