//https://leetcode.com/problems/unique-paths-ii/
#include<iostream>
#include<vector>
#include<set>
#include <bits/stdc++.h>
using namespace std;

set<string> paths ;
void permute(string str, string out)
{
    // When size of str becomes 0, out has a
    // permutation (length of out is n)
    if (str.size() == 0)
    {
        paths.insert(out);
        return;
    }

    // One be one move all characters at
    // the beginning of out (or result)
    for (int i = 0; i < str.size(); i++)
    {
        // Remove first character from str and
        // add it to out
        permute(str.substr(1), out + str[0]);

        // Rotate string in a way second character
        // moves to the beginning.
        rotate(str.begin(), str.begin() + 1, str.end());
    }
}
int uniquePath(vector<vector<int>> const & obstacleGrid)
{
  string default_pattern = "";
  for(int i = 0 ; i <
    obstacleGrid.size() - 1;i++)
  {
    default_pattern+="RD";
  }
  permute(default_pattern,"");
  int count = 0 ;
  for(auto path : paths)
  {
    int rights = 0; int downs = 0 ;
    bool flag = true;
    for(char dir : path)
    {
      dir == 'R'?rights++:downs++;
      if(obstacleGrid[rights][downs] == 1)
      {

        flag = false;
        break;
      };
    }
    if(flag)
    {
      count++;
    }
  }

  return count;
  //if there was no obstacle , the total number of unique
  // ways would be all possible combinations of rights and downs
  // we can simply consider all at first and then mark off the impossible ones
  //due to obstacles using an validator.
}


int main()
{

  int x = uniquePath({{0,0,0,1},{0,0,0,0},{0,0,0,1},{1,0,0,0}});
  cout<<x <<endl;
  return 0 ;
}
