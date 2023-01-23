
#include <iostream>
#include <vector>
#include <set>
using namespace std;

class Solution
{
    vector<vector<char>> components;
    vector<vector<char>> unequal;

public:
    int componentPool(char symbol)
    {
        for (int i = 0; i < components.size(); i++)
        {
            for (auto symbol_this : components[i])
            {
                if (symbol == symbol_this)
                    return i;
            }
        }
        return -1;
    }

    bool equationsPossible(vector<string> &equations)
    {
        for (string equation : equations)
        {
            if (equation.find("!") != string::npos)
            {
                vector<char> c;
                c.push_back(equation[0]);
                c.push_back(equation[3]);
                unequal.push_back(c);
            }
            else
            {
                int pool_1 = componentPool(equation[0]);
                int pool_2 = componentPool(equation[3]);
                if (pool_1 != -1 && pool_2 != -1 && pool_1 == pool_2)
                {
                    continue;
                }
                else if (pool_1 == -1 && pool_2 != -1)
                {
                    components[pool_2].push_back(equation[0]);
                }
                else if (pool_1 != -1 && pool_2 == -1)
                {
                    components[pool_1].push_back(equation[3]);
                }
                else if (pool_1 != -1 && pool_2 != -1 && pool_1 != pool_2)
                {
                    vector<char> pool_first = components[pool_1];

                    vector<char> pool_second = components[pool_2];
                    std::set<char> new_set;
                    for (auto x : pool_first)
                    {
                        new_set.insert(x);
                    }
                    for (auto x : pool_second)
                    {
                        new_set.insert(x);
                    }
                    vector<char> new_pool(new_set.begin(), new_set.end());

                    components[pool_1] = {};
                    components[pool_2] = {};
                    components.push_back(new_pool);
                }
                else if (pool_1 == -1 && pool_2 == -1)
                {
                    vector<char> c;
                    c.push_back(equation[0]);
                    c.push_back(equation[3]);
                    components.push_back(c);
                }
            }
        }

        for (auto vec : unequal)
        {
            std::cout << vec[0] << "-" << vec[1] << endl;
            int pool_11 = componentPool(vec[0]);
            int pool_22 = componentPool(vec[1]);
            std::cout << pool_11 << " " << pool_22 << endl;

            if (pool_11 == pool_22 && pool_11 != -1)
            {

                return false;
            }
        }

        return true;
    }
};

int main()
{
    vector<string> equations = {"a==b", "e==c", "b==c", "a!=e"};
    std::cout << Solution().equationsPossible(equations);
    return 0;
}
