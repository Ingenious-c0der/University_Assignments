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
    string get_name(){return this->name; };
    

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
    vector<Employee>::iterator it;
while(1){
    cout<<"******Menu*******\n1. Add Employee\n2. Remove Employee\n3. Edit Employee\n4. Display All Employees \n5. Search Employee\n6. Sort Employees\n7.Exit"<<endl;
    int choice;
    cin>>choice;
    switch(choice){
        case 1:
        {
            Employee e ; 
            get_details(e);
            Employees.push_back(e);
            break;
        }

        case 2:
            cout<<"Enter the name of the Employee who is to be removed : ";
            cin>>Name;
            Employees.erase(remove_if(Employees.begin(), Employees.end(), [Name](Employee E){return (E.get_name() == Name);}),Employees.end());
            cout<<"Employees with name "<<Name<<" removed"<<endl;
            break;
        
        case 3:
        {
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
            break;
        }

        case 4:
            for_each(Employees.begin(),Employees.end(),display);
            break ;

        case 5:
            {
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
            break ;
            }

        case 6:
            std::sort(Employees.begin(),Employees.end());
            for_each(Employees.begin(),Employees.end(),display);
            break;
        case 7:
            exit(0);
    }




}

    return 0;
}
