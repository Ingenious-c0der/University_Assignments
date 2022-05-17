#include<iostream>
using namespace std;

class Job{
    string name;
    int priority;
    
    public:
    Job(){
        priority=0;
    }
    Job(string n,int p){
        name = n ; 
        priority = p; 
    }
    bool operator >(const Job& J_other){
        return this->priority>J_other.priority;
    }
    bool operator <(const Job& J_other){
        return this->priority<J_other.priority;
    }


    friend class Node;
    friend class OrderQueue; 


};


class Node{
    friend class OrderQueue;
    Job data;
    Node *next;
    Node* prev;
    public:

    Node(Job j){
        data.name= j.name;
        data.priority = j.priority;
        next=nullptr;
        prev = nullptr;
    }
};

class OrderQueue{
    Node * front , *rear = nullptr;
    public:
    OrderQueue();
    void enqueue(Job);
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

void OrderQueue::enqueue(Job j){
        Node * temp = new Node(j);
       Node * store; 
       

        if(rear == nullptr){
            front = rear = temp ;
            return ;
        }
        if(front->next == nullptr &&front->data>j){
            front->next = temp ; 
            temp->prev = front; 
            temp->next = nullptr ;
            rear = temp ;
            return;
        }
        if(front->next == nullptr && front->data<j){
            temp->next = front;
            front->prev = temp ; 
            rear = front ; 
            front = temp; 
            
            return ;
        }

        if(front->data<j){
            temp->next = front; 
            front->prev = temp; 
            front = temp;
            return ;


        }


        for(store = front ; store->next->data>j;store=store->next){
            if(store->next->next==nullptr &&store->next->data<j){
           
                temp->next = store->next;
                temp->prev = store;
                store->next->prev = temp ;
                store->next = temp;
                rear = temp->next ; 
                return ;
            }
            if(store->next->next==nullptr &&store->next->data>j){
                
                temp->next = nullptr;
                temp->prev = store->next->next; 
                store->next->next = temp;
                rear = temp ; 
                return; 
            }

            
        }
        temp->next = store->next;
        temp->prev = store;
        store->next = temp;
        return ; 
}

void OrderQueue::displayQueue(){
        for(auto ptr = front ; ptr!=nullptr;ptr = ptr->next){cout<<ptr->data.name<<" ";}
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
    Job j1("job 1",5);
    Job j2("job 2",7);
    Job j3("job 3",2);
    Job j4("job 4",-1);
    Q.enqueue(j1);
    Q.enqueue(j2);
    Q.enqueue(j3);
    Q.enqueue(j4);
    Q.dequeue();
    Q.displayQueue();

    return 0;
}
