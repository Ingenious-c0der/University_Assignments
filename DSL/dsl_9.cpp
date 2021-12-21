#include<iostream>
using namespace std;

class Node{
    
        Node * prev; 
        char paren;
        Node(){
            paren = ' ';
            prev = nullptr;
        }
        Node(const char c){
            paren = c;
            prev = nullptr;
        }
    friend class Stack;
    
};
class Stack{
    Node * top = nullptr;
   
    public:
    Stack(string);
    void push(char);
    void pop();
    void display();
    bool iswellparenthesized();
    ~Stack();

};
Stack::Stack(string s){
    for(int i = 0 ; i<s.length();i++){
       
        if(top == nullptr){
            top = new Node(s[i]);
        }
        else{
           push(s[i]);
        }
        
    }
}
void Stack::pop(){
    if(top == nullptr){
        cout<<"Stack underflow"<<endl;
    }
    else{
        Node * to_delete = top;
        top = top->prev;
        delete to_delete;
    }
}

void Stack::display(){
    if(top==nullptr){
        cout<<"Stack is empty"<<endl;
        return ;
    }
    cout<<"Stack top-> ";
    for(auto ptr = top ; ptr!=nullptr ; ptr = ptr->prev){
        cout<<ptr->paren<<" ";
    }
    cout<<" <-Stack bottom"<<endl;
   
}
bool Stack::iswellparenthesized(){
    if(top==nullptr){
        return true;
    }else{
        return false;
    }
}

void Stack::push(char c){
    Node * temp = new Node(c);
    
    if((int)top->paren - (int)temp->paren<0 && (int)top->paren - (int)temp->paren> -3) //hunting a shorthand for this brb
    {pop();delete temp;} 
    else{
            temp->prev = top;
            top = temp;
        }

    
}

Stack::~Stack(){
    while(top!=nullptr){
        Node * to_delete = top;
        top = top->prev;
        delete to_delete;
    }
}


int main()
{
    
        string s ; 
        int choice;
        cout<<"Enter a string to check if it is well parenthesized or not : ";
        cin>>s;
        Stack st(s);
        while(true){
        cout<<"************Menu************\n1.Check if the stack is well parenthesized\n2.Push parenthesis to stack\n3.Display current Stack\n4.Pop from Stack\n5.Exit\nChoice: ";
        cin>>choice;
        switch(choice){
            case 1:
                st.iswellparenthesized()?cout<<"Stack is well parenthesized"<<endl:cout<<"Stack is not well parenthesized"<<endl;
                break;
            case 2:
                char c;
                cout<<"Enter a parenthesis to push to stack : ";
                cin>>c;
                st.push(c);
                break;
            case 3:
                st.display();
                break;
            case 4:
                st.pop();
                break;
            case 5:
                cout<<"Thankyou"<<endl;
                return 0;
            default:
                cout<<"Invalid choice"<<endl;
        }
    }
  

}
