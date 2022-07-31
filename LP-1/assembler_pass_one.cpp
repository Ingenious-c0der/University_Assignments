#include<iostream>
#include<fstream>
#include<vector>
#include <unordered_map>
//to-be-implemented
class Tables{
    static const std::unordered_map<std::string, int> opcodes;
    static const std::unordered_map<std::string, int> registers;
    static const std::unordered_map<std::string, std::string> classes;

};
const std::unordered_map<std::string, int> Tables::opcodes =  {
    {"STOP",0},
    {"ADD",1},
    {"SUB",2},
    {"MULT",3},
    {"MOVER",4},
    {"MOVEM",5},
    {"COMP",6},
    {"BC",7},
    {"DIV",8},
    {"READ",9},
    {"PRINT",10},
    {"START",1},
    {"END",2},
    {"ORIGIN",3},
    {"EQU",4},
    {"LTORG",5},
    {"DC",1},
    {"DS",2},

};

const std::unordered_map<std::string, std::string> Tables::classes = {
    {"STOP","IS"},
    {"ADD","IS"},
    {"SUB","IS"},
    {"MULT","IS"},
    {"MOVER","IS"},
    {"MOVEM","IS"},
    {"COMP","IS"},
    {"BC","IS"},
    {"DIV","IS"},
    {"READ","IS"},
    {"PRINT","IS"},
    {"START","AD"},
    {"END","AD"},
    {"ORIGIN","AD"},
    {"EQU","AD"},
    {"LTORG","AD"},
    {"DC","DL"},
    {"DS","DL"},

};

const std::unordered_map<std::string, int > Tables::registers =  {
    {"AREG",1},
    {"BREG",2},
    {"CREG",3},
    {"DREG",4},

};

class ICWriter {
    static void writeICLine(std::vector<std::string>);
};

void ICWriter::writeICLine(std::vector<std::string> tokens) {
    std::string outline ;
    for(auto token :tokens)
    {
        outline += token + " ";
    }
    std::ofstream outfile;
    outfile.open("IC.txt", std::ios_base::app);
    outfile << outline << std::endl;
    outfile.close();
}

class SourceCodeLine {
    static int LC ;
    std::string label;
    std::string opcode;
    std::string operand_1;
    std::string operand_2;

    static std::vector<std::string> convertor(std::vector<std::string>);
    static SourceCodeLine readLine(std::string sourceline)
    {
        SourceCodeLine line;
        std::vector<std::string> tokens {};
        size_t pos = 0;
        std::string delimiter =  " " ;  
        while ((pos = sourceline.find(delimiter)) != std::string::npos) {
            //TODO: capitalize them here
        tokens.push_back(sourceline.substr(0, pos));
        sourceline.erase(0, pos + delimiter.length());
        }
        
        return line;
    }

    SourceCodeLine(std::string label = "", std::string opcode = "", std::string operand_1 = "", std::string operand_2 = "") {	
        this->label = label;
        this->opcode = opcode;
        this->operand_1 = operand_1;
        this->operand_2 = operand_2;
    }
};
int SourceCodeLine::LC = 0;
std::vector<std::string> SourceCodeLine::convertor(std::vector<std::string> tokens)
{
    std::vector<std::string> converted_tokens {};
    for(auto token : tokens)
    {
        if(token == "START")
        {
            
        }
    }

};

int main()
{
    
    return 0;
}