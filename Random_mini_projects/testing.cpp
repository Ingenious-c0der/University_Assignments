#include <iostream>
using namespace std; 
class Test{

    public:
    static int z;
    int x,y;
    static void st_func(){
       void xyz();
       void cake();
    }
    public:
    Test();//default
    Test(int,int);//Parameterized 
    Test(Test &T);//Copy 
    void cake(int);
    ~Test();//Destructor

};
void xyz(){
    cout<<"works"<<endl;
}
int Test::z;
Test::Test(){
    cout<<"Default constructor called"<<endl;
    this->x = 0;
    this->y = 0;
}
Test::Test(int x,int y){
    cout<<"Parameterized contructor called"<<endl;
    
    x = x;
    y = y;
}
Test::Test(Test &T){
    cout<<"Copy contructor called"<<endl;
    this->x = T.x;
    this->y = T.y;

}
Test::~Test(){
    cout<<"Destructor was called"<<endl;
}
void Test::cake(int x){
    this->x = x;
    cout<<"this"<<endl;
   
}
int main(){
    Test t1;
    Test t3(3,4);
    t1.z = 4;
    t1.st_func();
    
   cout<<t3.z<<endl;
}
