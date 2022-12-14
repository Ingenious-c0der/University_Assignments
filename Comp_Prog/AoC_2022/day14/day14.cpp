#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <sstream>
#include <regex>
using namespace std;
int x_lim = 100;
int x_size = 700;
int y_size = 200;

int dump_sand(int row, int col, vector<vector<char>> &grid)
{

    if (grid[0][500 - x_lim] == 'o')
    {
        return -1;
    }
    if (row == grid.size() - 1 || col == grid[0].size() - 1)
    {
        return -1;
    }

    if (grid[row + 1][col] == '.')
    {
        return dump_sand(row + 1, col, grid);
    }
    else if (grid[row + 1][col] == 'o')
    {

        if (grid[row + 1][col - 1] == '.')
        {
            return dump_sand(row + 1, col - 1, grid);
        }
        else if (grid[row + 1][col + 1] == '.')
        {
            return dump_sand(row + 1, col + 1, grid);
        }
        else
        {
            grid[row][col] = 'o';
            return 1;
        }
    }
    else if (grid[row + 1][col] == '#')
    {

        if (grid[row + 1][col - 1] == '.')
        {
            return dump_sand(row + 1, col - 1, grid);
        }
        else if (grid[row + 1][col + 1] == '.')
        {
            return dump_sand(row + 1, col + 1, grid);
        }
        else
        {
            grid[row][col] = 'o';
            return 1;
        }
    }
    // check for grid out of bounds or co ods of sand dumper are jammed

    cout << "reached here" << endl;
    return -1;
}

void drawline(vector<int> start, vector<int> end, vector<vector<char>> &grid)
{
    if (start[0] == end[0])
    {
        int starty = start[1];
        int endy = end[1];
        // cout << starty << " drawing for row change " << endy << endl;
        for (int i = min(starty, endy); i <= max(starty, endy); i++)
        {
            grid[i][start[0] - x_lim] = '#';
        }
    }
    else
    {
        int startx = start[0] - x_lim;
        int endx = end[0] - x_lim;
        // cout << startx << " drawing for col change " << endx << endl;
        for (int i = min(startx, endx); i <= max(startx, endx); i++)
        {
            grid[start[1]][i] = '#';
        }
    }
}
void drawline_2(int row, vector<vector<char>> &grid)
{
    for (int i = 0; i < grid[row].size(); i++)
    {

        grid[row][i] = '#';
    }
}

void draw_grid(vector<vector<char>> &grid)
{
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            cout << grid[i][j];
        }
        cout << endl;
    }
}

int main()
{
    vector<vector<char>> grid(y_size, vector<char>(x_size, '.'));
    fstream input("input.txt");
    string line;
    int y_max = 0;
    while (getline(input, line))
    {
        // split the line in to tokens separated by ->
        stringstream ss(line);
        string token;
        vector<string> tokens;
        while (getline(ss, token, '-'))
        {
            tokens.push_back(token);
        }
        for (int i = 0; i < tokens.size(); i++)
        {
            // regex replace all the non numeric characters
            tokens[i] = regex_replace(tokens[i], regex("[^0-9]"), "");
        }

        for (int i = 0; i < tokens.size(); i++)
        {
            cout << tokens[i] << endl;
            if (i + 1 >= tokens.size())
            {
                break;
            }
            if (y_max < stoi(tokens[i].substr(3)))
            {
                y_max = stoi(tokens[i].substr(3));
            }
            drawline({stoi(tokens[i].substr(0, 3)), stoi(tokens[i].substr(3))}, {stoi(tokens[i + 1].substr(0, 3)), stoi(tokens[i + 1].substr(3))}, grid);
        }
    }

    drawline_2(y_max + 2, grid); // for part 2 only
    grid[0][500 - x_lim] = '+';

    int count = 0;
    int x = 0;
    while (true)
    {
        x = dump_sand(0, 500 - x_lim, grid);

        if (x == -1)
        {
            break;
        }
        count++;
    }
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            cout << grid[i][j];
        }
        cout << endl;
    }

    cout << count << endl;

    return 0;
}