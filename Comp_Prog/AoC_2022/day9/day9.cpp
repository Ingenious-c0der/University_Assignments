#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

int main()
{

    ifstream file("input.txt");
    const int grid_size = 500;
    vector<vector<int>> map(grid_size, vector<int>(grid_size, 0));
    int column = grid_size / 2, row = grid_size / 2;
    map[row][column] = 1;
    string line;
    vector<vector<int>> knot_locations(10, vector<int>(column, row));

    while (getline(file, line))
    {
        char direction;
        int steps;

        stringstream ss(line);
        ss >> direction >> steps;
        for (int i = 0; i < steps; i++)
        {

            if (direction == 'U')
            {
                knot_locations[0][0] = knot_locations[0][0] - 1;
            }
            else if (direction == 'D')
            {
                knot_locations[0][0] = knot_locations[0][0] + 1;
            }
            else if (direction == 'L')
            {
                knot_locations[0][1] = knot_locations[0][1] - 1;
            }
            else if (direction == 'R')
            {
                knot_locations[0][1] = knot_locations[0][1] + 1;
            }
            if (knot_locations[0][0] > grid_size || knot_locations[0][0] < 0 || knot_locations[0][1] > grid_size || knot_locations[0][1] < 0)
            {
                cout << "out of bounds" << endl;
                return 1;
            }

            for (int i = 1; i < knot_locations.size(); i++)
            {
                int row_d = knot_locations[i - 1][0] - knot_locations[i][0];
                int col_d = knot_locations[i - 1][1] - knot_locations[i][1];


                if (row_d != 0)
                {
                    if(row_d > 0)
                    {
                        row_d--;
                    }
                    else
                    {
                        row_d++;
                    }
                }

                if(col_d != 0)
                {
                    if(col_d > 0)
                    {
                        col_d--;
                    }
                    else
                    {
                       col_d++;
                    }
                }
                if(row_d || col_d)
                {
                    knot_locations[i] = {knot_locations[i-1][0] - row_d, knot_locations[i-1][1] - col_d};
                }
                   
                // if (knot_locations[i - 1][1] > knot_locations[i][1] + 1)
                // {
                //     knot_locations[i][1]++;
                //     if (knot_locations[i - 1][0] > knot_locations[i][0])
                //     {
                //         knot_locations[i][0]++;
                //     }
                //     else if (knot_locations[i - 1][0] < knot_locations[i][0])
                //     {
                //         knot_locations[i][0]--;
                //     }
                // }
                // else if (knot_locations[i - 1][1] < knot_locations[i][1] - 1)
                // {
                //     knot_locations[i][1]--;
                //     if (knot_locations[i - 1][0] > knot_locations[i][0])
                //     {
                //         knot_locations[i][0]++;
                //     }
                //     else if (knot_locations[i - 1][0] < knot_locations[i][0])
                //     {
                //         knot_locations[i][0]--;
                //     }
                // }
                // else if (knot_locations[i - 1][0] > knot_locations[i][0] + 1)
                // {
                //     knot_locations[i][0]++;
                //     if (knot_locations[i - 1][1] > knot_locations[i][1])
                //     {
                //         knot_locations[i][1]++;
                //     }
                //     else if (knot_locations[i - 1][1] < knot_locations[i][1])
                //     {
                //         knot_locations[i][1]--;
                //     }
                // }
                // else if (knot_locations[i - 1][0] < knot_locations[i][0] - 1)
                // {
                //     knot_locations[i][0]--;
                //     if (knot_locations[i - 1][1] > knot_locations[i][1])
                //     {
                //         knot_locations[i][1]++;
                //     }
                //     else if (knot_locations[i - 1][1] < knot_locations[i][1])
                //     {
                //         knot_locations[i][1]--;
                //     }
                // }
            }

            map[knot_locations[9][0]][knot_locations[9][1]] = 1;
           
        }
    }
    int total = 0;
    for (int i = 0; i < grid_size; i++)
    {
        for (int j = 0; j < grid_size; j++)
        {

            if (map[i][j] == 1)
            {
                 cout << "#"
                      << "";
                total++;
            }
            else
            {
                 cout << "."
                      << "";
            }
        }
        cout << endl;
    }
    cout << total << endl;
}