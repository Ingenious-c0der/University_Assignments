#include <iostream>
#include <string.h>
using namespace std;
/*hierarchical inheritance
        Publication
            |
       _____|_____
       |         |
       V         V
      Book      Tape
*/
class Publication{
    protected:
    string title;
    float price;

};
class Book:private Publication{
    int page_count;
    public:
    void set_details();
    void get_details();

};
class Tape:private Publication{
    float play_time;
    public:
    void set_details();
    void get_details();


};
void Book::set_details(){
    
    try{
        cout<<"Enter the Title : ";
        cin.ignore();
        getline(cin,title);
        if (title.length()<3){
            cout<<"Invalid title entered"<<endl;
                throw title;

        }
        else{
            cout<<"Title valid,you may continue.."<<endl;
        }
         cout<<"Enter the price of the book : ";
         cin>>price;
          if (price<=0){
              cout<<"Invalid price entered"<<endl;
            throw price;
        }
        else{
            cout<<"Valid price given..you may continue"<<endl;
        }
         cout<<"Enter the number of pages : ";
          cin>>page_count;
        if (page_count<=0){
            cout<<"Invalid page count entered"<<endl;
            throw page_count;
        }
        else{
            cout<<"Valid page count given..you may continue"<<endl;
        }
    }catch(int page){
            title =" ";
            price = 0;
            page_count = 0;


        }
    catch(float p){
        title =" ";
        price = 0;
        page_count = 0;
    }
    catch(string t){
            title =" ";
            price = 0;
            page_count = 0;
    }
}

void Book::get_details(){
    cout<<"The title of the book is "<<title<<endl;
    cout<<"The price of the book is "<<price<<endl;
    cout<<"The page count of the book is "<<page_count<<endl;
}
void Tape::set_details(){
    
    try{
        cout<<"Enter the Title : ";
        cin.ignore();
        getline(cin,title);
        if (title.length()<3){
            cout<<"Invalid title entered"<<endl;
                throw title;

        }
        else{
            cout<<"Title valid,you may continue.."<<endl;
        }
         cout<<"Enter the price of the tape :";
         cin>>price;
          if (price<=0){
            cout<<"Invalid price given"<<endl;
            throw price;
        }
        else{
            cout<<"Valid price given..you may continue"<<endl;
        }
         
         
    }catch(float p){
            title =" ";
            price = 0;
            play_time = 0;
            return ;


        }
 
    catch(string t){
            title =" ";
            price = 0;
            play_time = 0;
    }
    try{
        cout<<"Enter the play time of the tape : "<<endl;
          cin>>play_time;
        if (play_time<=0){
            cout<<"Invalid play time entered"<<endl;
            throw play_time;
        }
        else{
            cout<<"Valid play time given..you may continue"<<endl;
        }
       
    }   catch(float play){
            title =" ";
            price = 0;
            play_time = 0;
    }
}
void Tape::get_details(){
    cout<<"The title of the tape is "<<title<<endl;
    cout<<"The price of the tape is "<<price<<endl;
    cout<<"The play time of the tape is "<<play_time<<endl;
}



int main(){
    Book b;
    b.set_details();
    b.get_details();
    Tape t;
    t.set_details();
    t.get_details();


    return 0;
}
