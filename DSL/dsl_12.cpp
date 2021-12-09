#include<iostream>
using namespace std;
class Node{
    friend class OrderQueue;
    int data;
    Node *next;
    public:

    Node(int d){
        data=d;
        next=nullptr;
    }
};

class OrderQueue{
    Node * front , *rear = nullptr;
    public:
    OrderQueue();
    void enqueue(int);
    void dequeue();
    void displayQueue();
    ~OrderQueue();
};

OrderQueue::OrderQueue(){
        front=nullptr;
        rear=nullptr;
    }
void OrderQueue::dequeue(){
        if (rear==front and rear!=nullptr){
            delete rear ; 
            rear = front = nullptr ; 
        }
        else if (rear == nullptr){
            cout<<"OrderQueue Underflow"<<endl;
        }
        else{
            Node* temp = front ; 
            front = front->next;
            if (front==nullptr){rear = nullptr; }
            delete temp; 
        }
    }

void OrderQueue::enqueue(int d){
        Node * temp = new Node(d);
        Node * store ; 
       

        if(rear == nullptr){
            front = rear = temp ;
            return ;
        }
        if(front->next == nullptr &&front->data>d){
            front->next = temp ; 
            temp->next = nullptr ;
            rear = temp ;
            return;
        }
        if(front->next == nullptr && front->data<d){
            temp->next = front; 
            rear = front ; 
            front = temp; 
            
            return ;
        }

        if(front->data<d){
            temp->next = front; 
            front = temp;
            return ;


        }


        for(store = front ; store->next->data>d;store=store->next){
            if(store->next->next==nullptr &&store->next->data<d){
                temp->next = store->next;
                store->next = temp;
                rear = temp->next ; 
                return ;
            }
            if(store->next->next==nullptr &&store->next->data>d){{
                temp->next = nullptr;
                store->next->next = temp;
                rear = temp ; 
                return; 
            }

            }
        }
        temp->next = store->next;
        store->next = temp;
        return ; 
}

void OrderQueue::displayQueue(){
        for(auto ptr = front ; ptr!=nullptr;ptr = ptr->next){cout<<ptr->data<<" ";}
        cout<<endl; 
    }

OrderQueue::~OrderQueue(){
        Node * temp ; 
        Node * ptr = front ; 
        while(ptr!=nullptr){
            temp = ptr->next ; 
            delete ptr ;
            ptr = temp ; 
        }
    }
int main()
{   OrderQueue Q;
    Q.enqueue(5);
    Q.enqueue(7);
    Q.enqueue(954);
    Q.dequeue();
    Q.dequeue();
    Q.enqueue(20);
    Q.enqueue(3);
    Q.enqueue(2);
    Q.enqueue(1000);
    Q.displayQueue();
    
    return 0;
}
