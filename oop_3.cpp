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
    int play_time;
    public:
    void set_details();
    void get_details();


};
void Book::set_details(){
    cout<<"Enter the Title : ";
    try{
        cin>>title;
        if (title.length()<3){
                throw title;

        }
        else{
            cout<<"Title valid,you may continue.."<<endl;
        }
         cout<<"Enter the price of the book : ";
         cin>>price;
          if (price<=0){
            throw price;
        }
        else{
            cout<<"Valid price given..you may continue"<<endl;
        }
         cout<<"Enter the number of pages : ";
          cin>>page_count;
        if (page_count<=0){
            throw page_count;
        }
        else{
            cout<<"Valid page count given..you may continue"<<endl;
        }
    }catch(int page_count){
            this->title =" ";
            this->price = 0;
            this->page_count = 0;


        }
    catch(float price){
        this->title =" ";
        this->price = 0;
        this->page_count = 0;
    }
    catch(string title){
            this->title =" ";
            this->price = 0;
            this->page_count = 0;
    }
}

void Book::get_details(){
    cout<<"The title of the book is "<<title<<endl;
    cout<<"The price of the book is "<<price<<endl;
    cout<<"The page count of the book is "<<page_count<<endl;
}
void Tape::set_details(){
    cout<<"Enter the Title : ";
    try{
        cin>>title;
        if (title.length()>3){
                throw title;

        }
        else{
            cout<<"Title valid,you may continue.."<<endl;
        }
         cout<<"Enter the price of the book :";
         cin>>price;
          if (price<=0){
            throw price;
        }
        else{
            cout<<"Valid price given..you may continue"<<endl;
        }
         cout<<"Enter the play time of the tape : "<<endl;
          cin>>play_time;
        if (play_time<=0){
            throw play_time;
        }
        else{
            cout<<"Valid page time given..you may continue"<<endl;
        }
    }catch(int play_time){
            this->title =" ";
            this->price = 0;
            this->play_time = 0;


        }
    catch(float price){
       this->title =" ";
            this->price = 0;
            this->play_time = 0;
    }
    catch(string title){
        this->title =" ";
            this->price = 0;
            this->play_time = 0;
    }
}
void Tape::get_details(){
    cout<<"The title of the book is "<<title<<endl;
    cout<<"The price of the book is "<<price<<endl;
    cout<<"The play time of the book is"<<play_time<<endl;
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
