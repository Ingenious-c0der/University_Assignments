#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <regex>

class InputReader
{
    std::ifstream infile;

public:
    InputReader()
    {
       
    }
    void open(const std::string& filename)
    {
        infile.open(filename);
    }
    ~InputReader()
    {
        infile.close();
    }
    std::string readNext()
    {
        std::string line;
        std::getline(infile, line);
        return line;
    }
    void setPointerFrom(int index)
    {
        std::string line;
        int lineNo = 1;
         
        //std::cout<<"index is "<<index<<std::endl;
        if (index == 0 || index == 1)
        {
            infile.seekg(0, std::ios::beg);
            return;
        }
        while (std::getline(infile, line))
        {
            //std::cout<<"line "<<line<<std::endl;
            if(lineNo == index-1)
            {

                return;
            }
            lineNo++; 
        }
    }
};

class macroProcessorSecond
{
    std::fstream MNT;
    std::fstream KPDTAB;
    std::fstream MDT;
    std::fstream PNTAB;
    std::fstream APTAB;
    std::fstream EC; // Expansion Code File
    int PNTAB_ptr = 0;
    int KPDTAB_ptr = 0;
    int MNTTAB_ptr = 0;
    int MDTTAB_ptr = 1;
    int kp_pool = 1;
    std::vector<std::string> pntab{};
    InputReader r;

public:
    macroProcessorSecond()
    {
        r.open("calls.txt");
        MNT.open("MNT.txt");
        KPDTAB.open("KPDTAB.txt");
        MDT.open("MDT.txt");
        PNTAB.open("PNTAB.txt");
        APTAB.open("APTAB.txt");
        EC.open("ExtendedCode.txt");
    }

    std::vector<int> searchMNT(std::string macroName)
    {
        std::vector<int> mntData{};
        std::string line;
        int lineNo = 0;
        while (std::getline(MNT, line))
        {
            lineNo++;
            // std::cout << line << std::endl;
            std::istringstream iss(line);
            std::string word;
            iss >> word;
            iss >> word;
            // std::cout<<word<<std::endl;
            if (word == macroName)
            {
                mntData.push_back(lineNo);
                iss >> word;
                mntData.push_back(std::stoi(word));
                iss >> word;
                mntData.push_back(std::stoi(word));
                iss >> word;
                mntData.push_back(std::stoi(word));
                iss >> word;
                mntData.push_back(std::stoi(word));
                break;
            }
        }
        return mntData;
    }
    int getQ(std::string paramName)
    {
        std::string line;
        int lineNo = 0;
        while (std::getline(KPDTAB, line))
        {
            lineNo++;
            // std::cout <<"QLine"<< line << std::endl;
            std::istringstream iss(line);
            std::string word;
            iss >> word;
            int loc = std::stoi(word);
            iss >> word;
            if (word == paramName)
            {
                iss >> word;
                KPDTAB.clear();
                KPDTAB.seekg(0, std::ios::beg);
                return loc;
            }
        }
        KPDTAB.clear();
        KPDTAB.seekg(0, std::ios::beg);
        // TODO: Raise Error
        return -1;
    }

    std::string getDefaultParamName(int index)
    {
        std::string line;
        int lineNo = 0;
        while (std::getline(KPDTAB, line))
        {
            lineNo++;
            
            std::istringstream iss(line);
            std::string word;
            iss >> word;
            int loc = std::stoi(word);
            iss >> word;
            if (loc == index)
            {
                KPDTAB.clear();
                KPDTAB.seekg(0, std::ios::beg);
                return word;
            }
        }
        KPDTAB.clear();
        KPDTAB.seekg(0, std::ios::beg);
        return "---";
    }

    std::string getDefaultValue(int index)
    {   
        //std::cout<<"returning param at index : "<<index<<std::endl;
        std::string line;
        int lineNo = 0;
        while (std::getline(KPDTAB, line))
        {
            lineNo++;
            // std::cout <<"QLine"<< line << std::endl;
            std::istringstream iss(line);
            std::string word;
            iss >> word;
            int loc = std::stoi(word);
            iss >> word;
            iss >> word;
            if (loc == index)
            {
                KPDTAB.clear();
                KPDTAB.seekg(0, std::ios::beg);
                return word;
            }
        }
        KPDTAB.clear();
        KPDTAB.seekg(0, std::ios::beg);
        return "---";
    }
    
