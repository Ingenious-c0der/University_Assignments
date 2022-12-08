#include<regex> 
#include<string> 
#include<vector>
#include<fstream>
#include<iostream>
using namespace std; 


class Directory{
    int size = 0;
    string name = "";
    Directory(string name,int size){
        this->name = name;
        this->size = size;
    }
    friend class FileTree;
};

class Node
{
    
public:
    Node(string name, Node* parent,int size = 0, vector<Node*> children = {},bool is_dir = false){
        this->name = name;
        this->size = size;
        this->children = children;
        this->is_dir = is_dir;
        this->parent = parent;
    }
    vector<Node*> children;
    string name;
    int size;
    Node* parent = nullptr; 
    bool is_dir;
};


class FileTree{ 
   
    Node* current = nullptr;
    int net_total_under_100k = 0 ;
    vector<Directory> directories ;
  
    public:
    int total_unused_space = 0  ;
    Node* root = nullptr; 
    FileTree(string name, int size){
        root = new Node(name,nullptr,0,{},true);
        this->current = root;
    }
    void add_node(string name,int size ,bool is_dir = false){
        Node* new_node = new Node(name,this->current,size,{},is_dir);
        current->children.push_back(new_node);
    }
    void cd_up(){
        current = current->parent; 
    }
    void cd_into(string name){
        for(auto child : current->children){
            if(child->name == name){
                current = child;
                return;
            }
        }
    }

    void calc_sizes(Node* node)
    {
        if(node->is_dir)
        {
            
            for(auto child : node->children)
            {
                calc_sizes(child);
                node->size += child->size;
            }
            cout<<"size of "<<node->name<<" is "<<node->size<<endl;
            directories.push_back(Directory(node->name,node->size)); 
            if(node->size <=100000)
            {
                net_total_under_100k += node->size;
            }
            if(node->name == "/")
            {
                total_unused_space = 70000000 - node->size;
            }
        
        }
    }
    void get_min_dir_size_to_delete()
    {
        int min = INT_MAX; 
        for (auto dir : directories)
        {
            if( dir.size + total_unused_space >= 30000000 && dir.size < min)
            {
                min = dir.size;
            }
        }
        cout<<"min size is "<<min<<endl;
    }

    void print_net_total_under_100k()
    {
        cout<<"net total is "<<net_total_under_100k<<endl;
    }

    string get_current_dir_name()
    {
        return current->name;
    }

}; 

int main()
{
    cout<<"tree gen started"<<endl ;
    FileTree tree("/",0);
    ifstream input("input.txt");
    string line = "";
    while(!input.eof())
    {
        if(line == "")
        {
            getline(input,line);
        }
        if(regex_match(line,regex("(\\$ cd) (\\.\\.)")))
        {
            cout<<"moving a directory up"<<endl; 
            tree.cd_up();
            cout<<"moved to "<<tree.get_current_dir_name()<<endl;
            line  = "" ;
        }
        else if (regex_match(line,regex("(\\$ cd) (.+)")))
        {
            string name = line.substr(5);
            cout<<"moving to "<<name<<endl;
            tree.cd_into(name);
            cout<<"moved to "<<tree.get_current_dir_name()<<endl;
            line = "" ;
        }
        else if(regex_match(line,regex("(\\$ ls)")))
        {
            getline(input,line);
            
            while(!regex_match(line,regex("(\\$ cd) (.+)")) && !input.eof())
            {
                
                if(regex_match(line , regex("([0-9]+)(.+)")))
                {
                   string file_name = regex_replace(line,regex("([0-9]+)(.+)"),"$2");
                   int size = stoi(regex_replace(line,regex("([0-9]+)(.+)"),"$1"));
                   tree.add_node(file_name,size);
                   cout<<"added file "<<file_name<<" of size "<<size<<" to "<<tree.get_current_dir_name()<<endl;
                }
                else if(regex_match(line,regex("(dir) (.+)")))
                {
                    string dir_name = regex_replace(line,regex("(dir) (.+)"),"$2");
                    tree.add_node(dir_name,0,true);
                    cout<<"added directory "<<dir_name<<endl;
                }
                getline(input,line);
                //cout<<regex_match(line,regex("(\\$ cd) (.+)"))<<"----"<<line <<std::endl; 

            }
            
        }
        else{
            cout<<"did not match any "<<line<<endl;
            line = "" ; 
         
        }
    }
    tree.calc_sizes(tree.root); 
    tree.print_net_total_under_100k();
    tree.get_min_dir_size_to_delete(); 
    cout<<"tree gen completed"<<endl ;
    return 0 ; 

}