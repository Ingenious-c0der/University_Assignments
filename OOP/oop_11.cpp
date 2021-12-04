#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;


class Employee{
    string name;
    int id ; 
    int salary;
    public:
    Employee();
    Employee(string name);
    Employee(string, int, int);
    int operator == (Employee);
    bool sort_function(Employee&, Employee&);
    bool operator<(const Employee&);
    void edit_employee();
    friend bool remove_emp(Employee& ,string);
    void show_details();
    friend void get_details(Employee&);
    

};
Employee::Employee(){
    name = "";
    id = 0;
    salary = 0;
}
Employee::Employee(string name){
    this->name = name;
    id = 0;
    salary = 0;
}
Employee::Employee(string name, int id, int salary){
    this->name = name;
    this->id = id;
    this->salary = salary;
}
void get_details(Employee & E){
    cout<<"Enter the name of the employee : ";
    cin>>E.name;
    cout<<"Enter the id of the employee : ";
    cin>>E.id;
    cout<<"Enter the salary of the employee : ";
    cin>>E.salary;
}
bool Employee::operator<(const Employee& E){
    return salary > E.salary;
}

int Employee::operator == (Employee E){
    if(this->name == E.name){
        return 1;
    }
    return 0;
}
bool Employee::sort_function(Employee& E1, Employee& E2){
    return E1.salary > E2.salary;
}

bool remove_emp(Employee& E, string name){
    if(E.name == name){
        return 1;
    }
    return 0;
}


void Employee::show_details(){
    cout<<"Name: "<<name;
    cout<<"\tID: "<<id;
    cout<<"\tSalary: "<<salary<<endl;
}
void display(Employee& e){
    e.show_details();
}
int main()
{   string Name;
    vector<Employee> Employees;
while(1){
    cout<<"******Menu*******\n1. Add Employee\n2. Remove Employee\n3. Edit Employee\n4. Display Employee\n5. Exit\n"<<endl;
    int choice;
    cin>>choice;
    switch(choice){
        

    }//too lazy to implement switch , ignore 79-88 if you want :)




}

    //creating vector of Employee objects
    vector<Employee> Employees;
    Employee e1,e2,e3;
    Employees.push_back(e1);
    Employees.push_back(e2);
    Employees.push_back(e3);

    //getting the details of the employees
    for_each(Employees.begin(),Employees.end(),get_details);
    cout<<"Employee details entered : "<<endl;
    for_each(Employees.begin(),Employees.end(),display);
    cout<<"***********************"<<endl;
    //searching for an employee for his details
    cout<<"Enter the name of the employee to be searched : ";
    cin>>Name;
    Employee to_search(Name);
    vector<Employee>::iterator it;
    it = find(Employees.begin(),Employees.end(),to_search);
    if (it!=Employees.end()){
        cout<<"Employee found"<<endl;
        it->show_details();
        cout<<"***********************"<<endl;
        
    }
    else{
        cout<<"Employee not found"<<endl;
    }

    //sorting employees according to their salaries
    std::sort(Employees.begin(),Employees.end());

    //displaying sorted employees
    for_each(Employees.begin(),Employees.end(),display);


    //removing an employee by name
    cout<<"Enter the name of the Employee who is to be removed : ";
    cin>>Name;
    remove_if(Employees.begin(), Employees.end(), [Name](Employee& E){return remove_emp(E,Name);}); // using lambda expression to pass in extra parameter
    cout<<"Employees with name "<<Name<<" removed"<<endl;
    
    //editing the employee
    cout<<"Enter the Name of the employee to be edited : ";
    cin>>Name;
    Employee to_search_2(Name);
    it = find(Employees.begin(),Employees.end(),to_search_2);
    if (it!=Employees.end()){
        cout<<"Employee found"<<endl;
        cout<<"Re enter the employee details please : "<<endl;
        get_details(*it);
        cout<<"Employee details edited , New Details are :  "<<endl;
        it->show_details();
        cout<<"***********************"<<endl;
    }
    else{
        cout<<"Employee not found"<<endl;
    }


    cout<<"Final Employee details after operations : "<<endl;
    for_each(Employees.begin(),Employees.end(),display);


    return 0;
}
