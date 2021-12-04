#include<iostream>  
using namespace std; 

class Student{
    int age; 
    float income ;
    string city ; 
    string four_wheeler_brand;
    public:
    Student();
    template<class T>
    class Exception{
    friend class Student; 
      string error; 
      T value;
      public:
      Exception(string error , T value){
          this->error = error ;
          this->value = value ; 
      }

    };
    
    void accept_details();

};

Student::Student(){
    age = 0 ; 
    income = 0 ; 
    city = "";
    four_wheeler_brand = ""; 


}
void Student::accept_details(){
    try{
        cout<<"Enter the age of the student : ";
        cin>>age;
        if (age<18 || age>55){
            throw Student::Exception<int>("Exception occured in accept_details() function while entering age",age);
        }
        this->age = age; 
        cout<<"Enter the income of the person : ";
        cin>>income;
        if(income<50000 || income>100000 ){
            throw Student::Exception<float>("Exception occured in accept_details() function while entering income",income) ;

        }
        this->income = income;
        cout<<"Enter the Name of the city : ";
        cin>>city ; 
        if (city!="Pune" && city!="Mumbai"){
            throw Student::Exception<string>("Exception occured in accept_details() function while entering City",city);
        }
        this->city = city;

    }catch(Student::Exception<int> err_object){
        cerr<<err_object.error<<endl;
        
        cout<<"Invalid user age entered , it must be between 18 and 55"<<endl;
        cout<<"Entered age : "<<err_object.value;
        exit(0);

    }
    catch(Student::Exception<float> err_object){
        cerr<<err_object.error<<endl;
        cout<<"Invalid income mentioned , it should be between 50000 and 100000"<<endl;
        cout<<"Entered Income : "<<err_object.value<<endl;
        exit(0);
    }
    catch(Student::Exception<string> err_object){
        cerr<<err_object.error<<endl;
        cout<<"Invalid City Name entered , the options are Pune and Mumbai"<<endl;
        cout<<"Entered City : "<<err_object.value<<endl;
        exit(0);
    }
    try{
        cout<<"Enter the brand of your 4 wheeler : ";
        cin>>four_wheeler_brand;
        if(four_wheeler_brand!="Honda" && four_wheeler_brand!="Hyundai" && four_wheeler_brand!="Toyota"){
            throw Student::Exception<string>("Exception occured in accept_details() function while entering the four wheeler brand name",four_wheeler_brand);
        }
        this->four_wheeler_brand = four_wheeler_brand;
    }catch(Student::Exception<string> err_object){
        cerr<<err_object.error<<endl;
        cout<<"Invalid Brand Name entered , the options are {Honda , Hyundai , Toyota}"<<endl;
        cout<<"Entered Brand Name : "<<err_object.value<<endl;
        exit(0);
    }

}
int main()
{
    Student s1;
    s1.accept_details();
    return 0;
}

