#include<iostream>
using namespace std;
class SLL{
    class Node{
        public:
        int value ; 
        Node * next;
        Node(const int val){
            value = val;
            next = nullptr;
        }
        Node(const int val ,  Node* n){
            value = val;
            next = n;	
        }
    };
    Node * first = nullptr;
    public:
    SLL(){
        first = nullptr;
    }
    void insert_node(const int val){
            Node * temp = new Node(val,first);
            first = temp;
    }
    void display(){
        for(auto ptr = first ; ptr!=nullptr ; ptr = ptr->next)
        {
            cout<<ptr->value<<" ";
        }
        cout<<endl;
    }
    void sort(){
        Node * ptr = first;
        Node * temp = nullptr;
        while(ptr!=nullptr){
            temp = ptr->next;
            while(temp!=nullptr){
                if(ptr->value > temp->value){
                    int temp_val = ptr->value;
                    ptr->value = temp->value;
                    temp->value = temp_val;
                }
                temp = temp->next;
            }
            ptr = ptr->next;
        }
    }
    ~SLL(){
        Node * ptr = first;
        Node * temp ;
        while(ptr!=nullptr)
        {
            temp = ptr->next;
            delete ptr;
            ptr = temp;
        }
    }
    void reverse(){
     Node * ptr = first;
     Node * next = nullptr;
     Node  * prev = nullptr;
     while(ptr){
         next = ptr->next ;
         ptr->next = prev;
         prev = ptr ; 
         ptr = next; 
     }
     first = prev ;
    }
};



int main()
{
    SLL l1;
    l1.insert_node(4);
    l1.insert_node(20);
    l1.insert_node(16);
    l1.display();
    l1.sort();
    l1.display(); 
    l1.reverse();
    l1.display();  

    return 0;
}
