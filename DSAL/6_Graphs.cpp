#include <iostream>
using namespace std;
class Graph;

template <typename T, int size>
class Stack
{
private:
  T *stack;
  int top = -1;

public:
  Stack();
  T pop();
  void push(T const &val);
  T get_top();
  void show();
  bool is_empty();
};
template <typename T, int size>
T Stack<T, size>::pop()
{
  if (top == -1)

  {
    cout << "Stack Underflow" << endl;
    return T(); //make sure the class(typename) has a default ctor
  }
  else
  {
    return stack[top--];
  }
}
template <typename T, int size>
bool Stack<T, size>::is_empty()
{
  return top == -1;
}
template <typename T, int size>
void Stack<T, size>::push(T const &val)
{
  if (top < size - 1)

  {
    top++;
    stack[top] = val;
  }
  else
  {
    cout << "stack overflow" << endl;
    
  }
}
template <typename T, int size>
Stack<T, size>::Stack()
{
  stack = new T[size];
}
template <typename T, int size>
void Stack<T, size>::show()
{
  for (int i = 0; i < top + 1; i++)

  {
    cout << stack[i] << " ";
  }
  cout << endl;
}
template <typename T, int size>
T Stack<T, size>::get_top()
{
  return stack[top];
}

class Node
{
  static int count;
  string placeName = "";
  Node *next = nullptr;
  int weight = 0;
  int refValue = -1;

public:
  Node()
  {
  }

  Node(string placeName, int weight, bool considerCount = false)
  {
    this->placeName = placeName;
    this->weight = weight;
    if (considerCount)
    {
      refValue = count;

      count++;
    }
  }
  void setrefValue(int refValue)
  {
    this->refValue = refValue;
  }

  void add(int ref, string placeName, int weight)
  {
    if (!next)
    {
      next = new Node(placeName, weight);
      next->setrefValue(ref);
      return;
    }
    Node * temp =  new Node(placeName, weight);
    temp->setrefValue(ref);
    temp ->next= next; 
    next = temp ;
    
  }
  friend class Graph;
  friend class Queue;
};
int Node::count = 0;

class Queue
{
  Node queue[100];
  int n = 100;
  int rear = -1;
  int front = -1;

public:
  Queue()
  {
  }

  void Insert(Node val)
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
  Node Delete()
  {
    if (front == -1 || front > rear)
    {
      cout << "Queue Underflow ";
      return Node();
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
};

class Graph
{

  Node **listgrp;
  int max_ver = 0;
  int count = 0;
  int *visited;

public:
  Graph(int max_vertices)
  {
    max_ver = max_vertices;
    listgrp = new Node *[max_ver];
    visited = new int[max_ver];
    for (int i = 0; i < max_ver; i++)
    {
      visited[i] = 0;
    }
  }
  void addConnection(string name, string placeNameOth, int weight)
  {


    for (int i = 0; i < max_ver; i++)
    {
      if (listgrp[i])
      {
        if (listgrp[i]->placeName == name)
        {
          listgrp[i]->add(NodefromName(placeNameOth).refValue, placeNameOth, weight);
          break;
        }
        if (i == max_ver)
        {
          cout << "No node named " << name << " found" << endl;
          return;
        }
      }
    }
    for (int i = 0; i < max_ver; i++)
    {
      if (listgrp[i])
      {
        if (listgrp[i]->placeName == placeNameOth)
        {
          listgrp[i]->add(NodefromName(name).refValue, name, weight);
          return;
        }
      }
    }
    cout << "No node named " << placeNameOth << " found" << endl;
  }
  Node NodefromName(string name)
  {
    for (int i = 0; i < max_ver; i++)
    {
      if (listgrp[i])
      {
        if (listgrp[i]->placeName == name)
        {
          return *listgrp[i];
        }
      }
    }
    cout << "No node named " << name << " found" << endl;
    return Node();
  }
  void insertNode(string placeName)
  {
    listgrp[count] = new Node(placeName, 0, true);
    count++;
  }

  void DisplayAdjacencyList()
  {
    for (int i = 0; i < max_ver; i++)
    {
      if (listgrp[i])
      {
        cout << listgrp[i]->placeName << " => ";
        Node *runner = listgrp[i]->next;
        while (runner)
        {
          cout << runner->placeName << " -> ";
          runner = runner->next;
        }
      }
      cout<<"|" << endl;
    }
  }

  void BFS(Node start)
  {
    Queue Q;
    Node U;

    Q.Insert(start);
    visited[start.refValue] = 1;
    cout << "BFS: ";
    while (Q.NotEmpty())
    {
      U = Q.Delete();

      cout << U.placeName << " ";
      for (Node *cur = U.next; cur != nullptr; cur = cur->next)
      {
        if (visited[cur->refValue] == 0)
        {
          Q.Insert(NodefromName(cur->placeName));
          visited[cur->refValue] = 1;
        }
      }
    }
    cout << endl;
    //the array is in class scope hence needs to be flushed for the next time. 
    for (int i = 0; i < max_ver; i++)
    {
      visited[i] = 0;
    }
  }

  void DFSrecursive(Node C)
  {

    visited[C.refValue] = 1;
    cout << C.placeName << "->";
    for (Node *cur = C.next; cur != nullptr; cur = cur->next)
    {
      if (visited[cur->refValue] == 0)
      {
        DFS(NodefromName(cur->placeName));
      }
    }
  }
  //same as bfs but stack instead of queue
  void DFS(Node start)
  {

    Stack<Node, 100> S;
    S.push(start);
    cout << "DFS : ";
    visited[start.refValue] = 1 ; 
    while (!S.is_empty())
    {
      Node U = S.pop();
      cout << U.placeName <<"  ";
      for (Node *cur = U.next; cur != nullptr; cur = cur->next)
      {
        if (visited[cur->refValue] == 0)
        {
          S.push(NodefromName(cur->placeName));
          visited[cur->refValue] = 1; 
        }
      }
    }

    //the array is in class scope hence needs to be flushed for the next time. 
    for (int i = 0; i < max_ver; i++)
    {
      visited[i] = 0;
    }
  }
};

int main()
{

  // Graph g(6);
  // g.insertNode("Pict");
  // g.insertNode("Bibwewadi");
  // g.insertNode("BVP");
  // g.insertNode("My_house");
  // g.insertNode("Datta_Nagar");
  // g.insertNode("Katraj");

  // g.addConnection("Pict", "Bibwewadi", 10);
  // g.addConnection("BVP", "Pict", 10);
  // g.addConnection("Datta_Nagar", "Bibwewadi", 10);
  // g.addConnection("My_house", "Bibwewadi", 10);
  // g.addConnection("BVP", "Datta_Nagar", 10);
  // g.addConnection("Datta_Nagar", "My_house", 10);
  // g.addConnection("Katraj", "My_house", 10);

  Graph g(5);
  g.insertNode("0");
  g.insertNode("1");
  g.insertNode("2");
  g.insertNode("3");
  g.insertNode("4");
  g.addConnection("0", "1", 10);
  g.addConnection("0", "2", 10);
  g.addConnection("0", "4", 10);
  g.addConnection("4", "3", 10);
  


  g.DisplayAdjacencyList();
  g.BFS(g.NodefromName("0"));
  g.DFS(g.NodefromName("0"));

  return 0;
}
