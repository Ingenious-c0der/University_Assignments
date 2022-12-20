#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <regex>
using namespace std;

class Node
{
    int flow_rate = 0;
    string name = "";
    bool isOpen = false ;
    vector<Node *> nexts;
    Node(string name, int flow_rate)
    {
        this->name = name;
        this->flow_rate = flow_rate;
    }
    friend class PipeNetwork;
};
class PipeNetwork
{

    vector<Node *> nodes;

public:
    PipeNetwork()
    {
    }
    void loadNodes(vector<string> names, vector<int> flow_rates)
    {
        for (int i = 0; i < names.size(); i++)
        {
            Node *node = new Node(names[i], flow_rates[i]);
            nodes.push_back(node);
        }
    }

    void displayNetwork()
    {
        for (int i = 0; i < nodes.size(); i++)
        {
            cout << nodes[i]->name << " " << nodes[i]->flow_rate << endl;
            for (int j = 0; j < nodes[i]->nexts.size(); j++)
            {
                cout << nodes[i]->nexts[j]->name << " ";
            }
            cout << endl;
        }
    }


    void connectNode(string parent, vector<string> next_names)
    {
        int parent_index = 0;
        for (int i = 0; i < nodes.size(); i++)
        {
            if (nodes[i]->name == parent)
            {
                parent_index = i;
                break;
            }
        }

        for (int i = 0; i < next_names.size(); i++)
        {
            for (int j = 0; j < nodes.size(); j++)
            {
                if (nodes[j]->name == next_names[i])
                {
                    nodes[parent_index]->nexts.push_back(nodes[j]);
                }
            }
        }
    }
};

int main()
{
    fstream input("input.txt");
    string line;
    vector<string> names;
    vector<int> flow_rates;
    vector<string> next_names;
    vector<vector<string>> all_names;
    PipeNetwork network;
    while (getline(input, line))
    {
        // regex replace
        smatch m;
        regex r("([A-Z])([A-Z])");
        vector<string> line_names;
        int flow_rate = stoi(regex_replace(line, regex("[^0-9]"), " "));
        while (regex_search(line, m, r))
        {
            line_names.push_back(m[0].str());
            line = m.suffix().str(); 
        }
        flow_rates.push_back(flow_rate);
        names.push_back(line_names[0]);
        all_names.push_back(line_names);
    }

    network.loadNodes(names, flow_rates);
    for (int i = 0; i < all_names.size(); i++)
    {
        network.connectNode(all_names[i][0], vector<string>(all_names[i].begin() + 1, all_names[i].end()));
    }
    network.displayNetwork();
    return 0;
}