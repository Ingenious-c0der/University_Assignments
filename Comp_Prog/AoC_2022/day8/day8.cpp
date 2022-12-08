#include<iostream> 
#include<fstream>
#include<string>
#include<vector>
using namespace std;

int main()
{
    
    ifstream file("input.txt");
    string line;
    vector<vector<int>> forest;
    

    while(getline(file, line))
    {
        vector<int> row;
        for(int i = 0; i < line.size(); i++)
        {
            row.push_back(line[i] - '0');
        }
        forest.push_back(row);
    }
    const int n = forest.size();
    const int m = forest[0].size();
    int forest_skele[99][99] = {0};

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(i == 0 || i == n-1 || j == 0 || j == m-1)
            {
                forest_skele[i][j] = 1;
            }
            else
            {
                //cout<<"i = "<<i<<" j = "<<j<< " "<<forest[i][j]<<endl;
                //check north 
                int flag = 0;
                
                for(int k = i-1; k >= 0 ; k --)
                {
                   
                    if(forest[k][j] >= forest[i][j])
                    {
                        flag = 1 ; 
                        break;
                    }
                    
                }
                if(flag == 0 )
                {
                    forest_skele[i][j] = 1;
                   
                    continue;
                }

                
                flag = 0 ; 
                //check south
               
                for(int k = i+1; k <= n-1 ; k ++)
                {
                    if(forest[k][j] >= forest[i][j])
                    {
                        flag = 1 ; 
                        break;
                    }
                    
                }
                if(flag == 0 )
                {
                    forest_skele[i][j] = 1;
                   
                    continue;
                }
                
                //check east
                flag = 0 ; 
                
                for(int k = j+1; k <= m-1 ; k ++)
                {
                    
                    if(forest[i][k] >= forest[i][j])
                    {
                        flag = 1 ; 
                        break;
                    }
                    
                }
                if(flag == 0 )
                {
                    forest_skele[i][j] = 1;
                    
                    continue;
                }
                
                //check west
                flag  = 0 ;
                
                for(int k = j-1; k >= 0 ; k --)
                {
                    if(forest[i][k] >= forest[i][j])
                    {
                        flag = 1 ; 
                        break;
                    }
                    
                }
                if(flag == 0 )
                {
                    forest_skele[i][j] = 1;
                  
                    continue;
                }
                

            }
        }
    }
    
    int scenic_score = 1;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
           
            if(forest_skele[i][j] == 0)
            {
               // total_count++;
            }
        }
        cout << endl;
    }
    cout<<"max_scenic_score = "<<scenic_score<<endl;
    




}
