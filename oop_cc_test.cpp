#include<iostream>
using namespace std;
// Problem Statement----
// Create a class User as base class, inherit 1st student class => read subject(), delete student(), add student(),tick
// inherit 2nd faculty class=> read subject(), calculate marks(), delete faculty() tick ;
// Make use of constructor, destructor, overload operator >>, << to read and display subject, function overriding and dynamic memory allocation.  Finally count number of student and faculty  display the same.
// Use linked list subject structure for storing user details. tick
class Student;
class Faculty;
class User{
    protected:
    char* name; int id;int dob;char* blood_grp;
    public:
    User(){
        name = new char;
        blood_grp = new char;
        id = 0;
        dob=0;
    }

    
    ~User(){
        delete name;
        delete blood_grp;
    }
    void readdata();
    friend ostream& operator <<(ostream&,User&);
    friend istream& operator >>(istream&,User&);



};

void User::readdata(){
    cout<<"Enter the name of the User : ";
    cin>>name;
    cout<<"Enter the id of the User : ";
    cin>>id;
    cout<<"Enter the blood group of the User";
    cin>>blood_grp;
    cout<<"Enter the Date of Birth of the user";
    cin>>dob;


}
ostream& operator<<(ostream& out, User& User){
    cout<<"The name of the User is "<<User.name<<endl;
    cout<<"The date of birth of the User is "<<User.dob<<endl;
    cout<<"The id of the user is "<<User.id<<endl;
    cout<<"The blood group of the user is "<<User.blood_grp<<endl;
    return out;
}

istream& operator>>(istream& in,User&User){
    cout<<"Input the name of the user :";
    cin>>User.name;
    cout<<"Input the id of the user :";
    cin>>User.id;
    cout<<"Input the blood group of the User :";
    cin>>User.blood_grp;
    cout<<"Input the date of birth of the User :";
    cin>>User.dob;
    return in;

}

struct node{
 string subject;
 int marks;
 node* link; 
};
class LinkList
{
    node *first;
    public:
    LinkList()
    {   
        first=NULL;
    }
    void AddItem(string,int);
    void AddEnd(string,int);
    void ShowItem();
    void AddItemindex(string,int,int);
    string DeleteFirst();
    string DeleteLast();
    string DeleteIndex(int );
    int Get_total_marks();
};
void LinkList ::AddItem(string x,int m)
    {
    node *temp=new node;
    temp->subject=x;
    temp->marks = m;
    temp->link=first;
    first=temp;
    }

void LinkList ::ShowItem()
    {
    node *ptr=first;
    cout<<"\n The subjects taken by the student and the respective marks are :"<<endl;
    while(ptr!=NULL)
    { 
        cout<<"Subject: "<<ptr->subject<<"  Marks: "<<ptr->marks<<endl;
        ptr=ptr->link;
    }
}
void LinkList ::AddEnd(string x,int m )
    {
    node*ptr = first;
    while (ptr->link!=NULL)
    {
            ptr = ptr->link;
    }
    node * new_ptr = new node;
    new_ptr->subject = x;
    new_ptr->marks = m ; 
    new_ptr->link = NULL;
    ptr->link= new_ptr;
}

int LinkList::Get_total_marks(){
    node *ptr=first;
   int total_marks = 0 ; 
    while(ptr!=NULL)
    { 
        total_marks+=ptr->marks;
        ptr=ptr->link;
    }
    return total_marks;
}

void LinkList::AddItemindex(string val,int m,int index){

    node *ptr = first;
    for (int i = 0; i<index-1;i++){
        ptr = ptr->link;

    }
    node * new_ptr = new node;
    node *intermidiate_link = ptr->link;
    ptr->link = new_ptr;
    new_ptr->subject = val;
    new_ptr->marks = m ; 
    new_ptr->link = intermidiate_link;

    
}string LinkList::DeleteFirst(){
    node*temp = first;
    first = first->link;
    
    return temp->subject;
    delete(temp);

}
string LinkList::DeleteLast(){
    string val;
    node*ptr = first;
    
    while (ptr->link->link!=NULL){
        ptr = ptr->link;
    }
    val = ptr->link->subject;
    ptr->link = NULL;
    return val;
}

string LinkList::DeleteIndex(int index){
    node *ptr = first;
        for (int i=0;i<index-1;i++){
            
              ptr = ptr->link;
        }
        node*temp = ptr->link;
        string val = ptr->subject;
        ptr->link = temp->link;
        return val;
        delete temp;

}


class Faculty :private User{
    string department ;int years_of_experience;string* subjects;int total_subjects;
    static int faculty_count;
    public:
    Faculty(){
        department = "";
        years_of_experience = 0 ;
        subjects = new string;
        faculty_counter(1);
        total_subjects = 0 ; 

    }
    static void faculty_counter(int c){
            faculty_count = faculty_count+c;
    }
    friend istream& operator >>(istream&,Faculty&);
    friend ostream& operator<<(ostream&,Faculty&);
    void readsubjects(){
        subjects = new string[total_subjects];
        for (int i =0; i<total_subjects;i++){
            cout <<"Enter the name of the subject : ";
            cin>>subjects[i];

        }
    }
    ~Faculty(){
        delete subjects;
        

    }
    void calculate_marks(Student student);

    
    static int get_faculty_count(){
        cout<<"The faculty count is "<<faculty_count<<endl;
        return faculty_count;
    }

};



