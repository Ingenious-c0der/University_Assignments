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
    cout << stack[i].nodeName << " ";
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
  string nodeName = "";
  Node *next = nullptr;
  int weight = 0;
  int refValue = -1;

public:
  Node()
  {
  }

  Node(string nodeName, int weight, bool considerCount = false)
  {
    this->nodeName = nodeName;
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

  void add(int ref, string nodeName, int weight)
  {
    if (!next)
    {
      next = new Node(nodeName, weight);
      next->setrefValue(ref);
      return;
    }
    Node * temp =  new Node(nodeName, weight);
    temp->setrefValue(ref);
    temp ->next= next; 
    next = temp ;
    
  }
  friend class Graph;
  friend class Queue;
  friend class Stack<Node, 100>; 
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
  
public:
int *visited;

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
  void addConnection(string name, string nodeNameOth, int weight)
  {


    for (int i = 0; i < max_ver; i++)
    {
      if (listgrp[i])
      {
        if (listgrp[i]->nodeName == name)
        {
          listgrp[i]->add(NodefromName(nodeNameOth).refValue, nodeNameOth, weight);
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
        if (listgrp[i]->nodeName == nodeNameOth)
        {
          listgrp[i]->add(NodefromName(name).refValue, name, weight);
          return;
        }
      }
    }
    cout << "No node named " << nodeNameOth << " found" << endl;
  }
  Node NodefromName(string name)
  {
    for (int i = 0; i < max_ver; i++)
    {
      if (listgrp[i])
      {
        if (listgrp[i]->nodeName == name)
        {
          return *listgrp[i];
        }
      }
    }
    cout << "No node named " << name << " found" << endl;
    return Node();
  }
  void insertNode(string nodeName)
  {
    listgrp[count] = new Node(nodeName, 0, true);
    count++;
  }

  void DisplayAdjacencyList()
  {
    for (int i = 0; i < max_ver; i++)
    {
      if (listgrp[i])
      {
        cout << listgrp[i]->nodeName << " = ";
        Node *runner = listgrp[i]->next;
        while (runner)
        {
          cout << runner->nodeName << " -> ";
          runner = runner->next;
        }
      }
      cout<<" X " << endl;
    }
  }

  void BFSRecursive(Queue q)
  {
    if(q.NotEmpty())
    {
      Node U = q.Delete();
      cout << U.nodeName << "  ";
      for (Node *cur = U.next; cur != nullptr; cur = cur->next)
      {
        if (visited[cur->refValue] == 0)
        {
          q.Insert(NodefromName(cur->nodeName));
          visited[cur->refValue] = 1;
        }
      }
      BFSRecursive(q);
    }
    else
    {
      //flush the visited array
      for (int i = 0; i < max_ver; i++)
      {
        visited[i] = 0;
      }
      return ; 
    }

  }



  void BFS(Node start)
  {
    Queue Q;
    Node U;

    Q.Insert(start);
    visited[start.refValue] = 1;
    cout << "BFS : ";
    while (Q.NotEmpty())
    {
      U = Q.Delete();

      cout << U.nodeName << "  ";
      for (Node *cur = U.next; cur != nullptr; cur = cur->next)
      {
        if (visited[cur->refValue] == 0)
        {
          Q.Insert(NodefromName(cur->nodeName));
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
    cout << C.nodeName << "  ";
    for (Node *cur = C.next; cur != nullptr; cur = cur->next)
    {
      if (visited[cur->refValue] == 0)
      {
        DFSrecursive(NodefromName(cur->nodeName));
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
      cout << U.nodeName <<"  ";
      for (Node *cur = U.next; cur != nullptr; cur = cur->next)
      {
        if (visited[cur->refValue] == 0)
        {
          S.push(NodefromName(cur->nodeName));
          visited[cur->refValue] = 1; 
        }
      }
    }
    //the array is in class scope hence needs to be flushed for the next time. 
    for (int i = 0; i < max_ver; i++)
    {
      visited[i] = 0;
      
    }
    cout<<endl;
  }

  void refreshBuffer()
  {
    for (int i = 0; i < max_ver; i++)
    {
      visited[i] = 0;
    }
  }



};

int main()
{


 
  cout<< "Graph" <<endl; 
  /*
    Structure of the graph is as follows
      
              A
            /   \
           /     \
          B       C
        /   \   /   \ 
      D     E  F     G
  */

  Graph tree_like(7);
  tree_like.insertNode("A");
  tree_like.insertNode("B");
  tree_like.insertNode("C");
  tree_like.insertNode("D");
  tree_like.insertNode("E");
  tree_like.insertNode("F");
  tree_like.insertNode("G");
  tree_like.addConnection("A", "B", 10);
  tree_like.addConnection("A", "C", 10);
  tree_like.addConnection("B", "D", 10);
  tree_like.addConnection("B", "E", 10);
  tree_like.addConnection("C", "F", 10);
  tree_like.addConnection("C", "G", 10);
  tree_like.DisplayAdjacencyList();
  tree_like.BFS(tree_like.NodefromName("A"));
  tree_like.DFS(tree_like.NodefromName("A"));
  cout<< "DFS Recursive : ";
  tree_like.DFSrecursive(tree_like.NodefromName("A"));
  tree_like.refreshBuffer() ;
  cout<<endl; 
  Queue q ;
  q.Insert(tree_like.NodefromName("A"));
  cout << "BFS Recursive : ";
  tree_like.visited[0] = 1; 
  tree_like.BFSRecursive(q);
  cout<<endl;


  return 0;
}
