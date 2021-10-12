#include<iostream>
using namespace std;

class Inventory1{
    int code, items;
    double price;
    public:

    Inventory1(){
        int code = 0  ;
        int items = 0 ; 
        double price = 0.0 ; 
    };

    Inventory1(int code,int items,double price){
            this-> code = code;
            this->items = items; 
            this-> price = price;
    }
    void show();
    int getItem();
    int getCode();
    double getPrice();
    operator double();



};
void Inventory1::show(){
    cout<<"The price per item is :"<<price<<endl;
    cout<<"The total items are : "<<items<<endl;
    cout<<"The code is :"<<code<<endl;
}
int Inventory1::getCode(){
   return code;
}
int Inventory1::getItem(){
    return items;
}
double Inventory1::getPrice(){
    return price;
}
Inventory1::operator double(){
    return price*items;
}
class Inventory2{
    int code ; double value; 
    public:
    Inventory2(){
        int code =0;
        double value = 0.0; 
    }
    void show();
    
    void operator = (Inventory1 &  obj){
        this->code = obj.getCode();
        this->value  = obj.getItem() * obj.getPrice();
    }

};
void Inventory2::show(){
    cout<<"The value is : "<<value<<endl;
    cout<<"The code is : "<<code<<endl;

}

int main()
{ 
     Inventory1 obj(100,5,140.8);
     double total_value;
     obj.show();
     total_value = obj;
     cout<<total_value<<endl;
     Inventory2 o;
     o = obj;
     o.show();
    
    return 0;
}