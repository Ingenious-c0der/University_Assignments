#include<iostream> 
#include<map> 
#include<fstream>
#include<string>
// AX rocks 
// BY Papers 
// CZ SCISSORS 
int main(){
    std::ifstream input("input.txt"); 
    std::map<std::string,std::string> combos ={
        {"AX", "S"}, 
        {"AY", "R"},
        {"AZ", "P"},
        {"BX", "R"},
        {"BY", "P"},
        {"BZ", "S"}, 
        {"CX", "P"},
        {"CY", "S"},
        {"CZ", "R"},
    }; 
    std::map<std::string,int> value_map  = 
    {
        {"P",2},
        {"S",3},
        {"R",1}
    } ;
    std::map<char,int> value2_map  = 
    {
        {'X',0},
        {'Y',3},
        {'Z',6}
    } ;
     std::string line ; 
     std::string combo ; 
     int reward = 0 ; 
    while(!input.eof()){

        std::getline(input, line) ; 
        combo += line[0];
        combo += line[2]; 
        reward += value_map[combos[combo]] + value2_map[line[2]] ; 
        combo = ""; 
    }
    std::cout<<reward<<std::endl; 



    return 0; 


}