    void Process()
    {
        std::string ipline = "";
        while (1)
        {
            ipline = r.readNext();
            if (ipline == "")
            {
                std::cout << "Pass 2 Completed" << std::endl;
                break;
            }
            else
            {
                std::string space_delimiter = " ";
                std::vector<std::string> words{};
                size_t pos = 0;
                int total_ap_size = 0;
                int MDTPtr = 0;
                int KPDPTR = 0;
                int APTAB_ctr = 0;
                int total_params_recieved = 0;
                int named_params_received_count = 0 ; 
                int q = 0;


                while ((pos = ipline.find(space_delimiter)) != std::string::npos)
                {
                    words.push_back(ipline.substr(0, pos));
                    ipline.erase(0, pos + space_delimiter.length());
                    if ((pos = ipline.find(space_delimiter)) == std::string::npos)
                    {
                        words.push_back(ipline.substr(0, pos));
                    }
                }
                // std::cout<<words[0]<<std::endl;
                std::string macro_name = words[0];
                std::vector<int> macroMetaData = searchMNT(words[0]);
                total_ap_size = macroMetaData[1] + macroMetaData[2];
                MDTPtr = macroMetaData[3];
                KPDPTR = macroMetaData[4];

                // std::cout<<"Total Count of AP: "<<total_ap_size<<std::endl;
                // std::cout<<"MDT Pointer: "<<MDTPtr<<std::endl;
                // std::cout<<"KPD Pointer: "<<KPDPTR<<std::endl;
                std::vector<std::string> APTAB_vec(total_ap_size, "-");
                std::vector<std::string> named_params_received(total_ap_size, "-");

                words.erase(words.begin());
                for (auto &word : words)
                {

                    if (std::regex_match(word, std::regex("(.+)(=)(.+)")))
                    {
                        // std::cout << "Word: " << word << std::endl;
                        std::string delimiter = "=";
                        std::string param = word.substr(0, word.find(delimiter));
                        std::string value = word.substr(word.find(delimiter) + 1, word.length());
                        //std::cout << "Param: " << param << std::endl;
                        //std::cout << "Value: " << value << std::endl;
                        q = getQ(param);
                        //std::cout << "Q: " << q << std::endl;
                        //std::cout<<"KPD BASE "<<macroMetaData[4]<<std::endl;
                        //std::cout<< "APTAB location : " << macroMetaData[1] + q - macroMetaData[4]  << std::endl;
                        named_params_received[named_params_received_count] = param;
                        named_params_received_count++;
                        total_params_recieved++;
                        APTAB_vec[macroMetaData[1] + q - macroMetaData[4]] = value;
                    }
                    else if (std::regex_match(word, std::regex("(.*)(=)")))
                    {
                        std::cout << "ERROR , NO PARAMETER PASSED FOR KEYWORD PARAM " << word << std::endl;
                        exit(1);
                    }
                    else
                    {
                        total_params_recieved++;
                        APTAB_vec[APTAB_ctr] = word;
                        APTAB_ctr++;
                    }
                }
                //TODO: symbol tracking at source

                for (int i = 0; i < total_ap_size; i++)
                {
                    if (APTAB_vec[i] == "-")
                    {
                    //std::cout<< "i : " << i << std::endl;
                    //std::cout<< "KPD BASE : " << macroMetaData[4] << std::endl;
                    //std::cout<<"Positional param count " <<macroMetaData[1] << std::endl;
                    std::string defaultParamValue = getDefaultValue(i+macroMetaData[4] - macroMetaData[1]) ; 
                    //std::cout<<"Default Param Value : "<<defaultParamValue<<std::endl;
                    if(defaultParamValue == "---")
                    {
                        std::cout << "ERROR , NO VALUE PASSED FOR KEYWORD PARAMETER " << getDefaultParamName(i+macroMetaData[4]-macroMetaData[1]) << std::endl;
                        exit(1);
                    }
                    else
                    {
                        APTAB_vec[i] = defaultParamValue;
                    }
                    
                    }
                }
                //write to APTAB
                APTAB_ctr = 1;
               
                for (auto &word : APTAB_vec)
                {
                    APTAB << APTAB_ctr << "  " << word << std::endl;
                    APTAB_ctr++;
                }
                
                //write to Expanded Code File
                InputReader ECwriter ; 
                ECwriter.open("MDT.txt");
              
                ECwriter.setPointerFrom(macroMetaData[3]);
                std::string mdtline = ECwriter.readNext();
                //split it into words 
                std::vector<std::string> mdtwords{};
                int EC_ctr = 1 ; 
                
                while(1)
                {
                    mdtwords.clear();
                    pos = 0;
                    while ((pos = mdtline.find(space_delimiter)) != std::string::npos)
                    {
                        mdtwords.push_back(mdtline.substr(0, pos));
                        mdtline.erase(0, pos + space_delimiter.length());
                        if ((pos = mdtline.find(space_delimiter)) == std::string::npos)
                        {
                            mdtwords.push_back(mdtline.substr(0, pos));
                        }
                    }
                    if(mdtwords.back() == "MEND")
                    {
                        break;
                    }
                    EC<<EC_ctr<<" ";
                    
                    for(auto &word : mdtwords)
                    {
                        if(std::regex_match(word, std::regex("(\\()(.*)(\\))")))
                        {
                            std::string delimiter = ",";
                            
                            int val_index = stoi(word.substr(word.find(delimiter) + 1, word.length()));
                           
                            // std::cout<<"Q : "<<val_index<<std::endl;
                            // std::cout<<"APTAB : "<<APTAB_vec[val_index-1]<<std::endl;
                            EC << APTAB_vec[val_index-1] << " ";
                        }
                        else if(std::regex_match(word, std::regex("[0-9]")))
                        {
                            continue; 
                        }
                        else
                        {
                            EC << word << " ";
                        }
                    }
                    EC << std::endl;
                    mdtline = ECwriter.readNext();
                    EC_ctr++; 
                }

                
            }
        }
    }
};

int main()
{
    macroProcessorSecond m;
    m.Process();
    return 0;
}