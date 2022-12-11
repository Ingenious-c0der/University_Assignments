#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
#include <regex>
#include <sstream>
#include <string>
using namespace std;
int mod_val = 1 ;
class Item
{
    long long worry_level = 0;
    Item()
    {
    }

public:
    Item(int worry_level)
    {
        this->worry_level = worry_level;
    }
    friend class Monkey;
};

class Monkey
{

    string operation = "+";
    int delta = 0;
    int divisibility = 0;
    int monk_number = 0;

public:
    vector<Item> items;
    vector<int> next_monkeys = {0, 0}; // true case , false case
    int total_inspects = 0;
    
    void printItems()
    {
        cout << "Monkey " << monk_number << " : ";
        for (int i = 0; i < items.size(); i++)
        {
            cout << items[i].worry_level << " ";
        }
        cout << endl;
    }
    Monkey(vector<Item> items, vector<int> next_monkeys, string operation, int divisibility, int delta, int monk_number)
    {
        this->items = items;
        this->next_monkeys = next_monkeys;
        this->operation = operation;
        this->divisibility = divisibility;
        this->delta = delta;
        this->monk_number = monk_number;
    }
    Monkey()
    {
    }
    void operate_round(vector<Monkey> &monk_vec)
    {
        // cout items

        for (int i = 0; i < items.size(); i++)
        {
            // cout<<items[i].worry_level << " ";
            total_inspects++;
            Item item;
            if (operation == "+")
            {
                items[i].worry_level += delta;
               
            }
            else if (operation == "*")
            {
                items[i].worry_level *= delta;
               
            }
            else
            {
                items[i].worry_level *= items[i].worry_level;
            }
             items[i].worry_level %= mod_val;
             item = items[i];
             monk_vec[(item.worry_level) % divisibility == 0 ? next_monkeys[0] : next_monkeys[1]].items.push_back(item);
            // std::cout<< "Monkey " << monk_number << " has thrown " << item.worry_level << " at " << " Monkey "<< ((item.worry_level) % divisibility == 0 ? next_monkeys[0] : next_monkeys[1])<< endl;
        }
        items.clear();
    }
};

int main()
{
    vector<Monkey> monkeys;
    ifstream file("input1.txt");
    // generate monkey objects by reawding input
    int count = 0;
    int max_monks = 8;
    string line = "";
    while (!file.eof())
    {
        vector<Item> items = {};
        vector<int> next_monkeys = {0, 0};
        string operation = "+";
        int divisibility = 0;
        int delta;
        string del;
        // cout<< "monkey " << count << endl;
        line = "";
        for (int i = 0; i < 7; i++)
        {
            cout << i;
            switch (i)
            {
            case 0:
                getline(file, line);
                // cout<< line << endl;
                break;
            case 1: // starting items
            {
                getline(file, line);
                stringstream ss(line);
                while (getline(ss, line, ' '))
                {
                    items.push_back(Item(stoi(line)));
                }
                // tokenize line
                break;
            }
            case 2: // operation
            {
                getline(file, line);
                stringstream ss(line);
                ss >> operation >> del;
                if (operation == "**")
                {
                    delta = 0;
                }
                else
                {
                    delta = stoi(del);
                }
                break;
            }
            case 3:
            {
                getline(file, line);
                stringstream ss(line);
                ss >> divisibility;
                break;
            }
            case 4:
            {
                getline(file, line);
                stringstream ss(line);
                ss >> next_monkeys[0];
                break;
            }
            case 5:
            {
                getline(file, line);
                stringstream ss(line);
                ss >> next_monkeys[1];
                break;
            }
            case 6:
                cout << file.eof();
                getline(file, line);
                // cout<< ":A#" << endl;
                // cout<<file.eof();
                break;
            }
        }
        // cout a monkey
        Monkey monkey = Monkey(items, next_monkeys, operation, divisibility, delta, count);
        monkeys.push_back(monkey);
        cout << "Monkey " << count << " has " << monkeys[count].items.size() << " items"
             << " operation " << operation << " " << divisibility << " " << delta << "throws at " << monkeys[count].next_monkeys[0] << " - " << monkeys[count].next_monkeys[1] << endl;
        count++;
        mod_val*= divisibility;
        if (count == max_monks)
            break;
    }
    cout << "\nBefore Round " << endl;
    for (int j = 0; j < max_monks; j++)
    {
        monkeys[j].printItems();
    }
    for (int i = 0; i < 10000; i++)
    {

        for (int j = 0; j < max_monks; j++)
        {

            monkeys[j].operate_round(monkeys);
        }
        if(i%1000 == 0){

            cout << "\nRound " << i << endl;
            
            for (int j = 0; j < max_monks; j++)
            {
                monkeys[j].printItems();
             
               cout<< monkeys[j].total_inspects<< " " <<endl;
            }
        }
    }

    // cout monkeys
    for (int i = 0; i < max_monks; i++)
    {
        cout << "Monkey " << i << " has " << monkeys[i].total_inspects << " total inspections"
             << " size " << monkeys[i].items.size() << endl;
    }

    return 0;
}