#include <iostream>
#include <omp.h>
#include <queue>
#include <stack>
#include <vector>

class Graph {
  std::vector<std::vector<int>> adjList;

public:
  Graph(int);
  void addEdge(int, int);
  void paraBFS(int);
  void paraDFS(int);
  void paraDFSutil(int, std::vector<bool> &);
  void print();
};

Graph::Graph(int V) { adjList.resize(V); };

void Graph::print() {
  for (int i = 0; i < adjList.size(); i++) {
    std::cout << i << " ";
    for (auto j : adjList[i]) {
      std::cout << j << " ";
    }
    std::cout << std::endl;
  }
}

void Graph::addEdge(int u, int v) { adjList[u].push_back(v); };

void Graph::paraBFS(int source) {
  std::vector<bool> visited(adjList.size(), false);
  std::queue<int> q;
  visited[source] = true;
  q.push(source);
  std::cout << "BFS : ";
  while (!q.empty()) {
    int u;
#pragma omp parallel shared(q, visited)
    {
#pragma omp single
      {
        u = q.front();
        q.pop();
        std::cout << u << ' ';
      }
      if (!(adjList[u].size() == 0)) {
#pragma omp for
        for (int i = 0; i <= adjList[u].size() - 1; ++i) {
          if (!visited[adjList[u][i]]) {
#pragma omp critical
            {
              q.push(adjList[u][i]);
              visited[adjList[u][i]] = true;
            }
          }
        }
      }
    }
  }
  std::cout << std::endl;
}
void Graph::paraDFSutil(int v, std::vector<bool> &visited) {
  visited[v] = true;
  std::cout << v << " ";
#pragma omp parallel for
  for (int i = 0; i < adjList[v].size(); ++i) {
    int u = adjList[v][i];
    if (!visited[u]) {
      paraDFSutil(u, visited);
    }
  }
};
void Graph::paraDFS(int source) {
  std::vector<bool> visited(adjList.size(), false);
  std::cout << "DFS : ";
  paraDFSutil(source, visited);
  std::cout << std::endl;
}

int main() {
  Graph g(7);

  g.addEdge(0, 1);
  g.addEdge(0, 2);
  g.addEdge(1, 3);
  g.addEdge(1, 4);
  g.addEdge(2, 5);
  g.addEdge(2, 6);
  // g.print();
  g.paraBFS(0);
  g.paraDFS(0);
  return 0;
}
