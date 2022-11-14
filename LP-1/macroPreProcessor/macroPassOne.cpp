#include <iostream>
#include <fstream>
#include <vector>

#include <regex>

class InputReader
{
    std::ifstream infile;

public:
    InputReader()
    {
        infile.open("input.txt");
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

class macroProcessorFirst
{
    std::fstream MNT;
    std::fstream KPDTAB;
    std::fstream MDT;
    std::fstream PNTAB;
    int PNTAB_ptr = 0;
    int KPDTAB_ptr = 0;
    int MNTTAB_ptr = 0;
    int MDTTAB_ptr = 1;
    int kp_pool = 1;
    std::vector<std::string> pntab{};
    InputReader r;

public:
    macroProcessorFirst()
    {
        MNT.open("MNT.txt");
        KPDTAB.open("KPDTAB.txt");
        MDT.open("MDT.txt");
        PNTAB.open("PNTAB.txt");
    }
    ~macroProcessorFirst()
    {
        MNT.close();
        KPDTAB.close();
        MDT.close();
        PNTAB.close();
    }

    void Process()
    {
        std::string ipline = "";
        while (1)
        {
            ipline = r.readNext();
            if (ipline == "")
                {
                    // eof
                    break;
                }
            if (ipline == "MACRO")
            {
                // generates KPDTAB, MNT and PNTAB entries
                int ppCount = 0;
                int kpCount = 0;
                std::string prototypingSmt = r.readNext();
                std::string space_delimiter = " ";
                std::vector<std::string> words{};
                std::string name = "";

                size_t pos = 0;
                while ((pos = prototypingSmt.find(space_delimiter)) != std::string::npos)
                {
                    words.push_back(prototypingSmt.substr(0, pos));
                    prototypingSmt.erase(0, pos + space_delimiter.length());
                    if ((pos = prototypingSmt.find(space_delimiter)) == std::string::npos)
                    {
                        words.push_back(prototypingSmt.substr(0, pos));
                    }
                }
                for (auto &word : words)
                {
                    // case for keyword param with default value

                    if (std::regex_match(word, std::regex("(&.+)(=)(.+)")))
                    {
                        std::vector<std::string> elems{};
                        std::string space_delimiter_equal = "=";
                        while ((pos = word.find(space_delimiter_equal)) != std::string::npos)
                        {
                            elems.push_back(word.substr(0, pos));
                            word.erase(0, pos + space_delimiter_equal.length());
                            if ((pos = word.find(space_delimiter_equal)) == std::string::npos)
                            {
                                elems.push_back(word.substr(0, pos));
                            }
                        }
                        KPDTAB_ptr++;

                        if (elems.size() == 2)
                        {
                            elems.front().erase(0, 1);

                            KPDTAB << KPDTAB_ptr << " " << elems.front() << " " << elems.back() << std::endl;
                        }
                        PNTAB_ptr++;
                        pntab.push_back(elems.front());
                        PNTAB << PNTAB_ptr << " " << elems.front() << std::endl;
                        kpCount++;
                    }
                    // case for keyword param with no default
                    else if (std::regex_match(word, std::regex("(&.+)(=)")))
                    {
                        std::vector<std::string> elems{};
                        std::string space_delimiter_equal = "=";
                        while ((pos = word.find(space_delimiter_equal)) != std::string::npos)
                        {
                            elems.push_back(word.substr(0, pos));
                            word.erase(0, pos + space_delimiter_equal.length());
                            if ((pos = word.find(space_delimiter_equal)) == std::string::npos)
                            {
                                elems.push_back(word.substr(0, pos));
                            }
                        }
                        PNTAB_ptr++;
                        kpCount++;
                        KPDTAB_ptr++;
                        elems.front().erase(0, 1);
                        KPDTAB << KPDTAB_ptr << " "
                               << elems.front() << " "
                               << "---" << std::endl;
                        pntab.push_back(elems.front());
                        PNTAB << PNTAB_ptr << " " << elems.front() << std::endl;
                    }
                    // case for positional param
                    else if (std::regex_match(word, std::regex("(&)(.)")))
                    {

                        // std::vector<std::string> elems{};
                        // std::string space_delimiter_equal = "&";
                        // while ((pos = word.find(space_delimiter_equal)) != std::string::npos)
                        // {
                        //     elems.push_back(word.substr(0, pos));
                        //     word.erase(0, pos + space_delimiter_equal.length());
                        // }

                        PNTAB_ptr++;
                        word.erase(0, 1);
                        pntab.push_back(word);
                        PNTAB << PNTAB_ptr << " " << word << std::endl;
                        ppCount++;
                    }
                    // case for macro name
                    else
                    {
                        name = word;
        
                    }
                }
                MNTTAB_ptr++;

                MNT << MNTTAB_ptr << " " << name << " " << ppCount << " " << kpCount << " " << MDTTAB_ptr << " " << kp_pool << std::endl;
                PNTAB_ptr = 0;
            }
            else if (ipline == "MEND")
            {
                // reset PNTAB pointers and Add to MDT
               
                MDT << MDTTAB_ptr << " MEND"<< std::endl;
                MDTTAB_ptr++;
                kp_pool = KPDTAB_ptr + 1;
                PNTAB_ptr = 0;
                pntab = {};
            }
            else
            {
                // generate MDT entry
                
                size_t pos = 0;
                std::vector<std::string> elems{};
                std::string space_delimiter_equal = " ";
                while ((pos = ipline.find(space_delimiter_equal)) != std::string::npos)
                {
                    elems.push_back(ipline.substr(0, pos));
                    ipline.erase(0, pos + space_delimiter_equal.length());
                    if ((pos = ipline.find(space_delimiter_equal)) == std::string::npos)
                    {
                        elems.push_back(ipline.substr(0, pos));
                    }
                }


                std::string instruction = "";
                std::string op_1 = "";
                std::string op_2 = "";
                bool op1_full = false;
                for (auto &word : elems)
                {
                    if (std::regex_match(word, std::regex("(&)(.)")))
                    {
                        word.erase(0, 1);
                        int ctr = 1;
                        for (auto &p : pntab)
                        {
                            if (word == p)
                            {

                                if (op1_full)
                                {
                                    op_2 = "(P," + std::to_string(ctr) + ")";
                                }
                                else
                                {
                                    op_1 = "(P," + std::to_string(ctr) + ")";
                                    op1_full = !op1_full;
                                }

                                break;
                            }
                            ctr++;
                        }
                    }
                    else if (std::regex_match(word, std::regex("(.*)(=)(.*)")))
                    {
                        op_2 = word;
                    }
                    else
                    {

                        instruction = word;
                    }
                }
                
                MDT << MDTTAB_ptr << " " << instruction << " " << op_1 << " " << op_2 << std::endl;
                MDTTAB_ptr++;
                
            }
            
        }
    }
};

int main()
{
    macroProcessorFirst m;
    m.Process();
    std::cout<< "Pass One completed Successfully" << std::endl;
}