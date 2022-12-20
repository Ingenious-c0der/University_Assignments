#include <iostream>
#include <regex>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <stack>
#include <queue>
#include <map>
#include <set>
using namespace std;

int x_lim = -900000;
int y_lim = -900000;
int given_y = 2'000'000 - x_lim;
int x_size = 7000000;
int y_size = 7000000;
int distance(int x, int y, int x2, int y2)
{

    int distance = abs(x - x2) + abs(y - y2);
    return distance;
}

int not_in(vector<vector<int>> points, int x, int y)
{
    for (int i = 0; i < points.size(); i++)
    {

        if (points[i][0] == x && points[i][1] == y)
        {
            // cout << x << " in points " << y << endl;
            return -1;
        }
    }
    // cout<< x << " not in points " << y << endl;
    return 1;
}

void setPoint(char c, int x, int y, vector<vector<char>> &grid)
{
    grid[y][x] = c;
}

void printGrid(vector<vector<char>> grid)
{
    for (int i = 0; i < grid.size(); i++)
    {
        cout << i << " ";
        for (int j = 0; j < grid[0].size(); j++)
        {
            cout << grid[i][j];
        }
        cout << endl;
    }
}
void extend_sensor_coverage(set<vector<int>> &point_set , vector<vector<int>> points, int x, int y, int distance_units)
{

  
    for (int j = 0; j < y_size; j++)
    {
        if (distance(x, y, given_y , j) <= distance_units )
        {
           if(not_in(points,j,given_y) == 1)
           {
                point_set.insert({j, given_y}); 
           }        
        
        }
    }
   // cout<< endl;

}
int main()
{
    fstream input("input.txt");
    string line;
    int total = 0;
    vector<vector<int>> points;
    set<vector<int>> points_set;


    while (getline(input, line))
    {

        regex non_digit("[^0-9]");
        line = regex_replace(line, non_digit, " ");

        stringstream ss(line);
        int a, b, c, d;
        ss >> a >> b >> c >> d;
        b -= x_lim;
        d -= x_lim;
        a -= y_lim;
        c -= y_lim;
       if(b == given_y)
       {
         points.push_back({a, b});
       }
       if(d == given_y)
       {
        points.push_back({c, d});
       }
       
    }
    input.clear();
    input.seekg(0, ios::beg);
    int m = 0 ; 
    cout<<points.size()<<endl;
    while (getline(input, line))
    {

        regex non_digit("[^0-9]");
        line = regex_replace(line, non_digit, " ");

        stringstream ss(line);
        int a, b, c, d;
        ss >> a >> b >> c >> d;
        // cout << a << " " << b << " " << c << " " << d << endl;
        b -= x_lim;
        d -= x_lim;
        a -= y_lim;
        c -= y_lim;
        int radius = distance(a, b, c, d);
        extend_sensor_coverage(points_set, points, a, b, radius );
        cout<< "sensor " << m+1 << " complete " << points_set.size() << endl;
        m++;
    }

    cout << total;

    return 0;
}