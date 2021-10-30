#include<iostream>
#include<fstream>
using namespace std;

//using extraction and insertion operators
void write_to_file_e(string filename){
    string data;
    string choice; 
    ofstream out; 
    out.open(filename);
    if (!out.fail()){
        while(true){
            cout<<"Enter the name and age of the person : ";
            cin.sync();
            getline(cin,data);
            out<<data<<endl;
            cout<<"Have more data?(Y/N) : ";
            cin>>choice;
            if (choice=="N") break; 
        }
    cout<<"file closed successfully after writing"<<endl;
    }
    else{
        cerr<<"Something went wrong."<<endl;
    }

}
void read_from_file_e(string filename){
     ifstream in;
    in.open(filename,ios::app);
    if(in.fail()){
        std::cerr<<"Could not open File"<<endl;
        exit(1);
    }
   
    string name,age;
    in>>name>>age;
    while(!in.eof()){
        cout<<"Name : "<<name<<" Age:"<<age<<endl;
        in>>name>>age;


    }
    cout<<endl;
    in.close();
    cout<<"File closed successfully after reading "<<endl;

}
//using get and put functions
void write_to_file_f(string filename){
    string choice; 
    ofstream out; 
    char c; 
    out.open(filename,ios::app);
    if (!out.fail()){
        while(true){
            cin.sync();
            cout<<"Enter the name and age of the person : ";
            cin.get(c);
            while(c!='\n'){
            out.put(c);
            cin.get(c);
            }
            out.put('\n');
            cout<<"Have more data?(Y/N) : ";
            cin>>choice;
            if (choice=="N") break; 
            
        }
    out.close();
    cout<<"file closed successfully after writing"<<endl;
    }
    else{
        cerr<<"Something went wrong."<<endl;
    }

}
void read_from_file_f(string filename){
    char c;
    int count ; 
    ifstream file;
    file.open(filename);
    file.seekg(0,ios::end);
    int end = file.tellg();
    file.seekg(0,ios::beg);
    if(file.fail()){
        cerr<<"Could not open "<<filename<<endl;
        exit(1);
    }
    else{
    while(count<end){
        cout<<"Name : ";
        while(c!=' ')
        {
        file.get(c);
        count+=1;
        cout<<c;
        }
        cout<<"Age : ";
        while(c!='\n')
        {
        file.get(c);
        count+=1;
        cout<<c;
        }
        count+=1;
    }
    cout<<endl;
    cout<<"File closed successfully after reading"<<endl;
    }
}

int main()
{
    write_to_file_e("record.txt");
    read_from_file_e("record.txt");
    write_to_file_f("record1.txt");
    read_from_file_f("record1.txt");
    return 0;
}
