#include<iostream>
#include<fstream>
using namespace std;



class FileHandling{
    private:
    string Filename;
    string Data;
    public:
    FileHandling(string Filename){
        this->Filename = Filename; 
    }
    void writeData();
    void readData();
};

void FileHandling::writeData(){
    ofstream out; 
    string choice;
    string data;
    out.open(Filename,ios::app);
    if(out.fail())
    {
        std::cerr<<"Could not open File"<<endl;
        exit(1);
    }
    while(true)
    {
    cout<<"Enter the data to be entered. : ";
    cin.sync();
    getline(cin,data);
    out<<data<<endl;
    cout<<"Have more data?(Y/N) : ";
    cin>>choice;
    if (choice=="N") break;
        
    }

    
    out.close();
    cout<<"File closed successfully after writing "<<endl;
}

void FileHandling::readData(){
    ifstream in;
    in.open(Filename);
    if(in.fail()){
        std::cerr<<"Could not open File"<<endl;
        exit(1);
    }
    char Data;
    in>>Data;
    while(!in.eof()){
        cout<<Data;
        in>>Data;


    }
    cout<<endl;
    in.close();
    cout<<"File closed successfully after reading "<<endl;

}


int main()

{  
    FileHandling file("output.txt");
    file.writeData();
    file.readData();

    return 0;
}
