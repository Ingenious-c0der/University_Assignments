#include <iostream>
using namespace std; 

template<class detail,class name>
class Personal {
protected:
	name Name; detail Detail;
public:
	Personal() {
		Name = "";
		Detail = "";
	};
};

template<class detail ,class name,class EmployeeBio, int employee_id>
class Employee :private Personal<detail, name> {
	EmployeeBio em_bio;
public:
	Employee(detail , name , EmployeeBio);
	void show_em_details();
};


template<class detail ,class name,class EmployeeBio,int employee_id>
Employee<detail,name,EmployeeBio,employee_id>::Employee(detail d, name em_Name,EmployeeBio Eb) {
	this->Detail = d;
	this->Name = em_Name;
	em_bio = Eb;
}


template<class detail, class name, class EmployeeBio, int employee_id>
void Employee<detail,  name, EmployeeBio, employee_id>::show_em_details(){
	cout << this->Detail << endl;
	cout << this->Name << endl;
	cout << em_bio << endl;
	cout << employee_id << endl;

}


int main() {
	Employee<string, string, string,3532302> e1("Pro","Employee","10+years of experience");
	e1.show_em_details();
}
