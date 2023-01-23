
//https://leetcode.com/problems/network-delay-time/
#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;

typedef pair<int,int>Pair;
class Graph{
public:
  vector<vector<Pair>> adjList;
  int n ;
  Graph(vector<vector<int>> const & times, int n)
  {
    this->n = n ;
    adjList.resize(n+1);
    for (auto &time :times)
    {
      int src = time[0];
      int dest = time[1];
      int weight = time[2];
      adjList[src].push_back(make_pair(dest,weight));
    }
  }
  //run  a DFS on the graph and check in the end if all nodes were covered
  int NetworkDelay(int start)
  {
    vector<bool> visited(n+1,false) ;
    vector<int> minTime(n+1,999);
    int k = 0 ;
    stack<int> stack ;
    stack.push(start);
    visited[start] = true;
    minTime[start] = 0 ;
    while(!stack.empty())
    {
      k = stack.top();
      stack.pop();
      for(Pair v :adjList[k])
      {
        minTime[v.first] = minTime[v.first]> minTime[k]+v.second? minTime[k]+v.second :minTime[v.first];
        if(!visited[v.first])
        {
          stack.push(v.first);
          visited[v.first] = !visited[v.first];
        }
      }

    }
    int minNDelay = 0;
    for(int i = 1; i<n+1 ; i++)
    {
        minNDelay = minNDelay<minTime[i]? minTime[i]:minNDelay;
    }
    for(int i = 1 ; i<n+1 ; i++)
    {
      if(!visited[i])
        return -1;
    }
    return minNDelay;
  }


};


int main()
{
  vector<vector<int>> times =
    {
      {2,3,1},{2,1,1},{3,4,1}
    };

    int n = 4;
    Graph graph(times, n);
    int ndelay = graph.NetworkDelay(2);
    cout<<ndelay;


}