istream& operator>>(istream& input,Faculty& F){
    int total_subjects;
   cout<<"Enter the name of the Faculty : ";
   cin>>F.name;
   cout<<"Enter the Department of the Faculty : ";
   cin>>F.department;
   cout<<"Enter the years of experience of the faculty : ";
   cin>>F.years_of_experience;
   cout<<"Input the id of the Faculty :";
   cin>>F.id;
    cout<<"Input the blood group of the Faculty : ";
    cin>>F.blood_grp;
    cout<<"Input the date of birth of the Faculty : ";
    cin>>F.dob;
    cout<<"Enter the number of subjects which the faculty teaches : ";
    cin>>F.total_subjects;
    F.readsubjects();
    return input;
    

}
ostream& operator<<(ostream& out,Faculty &F){
    cout<<"the name of the Faculty : "<<F.name<<endl;
   cout<<" the Department of the Faculty : "<<F.department<<endl;
   cout<<"the years of experience of the faculty : "<<F.years_of_experience<<endl;
   cout<<"the id of the Faculty : "<<F.id<<endl;
    cout<<" the blood group of the Faculty : "<<F.blood_grp<<endl;
    cout<<" the date of birth of the Faculty : "<<F.dob<<endl;
    cout<<" the number of subjects which the faculty teaches : "<<F.total_subjects<<endl;
    cout<<"The subjects taught by the faculty are :";
    for(int i= 0 ; i<F.total_subjects;i++){
        cout<<F.subjects[i]<<" and ";
    }
    cout<<" "<<endl;
    return out;

}










class Student :private User{
    static int student_count;
    protected:
    LinkList subjects;
    public:
    Student(){
        Student_counter(1);
    }
    friend class Faculty;
    friend istream& operator >>(istream&,Student&);
    friend ostream& operator<<(ostream&,Student&);



    void addstudent(){
    int total_subjects;
    cout<<"Enter the name of the Student : ";
    cin>>name;
    cout<<"Enter the id of the Student : ";
    cin>>id;
    cout<<"Enter the blood group of the Student : ";
    cin>>blood_grp;
    cout<<"Enter the Date of Birth of the Student: ";
    cin>>dob;
    cout<<"Enter the total number of subjects of the student";
    cin>>total_subjects;
    for (int i= 0 ; i< total_subjects;i++){
        string subject; int marks;
        cout<<"Enter the Subject " <<i+1<< " :";
        cin>>subject;
        cout<<"Enter the marks for subject "<<subject<<" :";
        cin>>marks;
        subjects.AddItem(subject,marks);
    }
    cout<<"The student is registered , Thankyou!"<<endl;

    }
    void deleteStudent(Student  S){
        delete &S;
    }
    static void Student_counter(int c){
        student_count = student_count+c;
    }
    ~Student(){
        Student_counter(-1);
        delete &subjects;
    }
    static int get_Student_count(){
        cout<<"The student count is "<<student_count<<endl;
        return student_count;
    }

    
    
};
int Student::student_count =0 ;
int Faculty::faculty_count = 0 ; 


istream& operator >>(istream& in,Student& S){
    int total_subjects;
    cout<<"Enter the name of the Student : ";
    cin>>S.name;
    cout<<"Enter the id of the Student : ";
    cin>>S.id;
    cout<<"Enter the blood group of the Student : ";
    cin>>S.blood_grp;
    cout<<"Enter the Date of Birth of the Student: ";
    cin>>S.dob;
    cout<<"Enter the total number of subjects of the student";
    cin>>total_subjects;
    for (int i= 0 ; i< total_subjects;i++){
        string subject; int marks;
        cout<<"Enter the Subject " <<i+1<< " :";
        cin>>subject;
        cout<<"Enter the marks for subject "<<subject<<" :";
        cin>>marks;
        S.subjects.AddItem(subject,marks);
    }
    cout<<"The student is registered , Thankyou!"<<endl;
    return in;

}

ostream& operator<<(ostream& out,Student& S){

    cout<<"The name of the User is "<<S.name<<endl;
    cout<<"The date of birth of the User is "<<S.dob<<endl;
    cout<<"The id of the user is "<<S.id<<endl;
    cout<<"The blood group of the user is "<<S.blood_grp<<endl;
    S.subjects.ShowItem();
    return out;


}
void Faculty::calculate_marks(Student student){
        int total; LinkList subject_list;
        subject_list = student.subjects;
        total = subject_list.Get_total_marks();
        cout<<"The total marks of student as calculated by the faculty are "<<total<<endl;
}


int main()
{   
  Faculty f;
  Student s;
  cin>>f;
  cin>>s;
  cout<<f;
  cout<<s;
  cout<<Faculty::get_faculty_count()+Student::get_Student_count()<<endl;
  f.calculate_marks(s);
  


    
    return 0;
}
