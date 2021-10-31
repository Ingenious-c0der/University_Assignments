#include<iostream>
using namespace std;

struct node{
    int roll_no=0;
    node*link;
};
class SetLinkList{
private:
    node* first = nullptr;
public:

    SetLinkList();
    SetLinkList(const SetLinkList&);
    ~SetLinkList();
    void AddItem(int);
    void showItems();
    bool item_check(int);
    SetLinkList intersection(SetLinkList);
    SetLinkList Union(const SetLinkList&);
    SetLinkList* operator = (const SetLinkList&);
};
SetLinkList* SetLinkList::operator=(const SetLinkList & old_list) {
    for (node* ptr =old_list.first; ptr!= nullptr;ptr=ptr->link)
        AddItem(ptr->roll_no);
    return this;
}
SetLinkList::SetLinkList() {first= nullptr;}
SetLinkList::SetLinkList(const SetLinkList& old_list){
    for (node* ptr =old_list.first; ptr!= nullptr;ptr=ptr->link)
        AddItem(ptr->roll_no);}

SetLinkList::~SetLinkList() {

    node* ptr = first;
    node * temp;
    while(ptr!=nullptr){
        temp = ptr->link;
        delete ptr;
        ptr = temp;
    }
    delete temp;
    delete ptr;
}


void SetLinkList ::AddItem(const int m){
    node *temp=new node;
    if (!item_check(m)){
        temp->roll_no =  m;
        temp->link=first;
        first=temp;
    }
}
bool SetLinkList::item_check(const int m){

    for(auto ptr = first;ptr!= nullptr;ptr=ptr->link){
        if (ptr->roll_no == m)
            return true;
    }

    return false;
}

void SetLinkList::showItems(){
        for (auto ptr = first;ptr!= nullptr;ptr=ptr->link)
            cout << ptr->roll_no << " ";

}

SetLinkList SetLinkList::intersection(SetLinkList set_other){
    SetLinkList new_set;
    for(auto ptr = first;ptr!= nullptr;ptr=ptr->link){
        if(item_check(ptr->roll_no) && set_other.item_check(ptr->roll_no)){
            new_set.AddItem(ptr->roll_no);
        }
    }
    return new_set;
}
SetLinkList SetLinkList::Union(const SetLinkList& set_other){
    SetLinkList new_set = set_other;
    for(auto ptr = first; ptr!= nullptr;ptr=ptr->link)
            new_set.AddItem(ptr->roll_no);



    return new_set;
}






int main()
{   int van , but, n ,choice,total;
    cout<<"Enter the total number of students";
    cin>>total;
    SetLinkList vanilla,butterscotch;
    cout<<"Enter the number of students who like vanilla ice-cream : ";
    cin>>van;
    for(int i= 0 ; i<van;i++) {
        cout << "Enter the roll no of the student : ";
        cin>>n ;
        if(vanilla.item_check(n)) {
            cout << "Roll number already used! Enter another roll_no.";
            cin>>n;
            vanilla.AddItem(n);

        }else{
            vanilla.AddItem(n);
        }
    }


    cout<<"Enter the number of students who like butterscotch ice-cream : ";
    cin>>but;
    for(int i = 0 ; i<but;i++) {
        cout << "Enter the roll no of the student : ";
        cin >> n;

        if (butterscotch.item_check(n)) {
            cout << "Roll number already used! Enter another roll_no : ";
            cin >> n;
            butterscotch.AddItem(n);

        } else {
            butterscotch.AddItem(n);
        }
    }
    while(true){
        cout<<"*****MENU*******\nSelect a choice\n1)Set of students who like both vanilla and butterscotch\n2) Set of students who like either vanilla or butterscotch or not both  \n3) Number of students who like neither vanilla nor butterscotch\n4)Exit\nChoice :  ";
        cin>>choice;
        switch(choice){
            case 1:{
                SetLinkList case1;
                case1 = vanilla.intersection(butterscotch);
                case1.showItems();
                cout<<endl;
                break;
            }
            case 2:{
                SetLinkList case2;
                for(int i = 0;i<total;i++)
                    if(!(vanilla.item_check(i+1)&&butterscotch.item_check(i+1)))
                        case2.AddItem(i + 1);

                case2.showItems();
                cout<<endl;
                break;
            }
            case 3:{
                SetLinkList case3, Union_set;
                Union_set = vanilla.Union(butterscotch);
                for(int i = 0;i<total;i++)
                    if(!(Union_set.item_check(i+1)))
                        case3.AddItem(i+1);
                case3.showItems();
                cout<<endl;
                break;
            }
            case 4:{
                cout<<"Thank you"<<endl;
                exit(0);
            }

        }
    }
}
