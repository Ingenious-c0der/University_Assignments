#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

void push(int &x, int delta_right, int delta_left, char direction)
{

    if (direction == '<')
    {
        if (x - delta_left > 0)
        {
            x--;
        }
    }
    else
    {
        if (x + delta_right < 7)
        {
            x++;
        }
    }
}

int main()

{
    ifstream file("input.txt");
    string jet_pushes;
    string line;
    int rocks_done = 0;
    int y_max = 59;
    int drop_size = 60;
    int jet_counter = 0;
    int rock_selector = 0;
    while (getline(file, line))
    {
        jet_pushes += line;
    }

    vector<vector<char>> grid(drop_size, vector<char>(7, '.'));
    for (int i = 0; i < 7; i++)
    {
        grid[y_max][i] = '-';
    }
    while (rocks_done < 50)
    {

        // segregate based on the rock type
        if (rock_selector == 0)
        {
            // doing it for the line rock type
            int y = y_max - 3;
            int x = 2;
            while (true)
            {
                char direction = jet_pushes[jet_counter];
                jet_counter++;
                push(x, 4, 0, direction);
              //  cout << y << "-" << x << endl;
                int flag = 0;
                for (int i = x; i < x + 4; i++)
                {

                    if (grid[y + 1][i] == '#' || grid[y + 1][i] == '-')
                    {
                        flag = 1;

                        break;
                    }
                }
                if (flag == 1)
                {
                    direction = jet_pushes[jet_counter];
                    jet_counter++;
                    push(x, 4, 0, direction);
                    for (int i = x; i < x + 4; i++)
                    {
                        grid[y][i] = '#';
                       // cout << grid[y][i] << endl;
                       // cout << y << " " << i << endl;
                    }
                    rocks_done++;
                    y_max = y;
                    break;
                }
                else
                {
                    y++;
                }
            }
        }

        else if (rock_selector == 1)
        {

            // doing it for the line plus rock type
            // x y co ods are of centre hash
            int y = y_max - 4;
            int x = 3;
            while (true)
            {
                char direction = jet_pushes[jet_counter];
                jet_counter++;
                push(x, 1, 1, direction);
                cout << y << "-" << x << endl;

                if (grid[y + 2][x] == '#' || grid[y + 2][x] == '-' || grid[y+1][x-1] ==  '#' || grid[y+1][x+1] == '#')
                {
                    direction = jet_pushes[jet_counter];
                    jet_counter++;
                    push(x, 1, 1, direction);
                    grid[y][x] = '#';
                    grid[y][x-1] = '#';
                    grid[y][x+1] = '#';
                    grid[y+1][x] = '#';
                    grid[y-1][x] = '#';
                    rocks_done++;
                    y_max = y;
                    break;
                }
                else
                {
                    y++;
                }
            }
        }


        else if (rock_selector == 2)
        {

            // doing it for the L rock type
            // x y co ods are of bottom line centre hash
            int y = y_max - 3;
            int x = 3;
            while (true)
            {
                char direction = jet_pushes[jet_counter];
                jet_counter++;
                push(x, 1, 1, direction);
               // cout << y << "-" << x << endl;

                int flag = 0;
                for (int i = x-1; i < x + 1; i++)
                {

                    if (grid[y + 1][i] == '#' || grid[y + 1][i] == '-')
                    {
                        flag = 1;

                        break;
                    }
                }
                if (flag == 1)
                {
                    direction = jet_pushes[jet_counter];
                    jet_counter++;
                    push(x, 1,1, direction);
                    for (int i = x-1; i < x + 1; i++)
                    {
                        grid[y][i] = '#';
                        cout << grid[y][i] << endl;
                        //cout << y << " " << i << endl;
                    }
                    grid[y-1][x+1] = '#';
                    grid[y-2][x-1] = '#';

                    rocks_done++;
                    y_max = y;
                    break;
                }
                else
                {
                    y++;
                }
            }
        }

        else if (rock_selector == 3)
        {

            // doing it for the line plus rock type
            // x y co ods are of centre hash
            int y = y_max - 4;
            int x = 3;
            while (true)
            {
                char direction = jet_pushes[jet_counter];
                jet_counter++;
                push(x, 1, 1, direction);
                cout << y << "-" << x << endl;

                if (grid[y + 2][x] == '#' || grid[y + 2][x] == '-' || grid[y+1][x-1] ==  '#' || grid[y+1][x+1] == '#')
                {
                    direction = jet_pushes[jet_counter];
                    jet_counter++;
                    push(x, 1, 1, direction);
                    grid[y][x] = '#';
                    grid[y][x-1] = '#';
                    grid[y][x+1] = '#';
                    grid[y+1][x] = '#';
                    grid[y-1][x] = '#';
                    rocks_done++;
                    y_max = y;
                    break;
                }
                else
                {
                    y++;
                }
            }
        }

        rock_selector = (rock_selector + 1) % 5;
    }

            // cout the grid
        for (int i = 0; i < drop_size; i++)
        {
            for (int j = 0; j < 7; j++)
            {
                cout << grid[i][j];
            }
            cout << endl;
        }
    return 0;
}