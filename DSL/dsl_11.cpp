#include<iostream>
using namespace std;
class Node{
    friend class Queue;
    string data;
    Node *next;
    public:

    Node(string d){
        data=d;
        next=nullptr;
    }
};

class Queue{
    Node * front , *rear = nullptr;
    public:
    Queue();
    void enqueue(string);
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

void Queue::enqueue(string d){
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
    int choice;
    Queue Q ;
    string job; 
    while(true){
    cout<<"***Menu***\n1. Enqueue\n2.Dequeue\n3.Display Queue"<<endl;
    cin>>choice;
    switch(choice){
        case 1 :
            cout<<"Enter the Job to be enqueued : ";
            cin>>job;
            Q.enqueue(job);
            break;
        case 2 :
            Q.dequeue();
            break;
        case 3 :
            Q.displayQueue();
            break;

    }
    
}
return 0;
}
