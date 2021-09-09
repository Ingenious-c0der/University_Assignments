
#include <iostream>
#include <string.h>
using namespace std;
class Student{

	char* Name;
	char* roll_no;
	char* Cls;
	char* div;
	char* dob;
	char* blood_grp;
	char* address;
	long long int tele_no;
	int license_no;

	public:
	//Constructor Definitions
	Student();//Default
	Student(char* , char* ,char* ,char* ,char*,char*,char *,long long int ,int);//Parameterized
	Student (Student &);//Copy
	~Student(); //Destructor


	//Overloaded insertion and extraction operators
	friend istream& operator >> (istream& input, Student &S);
	friend ostream& operator << (ostream& output,Student &S);
	void get_details();

};

//Parameterized Constructor
Student::Student(  char* Name,  char* roll_no, char* Cls, char* div,
char* dob, char* blood_grp, char*  address,long long int tele_no,int license_no){
	int length;
		length = strlen(Name);
		this->Name = new char[length];
		this->Name = Name;

		length = strlen(roll_no);
		this->roll_no = new char[length];
		this->roll_no =roll_no;

		length = strlen(Cls);
		this->Cls = new char[length];
		this->Cls = Cls;

		length = strlen(div);
		this->div = new char[length];
		this->div =div;

		length = strlen(dob);
		this->dob = new char[length];
		this->dob =dob;

		length = strlen(blood_grp);
		this->blood_grp = new char[length];
		this->blood_grp =blood_grp;

		length = strlen(address);
		this->address = new char[length];
		this->address = address;

		this->tele_no = tele_no;
		this->license_no = license_no;

}
//Default Constructor
Student::Student(){
	Name = new char;
	roll_no = new char;
	Cls =new char;
	div = new char;
	dob = new char;
	blood_grp = new char;
	address = new char;
	tele_no = 0;
	license_no = 0;

}
//Copy Constructor
Student::Student(Student &S){
	Name = S.Name;
	roll_no = S.roll_no;
	Cls = S.Cls;
	div = S.div;
	dob = S.dob;
	blood_grp = S.blood_grp;
	address = S.address;
	tele_no = S.tele_no;
	license_no = S.license_no;
}
//Destructor
Student::~Student(){
	delete Name;
	delete roll_no;
	delete Cls;
	delete blood_grp;
	delete address;
	delete dob;
	delete div;
}

ostream& operator << (ostream& output,Student &S){
		cout<<"*********Following are the details of the Student********"<<endl;
		cout<<"Name : "<<S.Name<<endl;
		cout<<"Address :"<<S.address<<endl;
		cout<<"Class : "<<S.Cls<<endl;
		cout<<"Date of Birth : "<<S.dob<<endl;
		cout<<"Blood Group : "<<S.blood_grp<<endl;
		cout<<"License Number : "<<S.license_no<<endl;
		cout<<"Roll number : "<<S.roll_no<<endl;
		cout<<"Division : "<<S.div<<endl;
		cout<<"Phone Number : "<<S.tele_no<<endl;
		return output;
}

istream& operator >> (istream& input, Student &S ){
		cout<<"Enter the Name of the student :";
		cin>>S.Name;
		cout<<"Enter the address of the student : ";
		cin>>S.address;
		cout<< "Enter the blood group of the student :";
		cin>>S.blood_grp;
		cout<<"Enter the Date of Birth of the student :";
		cin>>S.dob;
		cout<<"Enter the roll_no,Class of the student : ";
		cin>>S.roll_no>>S.Cls;
		cout<<"Enter the telephone number and the driving license number of the student :";
		cin>>S.tele_no>>S.license_no;
		cout<<"Enter the Division of the student : ";
		cin>>S.div;
		return input;

	}
inline void Student::get_details(){
		cout<<"Enter the Name of the student :";
		cin>>this->Name;
		cout<<"Enter the address of the student : ";
		cin>>this->address;
		cout<< "Enter the blood group of the student :";
		cin>>this->blood_grp;
		cout<<"Enter the Date of Birth of the student :";
		cin>>this->dob;
		cout<<"Enter the roll_no,Class of the student : ";
		cin>>this->roll_no>>this->Cls;
		cout<<"Enter the telephone number and the driving license number of the student :";
		cin>>this->tele_no>>this->license_no;
		cout<<"Enter the Division of the student : ";
		cin>>this->div;

}



int main() {
	char* Name =new char;
	char* address=new char;
	char* roll_no =new char;
	char* Cls =new char;
	char* div = new char;
	char* dob = new char;
	char* blood_grp =new char;
	long long int tele_no;
	int license_no;
	
		cout<<"Enter the Name of the student :";
		cin>> Name;
		cout<<"Enter the address of the student : ";
		cin>>address;
		cout<< "Enter the blood group of the student :";
		cin>>blood_grp;
		cout<<"Enter the Date of Birth of the student :";
		cin>>dob;
		cout<<"Enter the roll_no,Class of the student : ";
		cin>>roll_no>>Cls;
		cout<<"Enter the telephone number and the driving license number of the student :";
		cin>>tele_no>>license_no;
		cout<<"Enter the Division of the student : ";
		cin>>div;
	Student s0(Name,roll_no,Cls,div,dob,blood_grp,address,tele_no,license_no);
	Student s1;
	cin>>s1;
	Student s2=s1;
	Student s3;
	s3.get_details();
	cout<<s0;
	cout<<s1;
	cout<<s2;
	cout<<s3;
	return 0;
}
