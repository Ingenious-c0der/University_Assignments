#include<iostream>
using namespace std;
class Node{
    friend class Queue;
    int data;
    Node *next;
    public:

    Node(int d){
        data=d;
        next=nullptr;
    }
};

class Queue{
    Node * front , *rear = nullptr;
    public:
    Queue();
    void enqueue(int );
    void dequeue();
    void displayQueue();
    ~Queue();
};

Queue::Queue(){
        front=nullptr;
        rear=nullptr;
    }
void Queue::dequeue(){
        if (rear==front and rear!=nullptr){
            delete rear ; 
            rear = front = nullptr ; 
        }
        else if (rear == nullptr){
            cout<<"Queue Underflow"<<endl;
        }
        else{
            Node* temp = front ; 
            front = front->next;
            if (front==nullptr){rear = nullptr; }
            delete temp; 
        }
    }

void Queue::enqueue(int d){
        Node * temp = new Node(d);
        if(rear == nullptr){
            front = rear = temp ;
            return ;
        }
        rear->next = temp ; 
        rear = temp ;
        return ; 
}

void Queue::displayQueue(){
        for(auto ptr = front ; ptr!=nullptr;ptr = ptr->next){cout<<ptr->data<<" ";}
        cout<<endl; 
    }

Queue::~Queue(){
        Node * temp ; 
        Node * ptr = front ; 
        while(ptr!=nullptr){
            temp = ptr->next ; 
            delete ptr ;
            ptr = temp ; 
        }
    }

int main()
{
    Queue Q ; 
    Q.enqueue(5);
    Q.enqueue(8);
    Q.enqueue(7);
    Q.displayQueue();
    Q.dequeue();Q.dequeue();Q.dequeue();Q.dequeue();
    Q.enqueue(9);
    Q.enqueue(8);
    Q.dequeue();
    Q.displayQueue();
    return 0;
}
