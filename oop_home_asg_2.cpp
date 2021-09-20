#include <iostream>
using namespace std;
/* Single Inheritance
    Mathematics
        |
        V
    Addtion
*/
class Mathematics{
    protected:
      int a,b;
    public:
      void accept();
};

void Mathematics::accept(){
    cout<<"Enter the first number"<<endl;
    cin>> a;
    cout<<"Enter the number 2"<<endl;
    cin>>b;
}

class Addition: public Mathematics{
     public:
    void add();
};
void Addition::add(){
   
    cout<<"The sum is "<<a+b<<endl;
}

/* Multilevel inheritance 
    Class A
      |
      V
    Class B
      |
      V
    Class C

*/


class A {
    protected:
    int a ;

    public:

    void accept();
    void display();

};

class B:protected A{
    protected :int b;

    public:

    void accept();
    void display();

};

class C:protected B{
    private: int c;

    public:

    void accept();
    void display();

    
};

void A::accept(){
    cout<<"Enter the value"<<endl;
    cin>>a;
}

void A::display(){
    cout<<a;
}
void B::accept(){
    cout<<"Enter the value for a"<<endl;
    cin>>a;
    cout<<"Enter the value for b"<<endl;
    cin>>b;
}

void B::display(){
    cout<<"a :"<<a<<endl;
    cout<<"b :"<<b<<endl;
}

void C::accept(){
    cout<<"Enter the value for a"<<endl;
    cin>>a;
    cout<<"Enter the value for b"<<endl;
    cin>>b;
    
    cout<<"Enter the value for c"<<endl;
    cin>>c;
}

void C::display(){
    cout<<"a :"<<a<<endl;
    cout<<"b :"<<b<<endl;
    cout<<"c :"<<c<<endl;
}


/*
       Hierarchial inheritance
        Person 
          |
        __|__
        |   |
        V   V
    Student Employee

*/

class Person{
   protected:
   int age;
   string name;

};

class Student :private Person{
    private: int marks;
    public:
    void get_details();
    void set_details();
};

class Employee :private Person{
private: int salary;
public:
    void get_details();
    void set_details();
};

void Student::set_details(){
    cout<<"Enter the name "<<endl;
    cin>>name;
    cout<<"Enter the age "<<endl;
    cin>>age;
    cout<<"Enter the marks "<<endl;
    cin>>marks;

}
void Student::get_details(){
    cout<<"name "<<name<<endl;
    cout<<"Enter the age "<<age<<endl;
    cout<<"Enter the marks "<<marks<<endl;
    
    
}
void Employee::set_details(){
    cout<<"Enter the name "<<endl;
    cin>>name;
    cout<<"Enter the age "<<endl;
    cin>>age;
    cout<<"Enter the marks "<<endl;
    cin>>salary;

}
void Employee::get_details(){
    cout<<"name "<<name<<endl;
    cout<<"Enter the age "<<age<<endl;
    cout<<"Enter the marks "<<salary<<endl;
    
    
}

/*
Multiple Inheritance
General Info   Academic info
  |__________________|
           |
           V
        Employee
*/

class General_info{
  protected:
  string Name;
  int age;
  string address;
  public:
  void Accept1();
  void Display1();
};
class Academic_info{
    protected:
    int marks;
    char grade;
    public:
    void Accept2();
    void Display2();


};

class Employee_info:private General_info, private Academic_info{
    public:
   void Accept3();
   void Display3();
};


void General_info::Accept1(){
    cout<<"Enter the name ";
    cin>>Name;
    cout<<"Enter your age ";
    cin>>age;
    cout<<"Enter your address ";
    cin>>address;
}
void General_info::Display1(){
     cout<<"Name "<<Name;
     cout<<"Age "<<age;
     cout<<"Address "<<address;

}
void Academic_info::Accept2(){
    cout<<"Enter the marks ";
    cin>>marks;
    cout<<"Enter your grade ";
    cin>>grade;
  
}
void Academic_info::Display2(){
     cout<<"Marks "<<marks;
     cout<<"Grade "<<grade;
    

}
void Employee_info::Display3(){
     cout<<"Name "<<Name;
     cout<<"Age "<<age;
     cout<<"Address "<<address;
       cout<<"Marks "<<marks;
     cout<<"Grade "<<grade;

}

void Employee_info::Accept3(){
     cout<<"Enter the name ";
    cin>>Name;
    cout<<"Enter your age ";
    cin>>age;
    cout<<"Enter your address ";
    cin>>address;
    cout<<"Enter the marks ";
    cin>>marks;
    cout<<"Enter your grade ";
    cin>>grade;
    
}


int main(){
    // Addition a;
    // a.accept();
    // a.add();
    // return 0;
 
    // C c;
    // c.accept();
    // c.display();

    // Student s;
    // s.set_details();
    // s.get_details();
    // Employee e;
    // e.set_details();
    // e.get_details();


    
    Employee_info Ei;
    Ei.Accept3();
    Ei.Display3();
}
