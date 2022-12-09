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
    int max_scenic_score = 1 ;
    

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
                int scenic_score = 1;
                int north , south , east ,west ; 
                cout<<"i = "<<i<<" j = "<<j<< " "<<forest[i][j]<<endl;
                //check north 
                int flag = 0;
                int count = 0; 
                for(int k = i-1; k >= 0 ; k --)
                {
                   count++; 
                    if(forest[k][j] >= forest[i][j])
                    {
                        
                        scenic_score *= (count);
                        north = count ; 
                        flag = 1 ; 
                        break;
                    }
                    
                }
                if(flag == 0 )
                {
                    forest_skele[i][j] = 1;
                   
                    continue;
                }
             count = 0 ;
                
                flag = 0 ; 
                //check south
               
                for(int k = i+1; k <= n-1 ; k ++)
                {
                    count++;
                    if(forest[k][j] >= forest[i][j])
                    {
                        flag = 1 ; 
                        south = count ; 
                        scenic_score *= count;
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
                count = 0 ;
                
                for(int k = j+1; k <= m-1 ; k ++)
                {
                    count++;
                    if(forest[i][k] >= forest[i][j])
                    {
                        flag = 1 ; 
                        east  = count ; 
                        scenic_score *= (count);
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
                count = 0 ;
                for(int k = j-1; k >= 0 ; k --)
                {
                    count++;
                    if(forest[i][k] >= forest[i][j])
                    {
                        flag = 1 ; 
                        west = count ; 
                        scenic_score *= (count);
                        break;
                    }
                    
                }
                if(flag == 0 )
                {
                    forest_skele[i][j] = 1;
                  
                    continue;
                }
                cout<<"North = "<<north<<" South = "<<south<<" East = "<<east<<" West = "<<west<<endl;
                if(scenic_score > max_scenic_score)
                {
                    max_scenic_score = scenic_score;
                }
                

            }
        }
    }
    
   
    cout<<"max_scenic_score = "<<max_scenic_score<<endl;
}
