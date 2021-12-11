// Write C++ program for storing binary number using doubly linked lists. Write functions-  

// a) To compute 1‘s and 2‘s complement  

// b) Add two binary numbers  

#include<iostream>
#include<string.h>
#include <bits/stdc++.h>
using namespace std;
class Node;
class Node{
int bit;
Node * next;
Node * prev;
friend class BinaryLL;
};

class BinaryLL{
Node * first = new Node; 
int bits = 0 ;   
public: 
char sum_table[2][2][2] = {{{'0','1'},{'1','0'}},{{'1','0'},{'0','1'}}};
int carry_table[2][2][2] = {{{0,0},{0,1}},{{0,1},{1,1}}};
BinaryLL(const char*);
 ~BinaryLL(); 
 void set_first(); 
 void addbit(int );
 void reverse_display();
 void display(); 
 void ones_complement(); 
 void twos_complement(); 
 BinaryLL addbinary(BinaryLL&);
 BinaryLL addbinary_2(BinaryLL&);
};
void BinaryLL::set_first(){ 
    first->next = nullptr; 
    first->prev = nullptr;
}


BinaryLL::BinaryLL(const char* binary){ 
    int l = strlen(binary); bits = l ;  
    set_first(); 
    for(int i = 0 ; i<l;i++) 
    {   
        addbit(int(binary[l-i-1])-48);  
    }
}
void BinaryLL::addbit(int bit){  
    Node * temp = new Node;   
    temp->next = first->next;   
    if (first->next){    first->next->prev = temp;   }
       temp->prev = first;   
       temp->bit = bit ;    
       first->next = temp;   
}
BinaryLL::~BinaryLL(){ 
    Node * ptr = first;  
    Node * temp ;  
    while(ptr!=nullptr)
    {   temp = ptr->next;   
    delete ptr;   
    ptr = temp; } 
    
} 
void BinaryLL::display(){ 
    for(auto ptr = first->next ; ptr!=nullptr;ptr = ptr->next) 
    { cout<<ptr->bit<<" "; } 
    cout<<endl;
}

void BinaryLL::ones_complement(){
     for(auto ptr = first->next ; ptr!=nullptr;ptr = ptr->next) 
     {    if(ptr->bit == 0)
     {   ptr->bit=1;   }   
     else{   ptr->bit=0;   } }

}
void BinaryLL::twos_complement()
{ ones_complement(); Node * last ;
 for(auto ptr = first->next; ptr!=nullptr;ptr=ptr->next){   last = ptr; }   
 for(auto ptr = last;ptr!=nullptr;ptr = ptr->prev) {   
     if (ptr->bit==0){    
         ptr->bit = 1;    
         return ;    
         }  
          else{    
              ptr->bit = 0;   } 
              }
               cout<<"carry generated : "<<1<<endl; 
}
BinaryLL BinaryLL::addbinary(BinaryLL& other){
    //"not so efficient with all those if else statements during pipelining in cpu" - Le Zope Sir
        int carry = 0; 
        Node * last_self = nullptr; 
        Node * last_other  = nullptr;
        Node * temp  = nullptr; 
        Node * last  = nullptr;
        int max_bit = this->bits>other.bits ? this->bits:other.bits ;
        
        int i = 0 ;
        char* bin_str = new char[max_bit];

        for(auto ptr = first->next; ptr!=nullptr;ptr=ptr->next){last_self = ptr;} 
        for(auto ptr = other.first->next; ptr!=nullptr;ptr=ptr->next){last_other = ptr;} 

        last = this->bits>other.bits ? last_self:last_other; 
        for(auto ptr = last,ptr_2 = this->bits>other.bits ? last_other:last_self ; ptr_2->prev!=nullptr; ptr = ptr->prev,ptr_2 = ptr_2->prev,i++){

            
            if (ptr->bit + ptr_2->bit + carry == 3){  
                bin_str[i] = '1';  
                carry = 1;  
            }  
            else if (ptr->bit + ptr_2->bit + carry == 2){  
                bin_str[i] = '0';  
                carry = 1;  
            }  
            else if (ptr->bit + ptr_2->bit + carry == 1){  
                bin_str[i] = '1';  
                carry = 0;  
            }  
            else if (ptr->bit + ptr_2->bit + carry == 0){  
                bin_str[i] = '0';  
                carry = 0;  

            } 
            temp = ptr; 

        }
        
        for(auto ptr = temp->prev; ptr!=nullptr;ptr = ptr->prev){  
            if (ptr->bit + carry == 2){  
                bin_str[i] = '0';  
                carry = 1;  
            }  
            else if (ptr->bit + carry == 1){  
                bin_str[i] = '1';  
                carry = 0;  
            }  
            else if (ptr->bit + carry == 0){  
                bin_str[i] = '0';  
                carry = 0;  
            } 
            i++;
         
        }
        
        for(int i= 0 ; i<max_bit/2;i++){  
            swap(bin_str[i],bin_str[max_bit-i-1]);
        }

        BinaryLL result = BinaryLL(bin_str);
        delete[] bin_str;
        
        
        return result;
        

    
}

BinaryLL BinaryLL::addbinary_2(BinaryLL& other) {
    //making it more efficient by adding a hash table for binary addition without using if else statements

     int carry = 0; 
        Node * last_self = nullptr; 
        Node * last_other  = nullptr;
        Node * temp  = nullptr; 
        Node * last  = nullptr;
        int max_bit = this->bits>other.bits ? this->bits:other.bits ;
        
        int i = 0 ;
        char* bin_str = new char[max_bit];

        for(auto ptr = first->next; ptr!=nullptr;ptr=ptr->next){last_self = ptr;} 
        for(auto ptr = other.first->next; ptr!=nullptr;ptr=ptr->next){last_other = ptr;} 

        last = this->bits>other.bits ? last_self:last_other; 
        for(auto ptr = last,ptr_2 = this->bits>other.bits ? last_other:last_self ; ptr_2->prev!=nullptr; ptr = ptr->prev,ptr_2 = ptr_2->prev,i++)
        {
            bin_str[i] = sum_table[carry][ptr->bit][ptr_2->bit];

            carry = carry_table[carry][ptr->bit][ptr_2->bit];
            
            temp = ptr; 
            
        }
        for(auto ptr = temp->prev; ptr->prev!=nullptr;ptr = ptr->prev){
 
            bin_str[i] = sum_table[carry][ptr->bit][0];
            carry = carry_table[carry][ptr->bit][0];
            i++;
        }
        for(int i= 0 ; i<max_bit/2;i++){  
            swap(bin_str[i],bin_str[max_bit-i-1]);
        }

        BinaryLL result = BinaryLL(bin_str);
        
        delete[] bin_str;
        
        
        return result;

}
int main(){  
    
    BinaryLL bin_list("1001111") ;
    BinaryLL bin_list_2("1111") ;
    BinaryLL result = bin_list.addbinary_2(bin_list_2);
    result.display();

    return 0 ; 

}
