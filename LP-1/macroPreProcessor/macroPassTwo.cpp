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
        infile.open("calls.txt");
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
        MNT.open("MNT.txt");
        KPDTAB.open("KPDTAB.txt");
        MDT.open("MDT.txt");
        PNTAB.open("PNTAB.txt");
        APTAB.open("APTAB.txt");
        EC.open("EC.txt");
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
    int getTotalDefaultParams(int kptab_ptr , int range)
    {
        int totalDefaultParams = 0;
        int ctr = 0  ; 
        KPDTAB.seekg(0, KPDTAB.beg);
        std::string line;
        int lineNo = 0;
        for(int i=0;i<kptab_ptr;i++)
        {
            std::getline(KPDTAB, line);
        }
        while (ctr < range)
        {
             std::istringstream iss(line);
                std::string word;
                iss >> word;
                iss >> word;
                iss>> word; 
            if (word!= "---")
            {    
                totalDefaultParams++;
            }
        }
        return 0;
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
    void Process()
    {
        std::string ipline = "";
        while (1)
        {
            ipline = r.readNext();
            if (ipline == "")
            {
                std::cout << "End of File" << std::endl;
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

                words.erase(words.begin());
                for (auto &word : words)
                {

                    if (std::regex_match(word, std::regex("(.+)(=)(.+)")))
                    {
                        // std::cout << "Word: " << word << std::endl;
                        std::string delimiter = "=";
                        std::string param = word.substr(0, word.find(delimiter));
                        std::string value = word.substr(word.find(delimiter) + 1, word.length());
                        // std::cout << "Param: " << param << std::endl;
                        // std::cout << "Value: " << value << std::endl;
                        q = getQ(param);
                        // std::cout << "Q: " << q << std::endl;
                        // std::cout<< "APTAB location : " << macroMetaData[1] + q - macroMetaData[2] + 1 << std::endl;
                        total_params_recieved++;
                        APTAB_vec[macroMetaData[1] + q - macroMetaData[2] + 1] = value;
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
                if (total_ap_size != total_params_recieved)
                {

                    if (total_params_recieved + getTotalDefaultParams( macroMetaData[4],macroMetaData[2]) == total_ap_size)
                    {
                      
                    }
                    
                    
                    else
                    {
                        std::cout << "ERROR , NOT ENOUGH PARAMETERS PASSED FOR MACRO NAMED " << macro_name << " , EXPECTED " << total_ap_size << " RECIEVED " << total_params_recieved << std::endl;
                        exit(1);
                    }
                }
                APTAB_ctr = 1;
                for (auto &word : APTAB_vec)
                {
                    APTAB << APTAB_ctr << "  " << word << std::endl;
                    APTAB_ctr++;
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