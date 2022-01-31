#include <iostream>
using namespace std;
class Node{
    Node* next = nullptr ;
    bool Tag = false ;
    union{
        char data;
        Node* down = nullptr;
    }u;
    friend class GLL;
    explicit Node(char x ){
        next = nullptr;
        Tag = false;
        u.data = x ;
        u.down = nullptr;
    }
    Node(){
        next = nullptr;
        Tag = false;
        u.down = nullptr;
    }
    Node(char x , bool t){
        next = nullptr;
        Tag = t;
        u.data = x ;

    }
};
class GLL{
    Node* head ;
public:

    int iteration=0;
    GLL(){
        head = nullptr;
    }
    Node* create_GLL(string input ) {
        Node *q; Node *start = nullptr; Node *s = nullptr;
        while(input[this->iteration]!='\0') {

            if (input[this->iteration] == '(' and this->iteration!=0) {
                q = new Node();


                q->Tag = true;
                this->iteration +=1;
                q->u.down = create_GLL(input);

                if (!start) {
                    start = q;
                }
                else {
                    s = start;
                    while (s->next != nullptr) {
                        s = s->next;
                    }
                    s->next = q;
                }


            }
            else if(input[this->iteration]!='(' and input[this->iteration]!=')' and input[this->iteration]!= ','){
                q = new Node(input[this->iteration],false);

                if(start){
                    s = start;
                    while(s->next!= nullptr){
                        s = s->next;
                    }
                    s->next = q;
                }
                else{
                    start = q ;
                }
            }
            else if (input[this->iteration]==')'){
                return start;
            }
            this->iteration++ ;

        }
        this->head = start;
        return start;
    }
    void display_gll(Node* t ){
        Node* T = t;
        cout<<"(";
        while(T!=nullptr){
            if (T->Tag){

                display_gll(T->u.down);
            }else{
                if(T->next){
                    cout<<T->u.data<<",";
                }
                else{
                    cout<<T->u.data;
                }


            }

            T = T->next;

        }
        cout<<"),";


    }
    Node * get_head(){
        return this->head;
    }


};

int main_1(){
    GLL list ;
    list.create_GLL("(A,B,C,(D,(H,I),E),F");
    list.display_gll(list.get_head());

}
