#include<iostream>
#include<fstream>
using namespace std;

int get_file_size(string filename){
    int start,end; 
    ifstream file;
  
    file.open(filename);
    if(!file.fail()){
        file.seekg(0,ios::beg);
        start = file.tellg();
        file.seekg(0,ios::end);
        end = file.tellg();
        file.close();
        return end-start;
    }
 else{
     cerr<<"Error in opening file"<<filename; 
     exit(1);
     }



}

int main()
{   string filename; 
    cout<<"Enter the filename of the file : ";
    cin>>filename;
    cout<<"The file is "<<get_file_size(filename)<< " bytes."<<endl;
    return 0;
}