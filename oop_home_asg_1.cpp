#include <iostream>
using namespace std;
class Test{
    int marks;
    static int count;
public:


    Test();
    Test(int);
    Test(Test&);
    ~Test();
    void set_marks(int);
    static void counter(int c){
        count+=c;
    }
    static void display_count(){
        cout<<"Currently there are "<<count<<" objects of the Test class"<<endl;
    };
};
Test::Test(){
    cout<<"Default Constructor called"<<endl;
    counter(1);
    marks = 0;
}
int Test::count;
Test::Test(int marks) {
    cout<<"Parameterized constructor called"<<endl;
    counter(1);
    this->marks = marks;
}
Test::Test(Test &t){
    cout<<"Copy Constructor called"<<endl;
    counter(1);
    this->marks = t.marks;

}
Test::~Test() {
    cout<<"Object having marks "<< marks <<" Destroyed."<<endl;
    counter((-1));
}
void Test::set_marks(int marks){
    this->marks = marks;
}
int main(){
    Test t1;
    Test::display_count();
    t1.set_marks(3);
    Test t2(4);
    Test t3 = t2;
    Test::display_count();

}
