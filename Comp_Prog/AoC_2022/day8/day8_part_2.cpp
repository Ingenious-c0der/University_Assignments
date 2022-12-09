#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main()
{

    ifstream file("input.txt");
    string line;
    vector<vector<int>> forest;
    int max_scenic_score = 1;

    while (getline(file, line))
    {
        vector<int> row;
        for (int i = 0; i < line.size(); i++)
        {
            row.push_back(line[i] - '0');
        }
        forest.push_back(row);
    }
    const int n = forest.size();
    const int m = forest[0].size();
    int forest_skele[99][99] = {0};

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (i == 0 || i == n - 1 || j == 0 || j == m - 1)
            {
                forest_skele[i][j] = 1;
            }
            else
            {
                int scenic_score = 1;
                int north = 0, south = 0, east = 0, west = 0;
                // cout<<"i = "<<i<<" j = "<<j<< " "<<forest[i][j]<<endl;
                // check north
      
                for (int k = i - 1; k >= 0; k--)
                {
                    north++;
                    if (forest[k][j] >= forest[i][j])
                    {
                        break;
                    }
                }
                // check south

                for (int k = i + 1; k <= n - 1; k++)
                {
                    south++;
                    if (forest[k][j] >= forest[i][j])
                    {
                        break;
                    }
                }
     

                // check east

                
                for (int k = j + 1; k <= m - 1; k++)
                {
                    east++;
                    if (forest[i][k] >= forest[i][j])
                    {
                        break;
                    }
                }
               

                // check west

                
                for (int k = j - 1; k >= 0; k--)
                {
                    west++;
                    if (forest[i][k] >= forest[i][j])
                    {
                        break;
                    }
                }
               

               // cout << "North = " << north << " South = " << south << " East = " << east << " West = " << west << endl;
                scenic_score = north * south * east * west;
                if (scenic_score > max_scenic_score)
                {
                    max_scenic_score = scenic_score;
                }
            }
        }
    }

    cout << "max_scenic_score = " << max_scenic_score << endl;
}
