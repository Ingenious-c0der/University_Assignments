// 8
// write a cpp or java program to implement topological sorting on graph using object oriented programming features
// design necessary class. Use a graph

// 301 staff room

#include <iostream>
using namespace std;

class Queue
{
    int queue[100];
    int n = 100;
    int rear = -1;
    int front = -1;

public:
    Queue()
    {
    }

    void Insert(int val)
    {

        if (rear == n - 1)
            cout << "Queue Overflow" << endl;
        else
        {
            if (front == -1)
                front = 0;
            rear++;
            queue[rear] = val;
        }
    }
    int Delete()
    {
        if (front == -1 || front > rear)
        {
            cout << "Queue Underflow ";
            return -1;
        }
        else
        {
            return queue[front++];
        }
    }

    bool NotEmpty()
    {
        return front != -1 && front <= rear;
    }
    void Display()
    {
        if (front == -1)
            cout << "Queue is empty" << endl;
        else
        {
            cout << "Queue elements are : ";
            for (int i = front; i <= rear; i++)
                cout << queue[i] << " ";
            cout << endl;
        }
    }
};

class Graph
{

    int **matrix;
    int max_ver = 0;
    string *NodeList;
    static int index;
    int *visited;
    int *indegree;

public:
    Graph(int max_vertices)
    {

        matrix = new int *[max_vertices];
        for (int i = 0; i < max_vertices; i++)
        {
            matrix[i] = new int[max_vertices];
        }
        for (int i = 0; i < max_vertices; i++)
        {
            for (int j = 0; j < max_vertices; j++)
            {
                matrix[i][j] = 0;
            }
        }
        max_ver = max_vertices;
        NodeList = new string[max_ver];
        visited = new int[max_ver];
        indegree = new int[max_ver];
    }
    ~Graph()
    {

        for (int i = 0; i < max_ver; i++)
        {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
    void insertNode(string name)
    {
        if (index < max_ver)
        {
            NodeList[index++] = name;
        }
        else
        {
            cout << "No more nodes can be added" << endl;
        }
    }
    int refValuefromName(string name)
    {
        for (int i = 0; i < max_ver; i++)
        {
            if (NodeList[i] == name)
            {
                return i;
            }
        }
        return -1;
    }

    void addConnection(string name1, string name2)
    {
        int index1 = refValuefromName(name1);
        int index2 = refValuefromName(name2);
        if (index1 == -1 || index2 == -1)
        {
            if (index1 == -1)
            {
                cout << "No node named " << name1 << " found" << endl;
                return;
            }
            cout << "No node named " << name2 << " found" << endl;
        }
        matrix[index1][index2] = 1;
    }

    void indegree_calculator(Queue *q)
    {

        for (int i = 0; i < max_ver; i++)
        {
            visited[i] = 0;
            indegree[i] = 0;
            for (int j = 0; j < max_ver; j++)
            {
                if (matrix[j][i] != 0)
                    indegree[i] += 1;
            }
            if (indegree[i] == 0)
            {
                visited[i] = 1;
                q->Insert(i);
            }
        }
    }
    // using adjecency list for graph representation is always preferable since otherwise
    // you need to keep a visited list to make sure you queue back a node you have already printed
    // using kahns (BFS:queue) algo , can be done using DFS:stack too
    void topological_sort()
    {
        Queue q;
        int j = 0;
        indegree_calculator(&q);
        while (q.NotEmpty())
        {
            j = q.Delete();
            cout << NodeList[j] << endl;
           

            for (int m = 0; m < max_ver; m++)
            {
                if (matrix[j][m] != 0)
                    indegree[m] -= 1;
                if (indegree[m] == 0 and visited[m] == 0)
                {
                    visited[m] = 1;	// mark as visited
                    q.Insert(m);
                }
            }
        }
    }

    void printAdjacencyMatrix()
    {
        cout << "Adjacency Matrix" << endl;
        for (int i = 0; i < max_ver; i++)
        {
            for (int j = 0; j < max_ver; j++)
            {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }
};
int Graph::index = 0;

int main()
{
    Graph g(6);
    // these nodes can be any name too
    g.insertNode("0");
    g.insertNode("1");
    g.insertNode("2");
    g.insertNode("3");
    g.insertNode("4");
    g.insertNode("5");
    /*
        5          4
        |\    /    |
        |  \/      |
        v   0      V
        2 -> 3 -> 1

    */

    g.addConnection("5", "0");
    g.addConnection("5", "3");
    g.addConnection("3", "2");
    g.addConnection("2", "1");
    g.addConnection("4", "0");
    g.addConnection("4", "1");
    g.topological_sort();

    return 0;
}
