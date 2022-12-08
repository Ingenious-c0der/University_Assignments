#include<iostream>
#include<stack>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>

using namespace std ; //:(
int main()
{
    ifstream input_file("input.txt") ;
    ifstream meta_input("metainput.txt") ;
    vector<stack<char>> crate_bay = {};
    while(!meta_input.eof())
    {
        string line ;
        getline(meta_input,line) ;
        stack<char> crate ;
        for(int i=0;i<line.length();i++)
        {
            crate.push(line[i]) ;
        }
        crate_bay.push_back(crate) ;
    }
    
    while(!input_file.eof())
    {
        string line ;
        getline(input_file,line) ;
        // split line with whitespace 
        stringstream ss(line) ;
        string token ;
        vector<string> tokens ;
        while(getline(ss,token,' '))
        {
            tokens.push_back(token) ;
        }
        //show tokens 
        int total = stoi(tokens[1]) ;
        int from = stoi(tokens[3]) ;
        int to = stoi(tokens[5]) ;
        stack<char> temp_crate_stack ; 
        for (int i = 0; i <total; i++)
        {
           char crate = crate_bay[from-1].top() ;
           crate_bay[from-1].pop() ;
           temp_crate_stack.push(crate) ;
        }
        for(int i=0;i<total;i++)
        {
            crate_bay[to-1].push(temp_crate_stack.top()) ;
            temp_crate_stack.pop() ;
        }
        cout<<temp_crate_stack.empty()<<endl ;
    }

    for(int i=0;i<crate_bay.size();i++)
    {
        cout<< crate_bay[i].top() << " " ;
          
    }
     cout<<endl ;
   


}